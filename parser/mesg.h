/*******************************************************************************
 * $Date: 1994/04/14 22:40:53 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/mesg.h,v $
 *
 **-M**************************************************************************/
#if 0
/******************************************************************************
 *
$Log: mesg.h,v $
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
static char	*mesg_h_rcsid = "@(#) $Id: mesg.h,v 1.4 1994/04/14 22:40:53 franklin Exp $";

#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/msg.h>

#include  <sys/errno.h>
extern int      errno;

#define MKEY1    1234L
#define  PERMS   0666

#define MAXMESGDATA   4080	       /* (4096-16) */
typedef struct my_msgbuf
{
	int             mesg_len;
	long            mesg_type;
	char            mesg_data[MAXMESGDATA];
}               Mesg;

#define MESGHDRSIZE   (sizeof(Mesg)-MAXMESGDATA)
