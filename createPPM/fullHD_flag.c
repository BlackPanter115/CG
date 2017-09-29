#include <stdio.h>
int
main (void)
{
  int i = 0;
  int j = 0;
  printf ("P3\n");
  printf ("1366 768\n");
  printf ("255\n");
  for (i = 0; i < 768; i++)
    {
      for (j = 0; j < 1366; j++)
	{
	  if (j < 455)
	    printf (" 0 255 0  ");
	  else if (j < 911 && j >= 455 && (i < 256 || i >= 512))
	    printf ("  255 255 255  ");
	  else if (j < 911 && j >= 455 && i >= 256 && i < 512)
	    printf ("  102 52 0  ");
	  else if (j < 1366 && j >= 911)
	    printf ("  255 0 0");
	}
      printf ("\n");
    }
}
