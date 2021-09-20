#ifndef	SOME_UTILS_H
#define	SOME_UTILS_H	1
/*******************************************************************************
 * HEADER:      SOME_UTILS.H
 *
 * PURPOSE:     Contains declarations of external functions defined in
 *		some_utils.c
 *
 * CREATED:     4/12/1994
 *
 * AUTHOR:      Malcolm L. Franklin, Arizona State University
 *
 * NOTE:	Requires <stdlib.h>, <stdio.h> and <stdarg.h>.
 *******************************************************************************
 * $Date: 1994/08/05 21:49:15 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/some_utils.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: some_utils.h,v $
 * Revision 1.12  1994/08/05  21:49:15  franklin
 * Allow const char pointers to be passed to
 * growbuf_strcpy() and growbuf_strcat().
 *
 * Revision 1.11  1994/08/03  16:00:02  franklin
 * Changed "unsigned long" to "unsigned long int" to shut up a
 * CodeCheck diagnostic.
 *
 * Revision 1.10  1994/08/02  13:33:24  franklin
 * isqempty -> qisempty (prefix "is" is reserved by ctype.h)
 *
 * Revision 1.9  1994/08/01  23:33:16  franklin
 * Suffix _t is reserved by POSIX.  Change growbuf_t to growbuf_tt.
 *
 * Revision 1.8  1994/07/06  04:58:12  franklin
 * Added. get_base_filename().
 *
 * Revision 1.7  1994/07/05  02:04:21  franklin
 * Added function "load_file_into_charbuf()" for reading a file
 * into a character buffer in heap storage.
 *
 * Revision 1.6  1994/05/21  20:47:08  franklin
 * Add the "growbuf" utilities, for storing/appending strings of arbitrary
 * length.  The buffer grows as more space is needed.
 *
 * Revision 1.5  1994/05/13  22:12:38  franklin
 * Add util_abort(), and run through SunOS "indent" utility.
 *
 * Revision 1.4  1994/04/24  00:52:41  franklin
 * Add a function to print integer values in binary format.
 *
 * Revision 1.3  1994/04/14  22:48:23  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.2  1994/04/14  18:26:41  franklin
 * Suppress ObjectCenter warnings about "static variable rcsid unused".
 *
 * Revision 1.1  1994/04/12  07:41:46  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *some_utils_h_rcsid = "@(#) $Id: some_utils.h,v 1.12, h4_3_8, h4_3_7, h4_3_6, h4_3_5 1994/08/05 21:49:15 franklin Exp $";

typedef int     SDATA;

struct qlinked_list
{
	SDATA           d;
	struct qlinked_list *next;
};

typedef struct qlinked_list SELEMENT;
typedef SELEMENT *SLINK;

struct queue
{
	SLINK           front;
	SLINK           rear;
};

typedef struct queue QUEUE;

typedef struct growbuf_t_struct
{
	size_t          cur_len;
	char           *buf;
}               growbuf_tt;

extern void     util_abort (int line, char *file, char *printf_fmt_str,...);

extern int      qisempty (QUEUE * q);
extern SDATA    vfront (QUEUE * q);
extern void     dequeue (QUEUE * q, SDATA * x);
extern void     enqueue (QUEUE * q, SDATA x);

extern void     dump_bits (FILE * outf, unsigned long int val);

extern void     growbuf_init (growbuf_tt ** gbuf);
extern void     growbuf_strcpy (growbuf_tt * gbuf, const char *in_str);
extern void     growbuf_strcat (growbuf_tt * gbuf, const char *in_str);
extern char    *growbuf_str (growbuf_tt * gbuf);
extern void     growbuf_free (growbuf_tt ** gbuf);
extern const char *get_base_filename (const char *fullpathname);
extern char    *load_file_into_charbuf (const char *pathname, int *len);

#endif				       /* some_utils.h hasnt already been #included. */
