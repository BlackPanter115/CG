//ffmpeg  avconv
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "drawline.h"
#include "3d.h"
#include "faceHiding.h"

static const double f = 35;
static const double width = 1920 / 2;
static const double height = 1080 / 2;

void
principal3d (struct vertex *vertexList,struct edge *edgeList,struct face *faceList,int nVertexList,int nEdgeList,int nFaceList, char *name)
{
  srand (clock ());
  double alfa = ((double) (rand () % 101) / 50) * M_PI;
  double beta = ((double) (rand () % 101) / 50) * M_PI;
  double gamma = ((double) (rand () % 101) / 50) * M_PI;
  printf ("alfa=%lf,beta=%lf,gamma=%lf\n", alfa, beta, gamma);
  struct points *coto = centerOfTheObject (vertexList, nVertexList); 
  translation (vertexList, nVertexList, coto);
  rotationX (vertexList, nVertexList, alfa);
  rotationY (vertexList, nVertexList, beta);
  rotationZ (vertexList, nVertexList, gamma);
  returnTranslation (vertexList, nVertexList, coto);
  translateAndProject (vertexList, nVertexList, coto);
  fh(faceList,nFaceList);
  transform_3D (vertexList, nVertexList);
  scaleAndTraslation (vertexList, nVertexList);
  draw3D (faceList, nFaceList, name);//<--aqui voy(con respecto a las modificaciones);
}

struct points *
centerOfTheObject (struct vertex *vertexList,int nVertexList)
{
  int i = 0;
  struct points *coto = (struct points *) malloc (sizeof (struct points) * 1);
  coto->x = 0;
  coto->y = 0;
  coto->z = 0;
  coto->w = 1;
  for (i = 0; i < nVertexList; i++)
    {
      coto->x += vertexList[i].x;
      coto->y += vertexList[i].y;
      coto->z += vertexList[i].z;
    }
  coto->x /= nVertexList;
  coto->y /= nVertexList;
  coto->z /= nVertexList;
  return coto;
}

void
translateAndProject (struct vertex *vertexList,int nVertexList, struct points *coto)
{
  double matrix[4][4] = { {1, 0, 0, -coto->x},
  {0, 1, 0, -coto->y},
  {0, 0, 1, (3 * f) - coto->z},
  {0, 0, 1 / f, (((3 * f) - coto->z)) / f}
  };
  applyMatrix (vertexList, nVertexList, matrix);
}

void
translation (struct vertex *vertexList,int nVertexList, struct points *coto)
{
  double matrix[4][4] = { {1, 0, 0, -coto->x},
  {0, 1, 0, -coto->y},
  {0, 0, 1, -coto->z},
  {0, 0, 0, 1}
  };
  applyMatrix (vertexList, nVertexList, matrix);
}

void
rotationX (struct vertex *vertexList,int nVertexList, double alfa)
{
  double cx = cos (alfa);
  double sx = sin (alfa);
  double matrix[4][4] = { {1, 0, 0, 0},
  {0, cx, -sx, 0},
  {0, sx, cx, 0},
  {0, 0, 0, 1}
  };
  applyMatrix (vertexList, nVertexList, matrix);
}

void
rotationY (struct vertex *vertexList,int nVertexList, double beta)
{
  double cy = cos (beta);
  double sy = sin (beta);
  double matrix[4][4] = { {cy, 0, sy, 0},
  {0, 1, 0, 0},
  {-sy, 0, cy, 0},
  {0, 0, 0, 1}
  };
  applyMatrix (vertexList, nVertexList, matrix);
}

