#include<stdio.h>
#include<stdlib.h>
#include"drawline.h"

int
main ()
{
  int **raster = NULL;
  int width = 0;
  int height = 0;
  int **points = NULL;
  printf ("insert the dimensions of the raster\n");
  printf ("width:");
  scanf ("%d", &width);
  printf ("height:");
  scanf ("%d", &height);
  raster = createRaster (width, height);
  printf ("Raster Created, dimensions: %dX%d\n", width, height);
  points = obtainPoints ();
  printf ("the points are (%d,%d) and (%d,%d)\n", points[0][0],
	  points[0][1], points[1][0], points[1][1]);
  calculate_line(points,raster);
  draw(raster,width, height);
}
