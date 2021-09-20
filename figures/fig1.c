#include <stdio.h>

float PI = 3.14;
extern int b (void);

void oddsize_paramlist (float f)
{
	printf ("%f", f);
}
void a (void)
{
	oddsize_paramlist (PI);
}

int main (void)
{
	printf ("Calling a: ");   a();
	printf ("\nCalling b: "); b();
	printf ("\n");
	return(0);
}
