#include<stdio.h>
#include<stdlib.h>
#include"drawline.h"


int **
createRaster (int width, int height)
{
  int **raster;
  int i = 0;
  int j = 0;
  raster = (int **) malloc (sizeof (int *) * width);
  for (i = 0; i < width; i++)
    {
      raster[i] = (int *) malloc (sizeof (int) * height);
    }
  for (i = 0; i < width; i++)
    {
      for (j = 0; j < height; j++)
	{
	  raster[i][j] = 0;
	}
    }
  return raster;
}

int **
obtainPoints ()
{
  int **points;
  int i = 0;
  int replay = 1;
  int replay2 = 0;
  char option = '\0';
  points = (int **) malloc (sizeof (int *) * 2);
  for (i = 0; i < 2; i++)
    {
      points[i] = (int *) malloc (sizeof (int) * 2);
    }
  while (replay)
    {
      printf ("Insert the points where the line passed it\n");
      printf ("X0=");
      scanf ("%d", &points[0][0]);
      printf ("Y0=");
      scanf ("%d", &points[0][1]);
      printf ("X1=");
      scanf ("%d", &points[1][0]);
      printf ("Y1=");
      scanf ("%d", &points[1][1]);
      getchar ();
      if (points[0][0] == points[1][0])
	{
	  printf ("Error, Insert a valid X values");
	  replay2 = 0;
	}
      else
	{
	  replay2 = 1;
	}
      while (replay2)
	{
	  printf ("the points are ok?\n1)yes	2)no\n");
	  option = getchar ();
	  if (option == '1')
	    {
	      replay = 0;
	      replay2 = 0;
	    }
	  else if (option != '2')
	    {
	      printf ("please insert an a valid option\n");
	    }
	  else
	    {
	      replay2 = 0;
	    }
	}
    }
  return points;
}

void
calculate_line(int **points, int **raster)
{
  int x=0;
  int y=0;
  int dx=0;
  int dy=0;
  int d=0;
  int incE=0;
  int incNE=0;
  x=points[0][0];
  y=points[0][1];
  put_pixel(x,y,raster);
  
  dx=points[1][0]-points[0][0];
  dy=points[1][1]-points[0][1];
  d=(2*dy)-dx;
  incE=2*dy;
  incNE=2*(dy-dx);
  for(x=points[0][0]+1;x<points[1][0];x++)
  {
    if(d<=0)
    {
      d+=incE;
    }
    else
    {
      d+=incNE;
      y++;
    }
    put_pixel(x,y,raster);
  }
  x=points[1][0];
  y=points[1][1];
  put_pixel(x,y,raster);
}

void
put_pixel(int x, int y, int **raster)
{
  raster[x][y]=1;
}

void
draw(int **raster,int width,int height)
{
int i=0;
int j=0;
  for(i=0;i<height;i++)
  {
    for(j=width-1;j>=0;j--)
    {
      if(raster[i][j]==1)
        printf("*");
      else
        printf(" ");
    }
    printf("\n");
  }
}