void
rotationZ (struct vertex *vertexList,int nVertexList, double gamma)
{
  double cz = cos (gamma);
  double sz = sin (gamma);
  double matrix[4][4] = { {cz, -sz, 0, 0},
  {sz, cz, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
  };
  applyMatrix (vertexList, nVertexList, matrix);
}

void
returnTranslation (struct vertex *vertexList,int nVertexList, struct points *coto)
{
  double matrix[4][4] = { {1, 0, 0, coto->x},
  {0, 1, 0, coto->y},
  {0, 0, 1, coto->z},
  {0, 0, 0, 1}
  };
  applyMatrix (vertexList, nVertexList, matrix);

}

void
applyMatrix (struct vertex *vertexList,int nVertexList, double matrix[4][4])
{
  int i = 0;
  int j = 0;
  int op = 1;
  struct points aux;
  for (i = 0; i < nVertexList; i++)
    {
      aux.x = 0.0;
      aux.y = 0.0;
      aux.z = 0.0;
      aux.w = 0.0;
      for (j = 0; j < 4; j++)
  {
    switch (op)
      {
      case 1:
        aux.x += (matrix[j][0] * vertexList[i].x);
        aux.x += (matrix[j][1] * vertexList[i].y);
        aux.x += (matrix[j][2] * vertexList[i].z);
        aux.x += (matrix[j][3] * vertexList[i].w);
        op = 2;
        break;
      case 2:
        aux.y += (matrix[j][0] * vertexList[i].x);
        aux.y += (matrix[j][1] * vertexList[i].y);
        aux.y += (matrix[j][2] * vertexList[i].z);
        aux.y += (matrix[j][3] * vertexList[i].w);
        op = 3;
        break;
      case 3:
        aux.z += (matrix[j][0] * vertexList[i].x);
        aux.z += (matrix[j][1] * vertexList[i].y);
        aux.z += (matrix[j][2] * vertexList[i].z);
        aux.z += (matrix[j][3] * vertexList[i].w);
        op = 4;
        break;
      case 4:
        aux.w += (matrix[j][0] * vertexList[i].x);
        aux.w += (matrix[j][1] * vertexList[i].y);
        aux.w += (matrix[j][2] * vertexList[i].z);
        aux.w += (matrix[j][3] * vertexList[i].w);
        op = 1;
        break;
      }
  }
      vertexList[i].x = aux.x;
      vertexList[i].y = aux.y;
      vertexList[i].z = aux.z;
      vertexList[i].w = aux.w;
    }
}

void
fh(struct face *faceList,int nFaceList)
{
  struct segment s1;
  struct segment s2;
  for(int i=0;i<nFaceList;i++)
  {
    s1.x1=faceList[i].e1->start->x;
	s1.y1=faceList[i].e1->start->y;
	s1.z1=faceList[i].e1->start->zBuff;
	s1.x2=faceList[i].e1->end->x;
	s1.y2=faceList[i].e1->end->y;
	s1.z2=faceList[i].e1->end->zBuff;
	s2.x1=faceList[i].e2->start->x;
	s2.y1=faceList[i].e2->start->y;
	s2.z1=faceList[i].e2->start->zBuff;
	s2.x2=faceList[i].e2->end->x;
	s2.y2=faceList[i].e2->end->y;
	s2.z2=faceList[i].e2->end->zBuff;
    if(principalFH(&s1,&s2)>0)
    {
      faceList[i].hide=1;
    }
    else
    {
      faceList[i].hide=0;
    }
  }

}

void  //3D->2D
transform_3D (struct vertex *vertexList,int nVertexList)
{
  int i = 0;
  for (i = 0; i < nVertexList; i++)
    {
      vertexList[i].x /= vertexList[i].w;
      vertexList[i].y /= vertexList[i].w;
      vertexList[i].z /= vertexList[i].w;
    }
}

void
scaleAndTraslation (struct vertex *vertexList,int nVertexList) //scale and translate the image
{
  int i = 0;
  for (i = 0; i < nVertexList; i++)
    {
      vertexList[i].x *= 1000;
      vertexList[i].y *= 1000;
      vertexList[i].x += width;
      vertexList[i].y += height;
    }
}

void
draw3D (struct face *faceList,int nFaceList, char *name)
{
    int **points = create_Points ();
    unsigned char ***raster = create_raster ();
    int i = 0;
    for (i = 0; i < nFaceList; i ++)
    {
    	if(faceList[i].hide==0)
    	{
    		points[0][0] = faceList[i].e1->start->x;
    	  points[0][1] = faceList[i].e1->start->y;
    	  points[1][0] = faceList[i].e1->end->x;
    	  points[1][1] = faceList[i].e1->end->y;
    	  principalDrawline (points, raster);
    	  points[0][0] = faceList[i].e2->start->x;
    	  points[0][1] = faceList[i].e2->start->y;
    	  points[1][0] = faceList[i].e2->end->x;
    	  points[1][1] = faceList[i].e2->end->y;
    	  principalDrawline (points, raster);
    	  points[0][0] = faceList[i].e3->start->x;
    	  points[0][1] = faceList[i].e3->start->y;
    	  points[1][0] = faceList[i].e3->end->x;
    	  points[1][1] = faceList[i].e3->end->y;
    	  principalDrawline (points, raster);
    	}
    }
  draw (raster, name);
}
