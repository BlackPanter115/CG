#include<stdio.h>
#include<stdlib.h>
#include"drawline.h"
#include<time.h>
int
main (void)
{
  srand (clock ());
  double slope;
  int i = 0;
  int j = 0;
  int k = 0;
  int **points;
  unsigned char ***raster;
  points = create_Points ();
  raster = create_raster ();
  for (i = 0; i < 1920; i++)
    for (j = 0; j < 1080; j++)
      for (k = 0; k < 3; k++)
	raster[i][j][k] = 0;
  for (i = 0; i < 10000; i++)
    {
      points[0][0] = rand () % 1920;
      points[0][1] = rand () % 1080;
      points[1][0] = rand () % 1900;
      points[1][1] = rand () % 1080;
      if (points[0][0] == points[1][0])	//ya esta
	{
	  printf("Points (%d,%d)->(%d,%d), Case Slope=inf\n",points[0][0],points[0][1],points[1][0],points[1][1]);
	  specialdrawX(points,raster);
	}
      else if (points[0][1] == points[1][1])	//ya esta
	{
	  printf("Points (%d,%d)->(%d,%d), Case Slope=0\n",points[0][0],points[0][1],points[1][0],points[1][1]);
	  specialdrawY(points,raster);
	}
      else
	{
	  slope =
	    (double) (points[1][1] - points[0][1]) / (points[1][0] -
						      points[0][0]);
	  printf ("\nSlope: %lf, ", slope);
	  if (slope > 1)	//ya esta
	    {
	      printf("Points (%d,%d)->(%d,%d), Case Slope>1\n",points[0][0],points[0][1],points[1][0],points[1][1]);
	      specialdrawPositive(points,raster);
	    }
	  else if (slope < -1)	//ya esta
	    {
	      printf ("Points (%d,%d)->(%d,%d), Case Slope<-1\n",
	              points[0][0], points[0][1], points[1][0], points[1][1]);
	      specialdrawNegative2 (points, raster);
	    }
	  else if ((slope < 0) && (slope > -1))	//ya esta
	    {
	      printf("Points (%d,%d)->(%d,%d), Case 0>Slope>-1\n",points[0][0],points[0][1],points[1][0],points[1][1]);
	      specialdrawNegative1(points,raster);
	    }
	  else if (slope == 1)	//ya esta
	    {
                printf("Points (%d,%d)->(%d,%d), Case Slope=1\n",points[0][0],points[0][1],points[1][0],points[1][1]);
                specialdrawM1(points,raster);
	    }
	  else if (slope == -1)	//ya esta
	    {
                printf("Points (%d,%d)->(%d,%d), Case Slope=-1\n",points[0][0],points[0][1],points[1][0],points[1][1]);
                specialdrawM2(points,raster);
	    }
	  else  //ya esta
	    {

	      printf("Points (%d,%d)->(%d,%d), Case 0<Slope<1\n",points[0][0],points[0][1],points[1][0],points[1][1]);
	      calculate_line(points,raster);
	    }
	}
    }
  draw (raster);
}
