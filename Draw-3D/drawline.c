#include <stdio.h>
#include <stdlib.h>
#include "drawline.h"

void
principalBresenhan (int **points, unsigned char ***raster)
{
  if (points[0][0] == points[1][0])	//ya esta
    specialdrawX (points, raster);
  else if (points[0][1] == points[1][1])	//ya esta
    specialdrawY (points, raster);
  else
    {
      double slope =
	(double) (points[1][1] - points[0][1]) / (points[1][0] -
						  points[0][0]);
      if (slope > 1)		//ya esta
	{
	  specialdrawPositive (points, raster);
	}
      else if (slope < -1)	//ya esta
	{
	  specialdrawNegative2 (points, raster);
	}
      else if ((slope < 0) && (slope > -1))	//ya esta
	{
	  specialdrawNegative1 (points, raster);
	}
      else if (slope == 1)	//ya esta
	{
	  specialdrawM1 (points, raster);
	}
      else if (slope == -1)	//ya esta
	{
	  specialdrawM2 (points, raster);
	}
      else			//ya esta
	{
	  calculate_line (points, raster);
	}
    }
}

int **
create_Points ()
{
  int **points;
  int i = 0;
  points = (int **) malloc (sizeof (int *) * 2);
  for (i = 0; i < 2; i++)
    {
      points[i] = (int *) malloc (sizeof (int) * 2);
    }
  return points;
}

unsigned char ***
create_raster ()
{
  unsigned char ***raster;
  int i = 0;
  int j = 0;
  raster = (unsigned char ***) malloc (sizeof (unsigned char **) * 1920);
  for (i = 0; i < 1920; i++)
    {
      raster[i] = (unsigned char **) malloc (sizeof (unsigned char *) * 1080);
    }
  for (i = 0; i < 1920; i++)
    {
      for (j = 0; j < 1080; j++)
	{
	  raster[i][j] =
	    (unsigned char *) malloc (sizeof (unsigned char) * 3);
	}
    }
  for (i = 0; i < 1920; i++)
    for (j = 0; j < 1080; j++)
      {
	raster[i][j][0] = 0;
	raster[i][j][1] = 0;
	raster[i][j][2] = 0;
      }
  return raster;
}

void
specialdrawX (int **points, unsigned char ***raster)
{
  int i = 0;
  int r = 255;
  int g = 255;
  int b = 255;
  if ((points[1][1] - points[0][1]) < 0)
    {
      for (i = points[1][1]; i <= points[0][1]; i++)
	{
	  put_pixel (points[0][0], i, raster, r, g, b);
	}
    }
  else
    {
      for (i = points[0][1]; i <= points[1][1]; i++)
	{
	  put_pixel (points[0][0], i, raster, r, g, b);
	}
    }
}

void
specialdrawY (int **points, unsigned char ***raster)
{
  int i = 0;
  int r = 255;
  int g = 255;
  int b = 255;
  if ((points[1][0] - points[0][0]) < 0)
    {
      for (i = points[1][0]; i <= points[0][0]; i++)
	{
	  put_pixel (i, points[0][1], raster, r, g, b);
	}
    }
  else
    {
      for (i = points[0][0]; i <= points[1][0]; i++)
	{
	  put_pixel (i, points[0][1], raster, r, g, b);
	}
    }
}

void
calculate_line (int **points, unsigned char ***raster)
{
  int r = 255;
  int g = 255;
  int b = 255;
  int aux = 0;
  int x = 0;
  int y = 0;
  int dx = 0;
  int dy = 0;
  int d = 0;
  int incE = 0;
  int incNE = 0;
  if ((points[1][0] - points[0][0]) < 0)
    {
      aux = points[0][0];
      points[0][0] = points[1][0];
      points[1][0] = aux;
      aux = points[0][1];
      points[0][1] = points[1][1];
      points[1][1] = aux;
    }
  put_pixel (points[0][0], points[0][1], raster, r, g, b);
  put_pixel (points[1][0], points[1][1], raster, r, g, b);
  dx = points[1][0] - points[0][0];
  dy = points[1][1] - points[0][1];
  d = (2 * dy) - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  y = points[0][1];
  for (x = points[0][0] + 1; x < points[1][0]; x++)
    {
      if (d <= 0)
	{
	  d += incE;
	}
      else
	{
	  d += incNE;
	  y++;
	}
      put_pixel (x, y, raster, r, g, b);
    }
}

void
specialdrawPositive (int **points, unsigned char ***raster)
{
  int r = 255;
  int g = 255;
  int b = 255;
  int x = 0;
  int y = 0;
  int dx = 0;
  int dy = 0;
  int d = 0;
  int aux = 0;
  int incE = 0;
  int incNE = 0;
  put_pixel (points[0][0], points[0][1], raster, r, g, b);
  put_pixel (points[1][0], points[1][1], raster, r, g, b);
  if ((points[1][1] - points[0][1]) < 0)
    {
      aux = points[0][0];
      points[0][0] = points[1][0];
      points[1][0] = aux;
      aux = points[0][1];
      points[0][1] = points[1][1];
      points[1][1] = aux;
    }
  dx = points[1][1] - points[0][1];
  dy = points[1][0] - points[0][0];
  d = (2 * dy) - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  y = points[0][0];
  for (x = points[0][1] + 1; x < points[1][1]; x++)
    {
      if (d <= 0)
	{
	  d += incE;
	}
      else
	{
	  d += incNE;
	  y++;
	}
      put_pixel (y, x, raster, r, g, b);
    }
}

