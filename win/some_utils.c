/*******************************************************************************
 * MODULE:      SOME_UTILS.C
 *
 * PURPOSE:     Implementation of queues taken from analysis1.c.  Moved to
 *		this file to improve modularity.
 *
 * AUTHOR:      Believed to bi Lih-Shiun Timothy Lee of Arizona State University
 *******************************************************************************
 * $Date: 1994/08/05 21:49:57 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/some_utils.c,v $
 *
 **-M**************************************************************************/

#if 0
/******************************************************************************
 *
$Log: some_utils.c,v $
 * Revision 1.17  1994/08/05  21:49:57  franklin
 * Allow const char pointers to be passed to
 * growbuf_strcpy() and growbuf_strcat().
 *
 * Revision 1.16  1994/08/04  22:36:00  franklin
 * workaround CodeCheck inability to handle ANSI variable argument lists.
 *
 * Revision 1.15  1994/08/04  18:03:02  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.14  1994/08/03  15:59:11  franklin
 * Changed "unsigned long" to "unsigned long int" to shut up a
 * CodeCheck diagnostic.
 *
 * Revision 1.13  1994/08/02  13:33:52  franklin
 * isqempty -> qisempty (prefix "is" is reserved by ctype.h)
 *
 * Revision 1.12  1994/08/01  23:32:47  franklin
 * Suffix _t is reserved by POSIX.  Change growbuf_t to growbuf_tt.
 *
 * Revision 1.11  1994/07/31  21:49:46  franklin
 * Fix a spurious Purify(tm) uninitialized memory read error, caused by
 * "strlen()" fetching a full word at a time, versus a byte at a time, while
 * searching for the null terminator of a string.
 *
 * Revision 1.10  1994/07/30  23:43:37  franklin
 * Fix an uninitialized memory read detected by Purify.  The
 * umr occured when you executed growbuf_strcpy (gbuf, "");
 *
 * Revision 1.9  1994/07/06  04:56:50  franklin
 * Add a function to return a pointer to "fred.stuff" when passed
 * a pointer to "/all/me/you/fred.stuff" (get_base_filename())
 *
 * Revision 1.8  1994/07/05  02:03:38  franklin
 * Added function "load_file_into_charbuf()" for reading a file
 * into a character buffer in heap storage.
 *
 * Revision 1.7  1994/06/02  17:24:35  franklin
 * Enable stricter type checking when running the CenterLine "clcc" in
 * K&R compatibility mode (-Xa switch) by re-defining __STDC__ after processing
 * the non-ansi SunOS system include files.
 *
 * Revision 1.6  1994/05/24  02:06:36  franklin
 * Cast pointer returned by calloc() to the proper type.
 *
 * Revision 1.5  1994/05/21  20:45:00  franklin
 * Add the "growbuf" utilities, for storing/appending strings of arbitrary
 * length.  The buffer grows as more space is needed.
 *
 * Revision 1.4  1994/05/13  22:12:13  franklin
 * Add util_abort(), and run through SunOS "indent" utility.
 *
 * Revision 1.3  1994/04/24  00:53:09  franklin
 * Add a function to print integer values in binary format.
 *
 * Revision 1.2  1994/04/23  16:15:09  franklin
 * Get the declarations of "free()" and "printf()" from system header files.
 *
 * Revision 1.1  1994/04/12  07:41:09  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char    *rcsid = "$Id: some_utils.c,v 1.17, h4_3_8, h4_3_7, h4_3_6, h4_3_5 1994/08/05 21:49:57 franklin Exp $";

#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stdarg.h>
#include "cchk_missing_stdarg.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
/******************************************************************************
 * NOTE TO FUTURE MAINTAINERS USING CenterLine "clcc" COMPILER:
 *
 * Nearly all the SunOS 4.x Operating System include files (<sys/xxx.h>)
 * cause compilation errors under a strict ANSI/ISO compiler running in anal-
 * retentive mode such as CenterLine "clcc".  In order to get these to compile,
 * with clcc, you have to pass the  -Xa (K&R C compatibility switch) to the
 * compiler.  BUT (get this) when we do this, the CenterLine preprocessor
 * #defines __STDC__ to 0 (zero); when this happens, we dont see the vararg
 * prototypes for the X functions -- and get warning messages for calling them
 * with different numbers of arguments.  On top of all this noise, we DONT GET
 * all the ANSI/ISO C type checking that we could have.
 *
 * WORKAROUND:
 *      When compiling with clcc, #define __STDC__ to 1 AFTER #including the
 * system header files you need (<sys/xxx.h>), and hopefully before #including
 * any of the header files you (or I, or Yu-Kuh, or someone else) wrote.
 * Here is the code:
 ******************************************************************************/

