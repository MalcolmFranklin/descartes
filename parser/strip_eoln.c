/******************************************************************************
*
*	STRIP_EOLN.C
*
*	Strips non-printable characters and newlines from stdin, writes
*	printable chars to stdout.  If a nonprintable character is encountered,
*	write a message to stderr.
*
*	Written:		7/12/1989
*
*	Author:			Malcolm L. Franlin, ASIC CAD Integration
*				Test Group.
*
*	Last Modified:
*
*******************************************************************************/

#include <stdio.h>

#define		LEAST_PRINTABLE		 32 
#define		GREATEST_PRINTABLE	127
#define		CR			 13
#define		LF			 10
#define		TAB			  9


main ()
{
	int  ch;

	while ( (ch = getchar() ) != EOF ) 
	{

		if ( ( (ch >= LEAST_PRINTABLE) && (ch <= GREATEST_PRINTABLE) )
		     || ( ch == TAB ) )

			putchar ( ch );

		else
			fprintf ( stderr, "\nNonprintable %d (decimal) %X (hex)", ch, ch );

	} /* while not end of stdin */

} /* end main() */