void
specialdrawNegative1 (int **points, unsigned char ***raster)
{
  int r = 255;
  int g = 255;
  int b = 255;
  int aux = 0;
  int x = 0;
  int y = 0;
  int dx = 0;
  int dy = 0;
  int d = 0;
  int incE = 0;
  int incNE = 0;
  if ((points[1][0] - points[0][0]) < 0)
    {
      aux = points[0][0];
      points[0][0] = points[1][0];
      points[1][0] = aux;
      aux = points[0][1];
      points[0][1] = points[1][1];
      points[1][1] = aux;
    }
  put_pixel (points[0][0], points[0][1], raster, r, g, b);
  put_pixel (points[1][0], points[1][1], raster, r, g, b);
  aux = points[1][1];
  points[1][1] = points[0][1];
  points[0][1] = aux;
  dx = (points[1][0] - points[0][0]);
  dy = (points[1][1] - points[0][1]);
  d = (2 * dy) - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  y = points[0][1];
  for (x = points[1][0] - 1; x > points[0][0]; x--)
    {
      if (d <= 0)
	{
	  d += incE;
	}
      else
	{
	  d += incNE;
	  y++;
	}
      put_pixel (x, y, raster, r, g, b);
    }
}

void
specialdrawNegative2 (int **points, unsigned char ***raster)
{
  int r = 255;
  int g = 255;
  int b = 255;
  int aux = 0;
  int x = 0;
  int y = 0;
  int dx = 0;
  int dy = 0;
  int d = 0;
  int incE = 0;
  int incNE = 0;
  if ((points[1][0] - points[0][0]) < 0)
    {
      aux = points[0][0];
      points[0][0] = points[1][0];
      points[1][0] = aux;
      aux = points[0][1];
      points[0][1] = points[1][1];
      points[1][1] = aux;
    }
  put_pixel (points[0][0], points[0][1], raster, r, g, b);
  put_pixel (points[1][0], points[1][1], raster, r, g, b);
  aux = points[1][1];
  points[1][1] = points[0][1];
  points[0][1] = aux;
  dx = (points[1][1] - points[0][1]);
  dy = (points[1][0] - points[0][0]);
  d = (2 * dy) - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  y = points[0][0];
  for (x = points[1][1] - 1; x > points[0][1]; x--)
    {
      if (d <= 0)
	{
	  d += incE;
	}
      else
	{
	  d += incNE;
	  y++;
	}
      put_pixel (y, x, raster, r, g, b);
    }
}

void
specialdrawM1 (int **points, unsigned char ***raster)
{
  int r = 255;
  int g = 255;
  int b = 255;
  int i = 0;
  int j = 0;
  int aux = 0;
  if ((points[1][0] - points[0][0]) < 0)
    {
      aux = points[0][0];
      points[0][0] = points[1][0];
      points[1][0] = aux;
      aux = points[0][1];
      points[0][1] = points[1][1];
      points[1][1] = aux;
    }
  for (i = points[0][0], j = points[0][1]; i < points[1][0]; i++, j++)
    put_pixel (i, j, raster, r, g, b);
}

void
specialdrawM2 (int **points, unsigned char ***raster)
{
  int r = 255;
  int g = 255;
  int b = 255;
  int i = 0;
  int j = 0;
  int aux = 0;
  if ((points[1][0] - points[0][0]) < 0)
    {
      aux = points[0][0];
      points[0][0] = points[1][0];
      points[1][0] = aux;
      aux = points[0][1];
      points[0][1] = points[1][1];
      points[1][1] = aux;
    }
  for (i = points[0][0], j = points[0][1]; i < points[1][0]; i++, j--)
    put_pixel (i, j, raster, r, g, b);
}

void
put_pixel (int x1, int y1, unsigned char ***raster, int r, int g, int b)
{
  raster[x1][y1][0] = r;
  raster[x1][y1][1] = g;
  raster[x1][y1][2] = b;
}

void
draw (unsigned char ***raster, char *name)
{
  int j = 0;
  int i = 0;
  FILE *fp = NULL;
  fp = fopen (name, "w");
  fprintf (fp, "P3\n");
  fprintf (fp, "1920 1080\n");
  fprintf (fp, "255\n");
  for (i = 1079; i >= 0; i--)
    {
      for (j = 0; j < 1920; j++)
	{
	  fprintf (fp, "  %d %d %d  ", raster[j][i][0], raster[j][i][1],
		   raster[j][i][2]);
	}
      fprintf (fp, "\n");
    }
  fclose (fp);
}
