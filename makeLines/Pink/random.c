#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int
main (void)
{
  srand(clock());
  int i = 0;
  int j = 0;
  FILE *fp = NULL;
  fp = fopen ("pink.ppm", "w");
  fprintf (fp, "P3\n");
  fprintf (fp, "1920 1080\n");
  fprintf (fp, "255\n");
  for (i = 0; i < 1080; i++)
    {
      for (j = 0; j < 1920; j++)
	{
	  fprintf (fp, " %d %d %d  ",rand()%256,rand()%256,rand()%256);
	}
      fprintf (fp,"\n");
    }
  fclose (fp);
}
