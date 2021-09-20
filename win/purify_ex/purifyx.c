#include <stdlib.h>
#include <string.h>

static void     umr_and_free (char *leakedptr, char *freedptr,
			                      int *badidx)
{
    strcpy (freedptr, leakedptr);      /* umr */
    free (freedptr);
    *badidx = 2;
}
int             main (void)
{
    char           *leakedptr = malloc (2);
    char           *freedptr = malloc (2);
    char            bounderr[2];
    int             badidx;
    char            val;

    umr_and_free (leakedptr, freedptr, &badidx);
    val = (int) freedptr[0];	/* fmr */
    freedptr[0] = val;		/* fmw */
    bounderr[badidx] = val;	/* abw not detected */
    bounderr[1] = bounderr[badidx];	/* abr not detected */

    leakedptr[badidx] = val;	/* abw often detected */
    val = leakedptr[badidx];	/* abr often detected */
    return (int) val;		/* leakedptr never freed */
}
