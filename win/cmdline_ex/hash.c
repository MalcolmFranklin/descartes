/*******************************************************************************
 * I borrowed the hash table utilities from Ethan Solomitas xmove program.  This
 * source is covered by a copyright that pretty much allows free use
 * (see below).
 *
 * NOTE: I added compute_hash(), but DID NOT USE IT.  I was hashing on process
 *	 IDs of fork()ed child processes, which tend to be sequential.  These
 *	 lend themselves to successful hashing by a trivial modulo operation.
 *
 *	 If you want to use compute_hash(), you will have to change the assumed
 *	 key from an integer to a string, and call compute_hash from within
 *	 the hash routines.  If you compute the hash function value, and then
 *	 store it as your key, the hash table functions will not be able to
 *	 tell the difference between a duplicated entry (because you are no-
 *	 longer storing the original key), and a hash function collision.
 *
 * I found this source on src.doc.ic.ac.uk in directory:
 * /computing/graphics/systems/X11/pub/R6untarred/contrib/programs/xmove/xmove
 *
 * --Malcolm /24/94
 *******************************************************************************
 *                            xmove
 *                            -----
 *             A Pseudoserver For Client Mobility
 *
 *   Copyright (c) 1994         Ethan Solomita
 *
 *   The X Consortium, and any party obtaining a copy of these files from
 *   the X Consortium, directly or indirectly, is granted, free of charge, a
 *   full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 *   nonexclusive right and license to deal in this software and
 *   documentation files (the "Software"), including without limitation the
 *   rights to use, copy, modify, merge, publish, distribute, sublicense,
 *   and/or sell copies of the Software, and to permit persons who receive
 *   copies from any such party to do so.  This license includes without
 *   limitation a license to do the foregoing actions under any patents of
 *   the party supplying this software to the X Consortium.
 *******************************************************************************
 * $Date: 1994/08/04 17:59:15 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/hash.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: hash.c,v $
 * Revision 1.6  1994/08/04  17:59:15  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.5  1994/08/03  21:55:53  franklin
 * Changed "str" to "pstr"; prefix "str" is reserved by string.h
 *
 * Revision 1.4  1994/08/01  18:35:00  franklin
 * I decided not to use compute_hash() after all.  I simply left in in
 * this file in case someone else needs it in the future, to build a
 * hash table utility based on character string keys, rather than
 * integers.
 *
 * Also ran it through indent.
 *
 * Revision 1.3  1994/07/29  15:49:47  franklin
 * Add new hashing algorithm, compute_hash().
 *
 * Revision 1.2  1994/07/25  00:13:11  franklin
 * hash_add() and hash_free() really dont return useful values.  Make them void.
 *
 * Revision 1.1  1994/07/24  23:02:33  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: hash.c,v 1.6, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4 1994/08/04 17:59:15 franklin Exp $";

#include <stdlib.h>
#include "cchk_missing_stdlib.h"        /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

/*******************************************************************************
 * FUNCTION:	COMPUTE_HASH
 *	For best results, use a prime-number for the hash table size.  The hash
 *	table size is stored inside the hash table header struct.
 *
 * NOTE:	The hash_table pointer is a parameter, so that you can have
 *		multiple hash tables of differering sizes in your program.
 *
 *		THIS FUNCTION WAS NOT USED IN MALCOLM FRANKLINS VERSION OF THE
 *		DESCARTES LANGUAGE PROCESSOR.  I only left it here in case
 *		someone in the future wanted to compute a hash value based on
 *		a string key.
 *
 * RETURNS:	An integer, because the hash table functions expect an int.
 *		Personally, I would have used an unsigned int, but I did not
 *		want to run the risk of injecting new bugs into code that
 *		probably works.
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 ******************************************************************************/

int             compute_hash (char *pstr, hash_table * table)
{
	int             idx;
	unsigned int    hash = 0;
	static int      bits_per_int;
	static const int SHIFTNUM = 7; /* This value seemed to work best for string representations of integers. */

/*
 * On the first call to this function, find out how many bits there are in an
 * integer for this machine.
 */
	if (bits_per_int == 0)
	{
		unsigned int    bits_to_go = UINT_MAX;

		while (bits_to_go)
		{
			++bits_per_int;
			bits_to_go >>= 1;
		}
	}

	if (pstr)		/* Null pointer protection */
	{
		memcpy (&hash, pstr, sizeof (int));

	/*
	 * printf("hash before loop  = %11d ", hash); dump_bits (stdout,
	 * hash);printf("\n");fflush(stdout);
	 */
		idx = 0;
		while (*pstr && (idx < sizeof (int)))
		{
		/* Rotate, not just shift, the bits in hash */
			hash = (hash << SHIFTNUM) |
				((hash >> bits_per_int - SHIFTNUM) & ((1 << SHIFTNUM) -1));

		/*
		 * printf("hash after rot = "); dump_bits (stdout,
		 * hash);printf("\n");fflush(stdout);
		 */

			hash ^= *pstr;
			++pstr;
			++idx;
		}
	}
	if ((int) hash < 0)
		return (-hash % table->len);
	else
		return (hash % table->len);
}				       /* end compute_hash */