#ifdef __CLCC__

#ifdef __STDC__
#undef __STDC__
#endif

#define __STDC__ 1
#endif

#include "some_utils.h"

/*******************************************************************************
 *******************************************************************************
 ** QUEUE UTILITIES
 **
 **	comprized of:	qisempty();	vfront();	dequeue();
 **			enqueue();
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION:	QISEMPTY
 *	Return 1 if q is empty; otherwise return 0
 ******************************************************************************/
int             qisempty (QUEUE * q)
{
	if (q->front == NULL)
		return (1);
	else
		return (0);
}

/*******************************************************************************
 * FUNCTION:	VFRONT
 *	Return the value if the first element
 ******************************************************************************/
SDATA           vfront (QUEUE * q)
{
	return (q->front->d);

}

/*******************************************************************************
 * FUNCTION:	DEQUEUE
 *	Return the value if the first element and remove it
 ******************************************************************************/
void            dequeue (QUEUE * q, SDATA * x)
{
	SLINK           temp = q->front;

	if (!qisempty (q))
	{
		printf ("before dqueue\n");
		*x = temp->d;
		printf ("before dqueue\n");
		q->front = temp->next;
		free (temp);
	}
	else
		printf ("empty  queue. \n");

}

/*******************************************************************************
 * FUNCTION:	ENQUEUE
 *	Place the value d onto the rear of q
 ******************************************************************************/
void            enqueue (QUEUE * q, SDATA x)
{
	SLINK           temp;

	printf ("before enqueue\n");
	temp = (SLINK) malloc (sizeof (SELEMENT));
	printf (" enqueue\n");
	temp->d = x;
	temp->next = 0;

	if (qisempty (q) == 1)
	{
		q->front = q->rear = temp;
		printf ("empty\n");
	}
	else
	{
		q->rear->next = temp;
		q->rear = temp;
		printf ("not empty\n");
	}
	printf (" after enqueue\n");
}

/*******************************************************************************
 *******************************************************************************
 ** DUMP_BITS_UTILITY
 **
 **	comprized of only 1 function: dump_bits()
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION:	DUMP_BITS
 *
 * PURPOSE:	Prints integers to a given file in binary format.
 *		The input value is declared to be of type unsigned long int,
 *		so that it can work for any size integer value you want (int,
 *		long, or short).
 *
 * PARAMETERS
 *	INPUT:	outf  -- Output file
 * 		val   -- Value you want to print
 *
 * USE:
 *	dump_bits (stdout, 1 | 8) writes the following to stdout():
 *		1001
 *
 *	dump_bits (stdout, 1 << 31) writes the following to stdout (provided
 *	words are at least 32 bits wide on your machine).
 *
 *	1000 0000 0000 0000 0000 0000 0000 0000 0000
 ******************************************************************************/
