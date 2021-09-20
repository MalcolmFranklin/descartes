/*******************************************************************************
 * I borrowed the hash table utilities from Ethan Solomitas xmove program.  This
 * source is covered by a copyright that pretty much allows free use
 * (see below).
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
 * $Date: 1994/08/01 18:24:19 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/hash.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: hash.h,v $
 * Revision 1.4  1994/08/01  18:24:19  franklin
 * Removed compute_hash().  It was not used in Malcolm Franklins version
 * of the Descartes language processor, and if you decide to use it,
 * you will have to perform some conversions on how the hash table
 * functions handle the key field.
 *
 * Revision 1.3  1994/07/29  15:50:15  franklin
 * Add new hashing algorithm, compute_hash().
 *
 * Revision 1.2  1994/07/25  00:15:13  franklin
 * Change hash_free() and hash_add() to void.  indent.
 *
 * Revision 1.1  1994/07/24  23:03:01  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char    *hash_h_rcsid = "@(#) $Id: hash.h,v 1.4, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4 1994/08/01 18:24:19 franklin Exp $";

#ifndef HASH_H
#define HASH_H


typedef struct hash_entry hash_entry;
typedef struct hash_table hash_table;
typedef struct hash_location hash_location;

struct hash_entry
{
	void           *data;
	hash_entry     *next;
	hash_entry     *ordered_next;
	hash_entry     *ordered_prev;
};

struct hash_table
{
	int             len;	       /* number of rows in hash table */
	hash_entry     *table;
	hash_entry     *ordered_last;
};

struct hash_location
{
	hash_entry     *cur_row;
	hash_entry     *last_row;
	hash_entry     *cur_entry;
	hash_entry     *prior_entry;   /* the entry that points to this entry */
	hash_table     *table;
};

extern hash_table *hash_new (int len);
extern void     hash_free (hash_table * table);
extern void     hash_add (hash_table * table, void *data);
extern void    *hash_find (hash_table * table, int key);
extern void    *hash_delete (hash_table * table, int key);
extern void    *hash_getfirst (void **pos, hash_table * table);
extern void    *hash_getnext (void **pos, hash_table * table);
extern void    *hashloc_init (hash_location * loc, hash_table * table);
extern void    *hashloc_getnext (hash_location * loc);
extern void    *hashloc_deletenext (hash_location * loc);


/*
 * hashloc_init starts by filling in the hash_location structure and
 * returning the first entry from the hash table. Thereafter, use
 * hashloc_getnext to get the next item in the table, or hashloc_deletenext
 * to delete the current entry, and then skip to the next item in the table
 * and return it.
 * 
 * Remember that even hashloc_init can return NULL, indicating no entries in the
 * table.
 * 
 * Do *not* combine hashloc_* with hash_* functions as the standard hash_*
 * functions may alter the structure of the table and thus invalidate the
 * contents of the hash_location structure.
 */
#endif				       /* HASH_H */