/*
 * here we implement the functions described in hash.h. hash_new and and
 * hash_delete create and destroy tables. All structures are allocated
 * dynamically using malloc, so the proc that called hash_new can exit. A
 * pointer is returned from hash_new with the address of the new table.
 * 
 * When the table is freed, all hash_entry->data's will be free()'d. hash_delete
 * also expects that no one else is either currently accessing the table or
 * will try to access the table in the future. hash_delete does *not* free()
 * the data, but returns it instead.
 * 
 * The "key" for a hash_entry is the first sizeof(int) bytes of the data pointed
 * to by hash_entry->data.
 * 
 * hash_find can be used to change data, since it returns the actual ptr.
 * 
 */

/*******************************************************************************
 * FUNCTION:	HASH_NEW
 ******************************************************************************/
hash_table     *hash_new (int len)
{
	hash_table     *table;

	table = (hash_table *) malloc (sizeof (hash_table));
	if (table == NULL)
		return NULL;

	table->len = len;
	table->table = (hash_entry *) calloc (len, sizeof (hash_entry));
	table->ordered_last = NULL;

	if (table->table == NULL)
	{
		free (table);
		return NULL;
	}

	return table;
}

/*******************************************************************************
 * FUNCTION:	HASH_FREE
 ******************************************************************************/
void            hash_free (hash_table * table)
{
	hash_entry     *cur,
	               *curlist,
	               *next;

	for (cur = table->table; cur < (table->table + table->len); cur++)
	{
		if (cur->data)
			free (cur->data);

		next = cur->next;
		while (next)
		{
			curlist = next;
			if (curlist->data)
				free (curlist->data);

			next = curlist->next;
			free (curlist);
		}
	}

	free (table->table);
	free (table);
}

/*******************************************************************************
 * FUNCTION:	HASH_ADD
 ******************************************************************************/
void            hash_add (hash_table * table, void *data)
{
	int             key = *(int *) data;
	int             hash_key = key % table->len;
	hash_entry     *cur = &table->table[hash_key],
	               *new;

	if (cur->data)
	{
		new = (hash_entry *) malloc (sizeof (hash_entry));
		new->next = cur->next;
		new->data = data;
		cur->next = new;
	}
	else
	{
		cur->data = data;
		new = cur;
	}

	if (table->ordered_last != NULL)
	{
		new->ordered_next = table->ordered_last->ordered_next;
		new->ordered_next->ordered_prev = new;
		new->ordered_prev = table->ordered_last;
		new->ordered_prev->ordered_next = new;
	}
	else
	{
		new->ordered_next = new;
		new->ordered_prev = new;
	}

	table->ordered_last = new;
}

/*******************************************************************************
 * FUNCTION:	HASH_FIND
 ******************************************************************************/
void           *hash_find (hash_table * table, int key)
{
	int             hash_key = key % table->len;
	hash_entry     *cur = &table->table[hash_key];

	while (1)
	{
		if (cur->data && (*(int *) (cur->data) == key))
			return cur->data;

		if (cur->next)
			cur = cur->next;
		else
			return NULL;
	}
}

/*******************************************************************************
 * FUNCTION:	HASH_DELETE
 ******************************************************************************/
void           *hash_delete (hash_table * table, int key)
{
	int             hash_key = key % table->len;
	hash_entry     *cur = &table->table[hash_key];
	hash_entry     *last = NULL;
	void           *ret_data;

/* step 1: locate key in table */

	while (1)
	{
		if (cur->data && (*(int *) (cur->data) == key))
			break;

		if (cur->next)
		{
			last = cur;
			cur = cur->next;
		}
		else
		{
			return NULL;
		}
	}

	ret_data = cur->data;	/* ret_data is returned at the very end */

/* step 2: unlink entry from ordered list */

	cur->ordered_next->ordered_prev = cur->ordered_prev;
	cur->ordered_prev->ordered_next = cur->ordered_next;

	if (table->ordered_last == cur)
	{
		if (cur == cur->ordered_prev)
			table->ordered_last = NULL;
		else
			table->ordered_last = cur->ordered_prev;
	}

/* step 3: unlink entry from hashed list */

	if (last == NULL)
	{
		if (cur->next)
		{
			hash_entry     *new_next;

			cur->data = cur->next->data;
			cur->ordered_next = cur->next->ordered_next;
			cur->ordered_next->ordered_prev = cur;
			cur->ordered_prev = cur->next->ordered_prev;
			cur->ordered_prev->ordered_next = cur;
			if (cur->next == table->ordered_last)
				table->ordered_last = cur;
			new_next = cur->next->next;
			free (cur->next);
			cur->next = new_next;

		}
		else
		{
			cur->data = NULL;
		}
	}
	else
	{
		last->next = cur->next;
		free (cur);
	}

	return ret_data;
}