void            dump_bits (FILE * outf, unsigned long int val)
{
	static int      bits_per_word = 0;
	unsigned long int bits_to_go;
	unsigned long int mask;
	int             count;

/*
 * On the first call to this function, compute how many bits are in an
 * unsigned long int.  (I assume that there will be a nonzero number of bits
 * in a word.
 */

	if (bits_per_word == 0)
	{
		bits_to_go = ULONG_MAX;
		while (bits_to_go)
		{
			++bits_per_word;
			bits_to_go >>= 1;
		}
	}

/*
 * Set only the most-significant-bit in "mask".  We'll shift the set bit in
 * mask from the most-significant-bit to the least significant bit.
 */
	mask = 1 << (bits_per_word - 1);
	count = 0;

/*
 * Skip past any leading groups of four '0' bits ("0000"). so you print
 * decimal 9 as  "0001 0000", and decimal 2 as "0010".  Always print at least
 * one group of zeros (zero should print as "0000", not a null string).
 */
	while ((count < (bits_per_word - 4)) &&
			!(val & (0xF << (bits_per_word - (count + 4)))))
	{
		count += 4;
		mask >>= 4;
	}

	while (mask)
	{
		if (mask & val)
			fputc ('1', outf);
		else
			fputc ('0', outf);

	/* Print a space between each group of 4 bits. */
		++count;
		if ((count < bits_per_word) && ((count % 4) == 0))
			fputc (' ', outf);

		mask >>= 1;
	}
}

/*******************************************************************************
 *******************************************************************************
 ** GROWBUF UTILITIES:
 **
 **	comprized of:	growbuf_init() 	growbuf_strcpy()	growbuf_strcat()
 **			growbuf_strcpy()growbuf_str()		free_growbuf()
 **
 ** PURPOSE:	Implement a character buffer, which grows to the size of the
 **		largest object stored in it.  Useful for making a copy of a
 **		string whose size is not known until runtime.
 **
 ** USE:	You must initialize the new growbuf_tt objects by calling
 **		growbuf_init().  Example usage of the growbuf functions:
 **
 **			char *unknown_len_str;
 **			growbuf_tt *gbuf;
 **
 **			growbuf_init (&gbuf);
 **			while (get_unknown_len_str(unknown_len_str))
 **			{
 **				growbuf_strcpy(gbuf, unknown_len_str);
 **				printf("growbuf_str(gbuf) == \"%s\%\n",
 **							growbuf_str(gbuf));
 **			}
 **			growbuf_free (&gbuf);
 **
 **		If you want to keep a pointer to the string stored in the
 **		growbuf, then manually free the growbuf_tt struct when you
 **		are finished with it, and do NOT call growbuf_free():
 **
 **			growbuf_init (&gbuf);
 **				...
 **			keep_str = growbuf_str(gbuf);
 **			free(gbuf)
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION:	GROWBUF_INIT
 *	Initializes a new growbuf.  You MUST call this function on each growbuf
 *	BEFORE calling any of the other growbuf functions.
 *
 * NOTE:        Users only declare POINTERS to growbuf_tt structures; pass the
 *              address of the pointer to this function.
 *
 * USE:         growbuf_tt *my_gbuf;
 *              growbuf_init (&my_gbuf);
 ******************************************************************************/
void            growbuf_init (growbuf_tt ** gbuf)
{
/* Calloc initializes (*gbuf)->cur_len to zero and (*gbuf)->buf to NULL. */
	*gbuf = (growbuf_tt *) calloc (1, sizeof (growbuf_tt));
	if (*gbuf == NULL)
	{
		util_abort (__LINE__, __FILE__, "growbuf_init() could not calloc() storage for a growbuf_tt struct.\n"
			    "sizeof (growbuf_tt) == %d\n", sizeof (growbuf_tt));
	}
}

/*******************************************************************************
 * FUNCTION:	GROWBUF_STR
 *	Returns a pointer to the character string stored in the growbuf.
 ******************************************************************************/
char           *growbuf_str (growbuf_tt * gbuf)
{
	return (gbuf->buf);
}

/*******************************************************************************
 * FUNCTION:	GROWBUF_FREE
 *	frees dynamically-allocated storage referenced by the growbuf_tt
 *	buffer, and the storage for the growbuf_tt strucure itself.
 *
 * NOTE:        Users only declare POINTERS to growbuf_tt structures; pass the
 *              ADDRESS of the pointer to this function.
 *
 * USE:         growbuf_tt *my_gbuf;
 *              growbuf_free (&my_gbuf);
 ******************************************************************************/
