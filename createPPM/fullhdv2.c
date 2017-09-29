#include <stdio.h>
int
main (void)
{
  int i = 0;
  int j = 0;
  FILE *fp = NULL;
  fp = fopen ("/home/blackpanter/CG/PPM/flag_auto.ppm", "w");
  fprintf (fp, "P3\n");
  fprintf (fp, "1920 1080\n");
  fprintf (fp, "255\n");
  for (i = 0; i < 1080; i++)
    {
      for (j = 0; j < 1920; j++)
	{
	  if (j < 640)
	    fprintf (fp, " 0 255 0  ");
	  else if (j < 1280 && j >= 640 && (i < 360 || i >= 720))
	    fprintf (fp, "  255 255 255  ");
	  else if (j < 1280 && j >= 640 && i >= 360 && i < 720)
	    fprintf (fp, "  102 52 0  ");
	  else if (j < 1920 && j >= 1280)
	    fprintf (fp, "  255 0 0");
	}
      fprintf (fp,"\n");
    }
  fclose (fp);
}
