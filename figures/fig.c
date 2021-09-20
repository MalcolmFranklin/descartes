#include <stdio.h>
float PI = 3.14;
int b ()
{
	int oddsize_paramlist();
	oddsize_paramlist (PI);
}
int oddsize_paramlist (float f)
{
	printf ("%f", f);
	return (1);
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