void            growbuf_free (growbuf_tt ** gbuf)
{
	free ((*gbuf)->buf);
	free (*gbuf);
	*gbuf = NULL;		/* Do not leave a pointer into de-allocated memory. */
}


/*******************************************************************************
 * FUNCTION:	GROW_THE_BUFFER
 *
 * PURPOSE:	Ensure that gbuf->buf is pointing to a buffer large enough to
 *		hold the arbirary-length string passed to this function.
 *
 * NOTE:	This is an INTERNAL function to the growbuf routines.  It is
 *		not intended for use by user code.
 *
 *		This function allways assumes you are appending a string to
 *		the growstrings buffer.  If you want to replace the string
 *		pointed to by gbuf->buf, then set gbf->buf[0] == '\0' before
 *		calling this function.
 ******************************************************************************/
static void     grow_the_buffer (growbuf_tt * gbuf, const char *in_str)
{
	const size_t    increment = 32;/* Grow the buffer in 32 byte increments. */
	size_t          desired_len;

/*
 * If no storage has been allocated for gbuf->buf, or if we are copying,
 * rather than appending a string to the buffer.
 */
	if ((gbuf->buf == NULL) || (gbuf->buf[0] == '\0'))
	{
		desired_len = strlen (in_str);
	}
	else
	{
		desired_len = strlen (in_str) + strlen (gbuf->buf);
	}

/*
 * Do not increase the buffer size unless you have to.  Leave room for the
 * '\0' terminator.
 */
	while ((desired_len + 1) > gbuf->cur_len)
	{

	/*
	 * Even though the ANSI/ISO C standard says that realloc() will
	 * return a newly-allocated block when passed a NULL pointer, several
	 * UNIX systems do not support this.  Manually allocate new buffers.
	 */

		if (gbuf->buf == NULL)
		{
			gbuf->cur_len = 0;
			if ((gbuf->buf = malloc ((increment + 1))) == NULL)
			{
				util_abort (__LINE__, __FILE__, "growbuf() failed to allocate new storage for gbuf.\n");
			}

		/*
		 * Workaround for a spurious Purify(tm) umr message.  You
		 * must initialize a full word of buf to '\0' to prevent a
		 * false umr error when calling strlen() on a newly created
		 * growbuf->buf string.
		 */
			memset (gbuf->buf, 0, sizeof (int));
		}
		gbuf->cur_len += increment;
		if ((gbuf->buf = realloc (gbuf->buf, (gbuf->cur_len + 1))) == NULL)
		{
			util_abort (__LINE__, __FILE__, "growbuf() failed to get more memory for your buffer via realloc().\n"
				    "buffer at 0x%X; length attempted = %d, desired length = %d\n"
				    "increment = %d.\n", gbuf->buf, gbuf->cur_len, desired_len, increment);
		}
	}
}

/*******************************************************************************
 * FUNCTION:	GROWBUF_STRCPY
 *
 * PURPOSE:	Copy a string of arbitrary length to gbuf->buf;  overwrite any
 *		data previously written to the buffer.
 *
 * PARAMETERS
 *	INPUT:	growbuf_tt *gbuf -- A pointer to your growbuf struct
 *		char *in_str    -- A pointer to the string that you want to
 *                                 store in the buffer.
 ******************************************************************************/
void            growbuf_strcpy (growbuf_tt * gbuf, const char *in_str)
{

/*
 * If storage for gbuf->buf has already been allocated, then zap the string
 * stored in gbuf->buf, because grow_the_buffer() assumes you want to append
 * in_str to gbuf->buf.
 */
	if (gbuf->buf != NULL)
	{
		gbuf->buf[0] = '\0';
	}
	grow_the_buffer (gbuf, in_str);
	gbuf->buf[0] = '\0';	/* grow_the_buffer() may have just malloc()ed gbuf->buf for the first time. */
	strcpy (gbuf->buf, in_str);
}

