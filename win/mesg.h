#ifndef MESG_H
#define MESG_H	1
/*******************************************************************************
 * $Date: 1994/06/01 16:43:51 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/mesg.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: mesg.h,v $
 * Revision 1.6  1994/06/01  16:43:51  franklin
 * Do not nest include files.  Include other header files in the source code
 * which #includes this file.
 *
 * Revision 1.5  1994/05/03  00:54:56  franklin
 * Add prototypes for the functions defined in msg.c.
 * Use unistd.h instead of sys/types.h.
 *
 * Revision 1.4  1994/04/14  22:40:53  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.3  1994/04/14  18:26:27  franklin
 * Suppress ObjectCenter warnings about "static variable rcsid unused".
 *
 * Revision 1.2  1994/04/08  01:06:00  franklin
 * Run through the prettyprinter
 *
 ******************************************************************************/
#endif
static char    *mesg_h_rcsid = "@(#) $Id: mesg.h,v 1.6, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3, h4_3_2, h4_3_1, h4_3_0, h4_2_7, h4_2_6, h4_2_5, h4_2_4 1994/06/01 16:43:51 franklin Exp $";

/* #include <unistd.h> */
/* #include  <sys/types.h> */
/* #include  <sys/ipc.h> */
/* #include  <sys/msg.h> */

/* #include  <sys/errno.h> */
/* #include  "sunos4_missing.h" */

#define MKEY1    1234L
#define  PERMS   0666

#define MAXMESGDATA   4080	       /* (4096-16) */
typedef struct my_msgbuf_struct
{
	int             mesg_len;
	long            mesg_type;
	char            mesg_data[MAXMESGDATA];
}               Mesg;

#define MESGHDRSIZE   (sizeof(Mesg)-MAXMESGDATA)

extern void     mesg_send (int id, Mesg * mesgptr);
extern int      mesg_recv (int id, Mesg * mesgptr);
extern int      mesg_arecv (int id, Mesg * mesgptr);

#endif				       /* end if MESG_H not already defined. */