/*******************************************************************************
 * I used hash_getfirst() and hash_getnext() to free memory reference by the
 * data referenced by the hash table entries.  Ex:
 *	free ( (*hash_entry)->data->allocated_string );
 * The hash_free() command takes care of freeing free ((*hash_entry)->data)
 *
 *	--Malcolm 7/29/94
 ******************************************************************************/

/*
 * the routines hash_getfirst and hash_getnext use the ordered list of the
 * hash table. The user passes in a void ** which we use as a reference as a
 * hash_entry *. These routines may be intermixed with prior hash_* routines
 * so long as hash_delete is not called on the last item obtained with
 * getfirst/getnext.
 */

#undef entry
#define entry ((hash_entry **)pos)

/*******************************************************************************
 * FUNCTION:	HASH_GETFIRST
 ******************************************************************************/
void           *hash_getfirst (void **pos, hash_table * table)
{
	if (!table->ordered_last)
		return NULL;

	*entry = table->ordered_last->ordered_next;
	if (*entry)
		return (*entry)->data;
	else
		return NULL;
}

/*******************************************************************************
 * FUNCTION:	HASH_GETNEXT
 ******************************************************************************/
void           *hash_getnext (void **pos, hash_table * table)
{
	if (*entry == table->ordered_last)
		return NULL;

	*entry = (*entry)->ordered_next;
	if (*entry)
		return (*entry)->data;
	else
		return NULL;
}

#undef entry

/*******************************************************************************
 * I did not use any of the functions that are defined past this point.
 *	(Malcolm)
 ******************************************************************************/

/*
 * the following routines scan the table unordered. They are more efficient
 * for deleting individual entries than would be the hash_getnext routine
 * combined with hash_delete.
 */

void           *hashloc_init (hash_location * loc, hash_table * table)
{
	loc->last_row = &table->table[table->len - 1];
	loc->cur_row = table->table;
	loc->prior_entry = NULL;
	loc->table = table;

	while (loc->cur_row <= loc->last_row)
	{
		if (loc->cur_row->data)
		{
			loc->cur_entry = loc->cur_row;
			return (loc->cur_entry->data);
		}

		loc->cur_row++;
	}

	return NULL;
}

void           *hashloc_getnext (hash_location * loc)
{
	if (loc->cur_row > loc->last_row)
		return NULL;

	if (loc->cur_entry->next)
	{
		loc->prior_entry = loc->cur_entry;
		loc->cur_entry = loc->cur_entry->next;
		return (loc->cur_entry->data);
	}
	else
	{
		loc->prior_entry = NULL;	/* cur_entry will be first item in row */
		while (++loc->cur_row <= loc->last_row)
		{
			if (loc->cur_row->data)
			{
				loc->cur_entry = loc->cur_row;
				return (loc->cur_entry->data);
			}
		}

		return NULL;
	}
}

void           *hashloc_deletenext (hash_location * loc)
{
	register hash_entry *cur = loc->cur_entry;

	if (loc->cur_row > loc->last_row)
		return NULL;

	if (loc->table->ordered_last == cur)
	{
		if (cur == cur->ordered_prev)
			loc->table->ordered_last = NULL;
		else
			loc->table->ordered_last = cur->ordered_prev;
	}

	cur->ordered_prev->ordered_next = cur->ordered_next;
	cur->ordered_next->ordered_prev = cur->ordered_prev;

	if (loc->cur_entry->next)
	{

	/*
	 * To delete the current entry, pull next entry's data into
	 * cur_entry, then delete next entry. This way we don't care about
	 * prior_entry, or if we are on the table directly or pointed to by
	 * it
	 */

		hash_entry     *free_me = cur->next;

		cur->data = free_me->data;
		cur->next = free_me->next;
		cur->ordered_next = free_me->ordered_next;
		cur->ordered_next->ordered_prev = cur;
		cur->ordered_prev = free_me->ordered_prev;
		cur->ordered_prev->ordered_next = cur;
		if (loc->table->ordered_last == free_me)
			loc->table->ordered_last = cur;
		free (free_me);

	/* loc->prior_entry is unchanged */

		return (cur->data);
	}
	else
	{

	/*
	 * To delete the current entry, we must check if we are on the table
	 * directly. If so, don't free anything, just change the data field
	 * to NULL. If not, we must make prior_entry point to NULL, and then
	 * free our location.
	 */

		if (loc->prior_entry)
		{
			loc->prior_entry->next = NULL;
			free (cur);
		}
		else
			loc->cur_row->data = NULL;

		loc->prior_entry = NULL;
		while (++loc->cur_row <= loc->last_row)
		{
			if (loc->cur_row->data)
			{
				loc->cur_entry = loc->cur_row;
				return (loc->cur_entry->data);
			}
		}

		return NULL;
	}
}