/*******************************************************************************
 * FUNCTION:	GROWBUF_STRCAT
 *
 * PURPOSE:	Append a string of arbitrary length to the strina stored in
 *		gbuf->buf.
 *
 * PARAMETERS
 *	INPUT:	growbuf_tt *gbuf -- A pointer to your growbuf struct
 *		char *in_str    -- A pointer to the string that you want to
 *                                 store in the buffer.
 ******************************************************************************/
void            growbuf_strcat (growbuf_tt * gbuf, const char *in_str)
{
	grow_the_buffer (gbuf, in_str);
	strcat (gbuf->buf, in_str);
}

/*******************************************************************************
 *******************************************************************************
 ** FILE UTILITY
 **
 **	comprized of:	get_base_filename();
 **			load_file_into_charbuf();
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION:	GET_BASE_FILENAME
 *
 * PURPOSE:	Return the name of the file, without the path to it.  Returns
 *		NULL if passed a null pointer, otherwise returns a pointer in
 *		to the string you passed to it.
 ******************************************************************************/
const char     *get_base_filename (const char *fullpathname)
{
	const char     *fname;

	if (fullpathname)
	{
		fname = fullpathname + strlen (fullpathname) - 1;
		if (fname < fullpathname)	/* if fullpathname points to a zero-length string */
		{
			fname = fullpathname;
		}
		else
		{
		/* Search for a directory separator character. */
			while ((fname >= fullpathname) && (*fname != '/'))
				--fname;
			if (*fname == '/')
				++fname;
		}
	}
	else
	{
		fname = NULL;
	}
	return (fname);
}

/*******************************************************************************
 * FUNCTION:	LOAD_FILE_INTO_CHARBUF
 *
 * PURPOSE:	Reads the contents of a file into a character array.
 *
 * PARAMETERS:
 *	INPUT:	char *pathname -- Name of a file that IS NOT being read/
 *				  written to by anyone else.
 *
 * RETURNS:	NULL if it cannot open the file, or get memory from the heap.
 *
 * WARNING:	Caller must free() the pointer passed back from this function
 *
 ******************************************************************************/
char           *load_file_into_charbuf (const char *pathname, int *len)
{
	FILE           *infile;
	int             filesize;
	char           *file_contents;

	file_contents = NULL;
	filesize = 0;

	if ((infile = fopen (pathname, "rb")) != NULL)
	{
		fseek (infile, 0L, SEEK_END);
		filesize = ftell (infile);
		rewind (infile);
		if ((file_contents = malloc (filesize + 1)) != NULL)
		{
			if (fread (file_contents, 1, filesize, infile) == filesize)
				file_contents[filesize] = '\0';
			else
			{
				free (file_contents);
				file_contents = NULL;
			}
		}
		fclose (infile);
	}
	*len = filesize;
	return (file_contents);
}

/*******************************************************************************
 *******************************************************************************
 ** ABORT UTILITIY:
 **
 **	comprized of only 1 function:	util_abort();
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 * Function:    UTIL_ABORT
 *
 *      Use to kill the program and leave a traceback stack.  This is intended
 *      for errors such as malloc() failures, or garbled datatypes, that
 *      prevent all hope of recovery, and leave no chance of producing anything
 *      resembling meaningful results.
 *
 *	USAGE:
 *	if ( (ptr=malloc(...)) == NULL )
 *		util_abort ( __LINE__, __FILE__, "malloc() failed. ptr == %X\n", ptr );
 *
 *      printf_fmt_str and any additional parameters behave like printf(), and
 *	use printf() format and escape sequences.
 ******************************************************************************/
void            util_abort (int line, char *file, char *printf_fmt_str,...)
{
	va_list         arguments;

	va_start (arguments, printf_fmt_str);
	fflush (stdout);
	fprintf (stderr, "\n*---- Aborting on line %d of file \"%s\". ----*\nReason:\n", line, file);
	fflush (stderr);
	vfprintf (stderr, printf_fmt_str, arguments);
	fflush (stderr);
	abort ();
	va_end (arguments);
}
