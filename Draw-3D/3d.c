//ffmpeg  avconv
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "drawline.h"
#include "3d.h"

static const double f = 35;
static const double width = 1920 / 2;
static const double height = 1080 / 2;

void
principal3d (char *name)
{
  srand (clock ());
  double alfa = ((double) (rand () % 101) / 50) * M_PI;
  double beta = ((double) (rand () % 101) / 50) * M_PI;
  double gamma = ((double) (rand () % 101) / 50) * M_PI;
  printf ("alfa=%lf,beta=%lf,gamma=%lf\n", alfa, beta, gamma);
  int raws = numberOfRaws ();
  struct points *data = get_points (raws);
  struct points *coto = centerOfTheObject (raws, data);
  translation (data, coto, raws);
  rotationX (data, raws, alfa);
  rotationY (data, raws, beta);
  rotationZ (data, raws, gamma);
  returnTranslation (data, coto, raws);
  translateAndProject (data, coto, raws);
  transform_3D (raws, data);
  scaleAndTraslation (raws, data);
  draw3D (raws, data, name);
}

int
numberOfRaws ()
{
  int raws = 0;
  FILE *fp = fopen ("monkey.raw", "r");
  char ch = fgetc (fp);
  while (ch != EOF)
    {
      if (ch == '\n')
         raws++;
      ch = fgetc (fp);
    }
  fclose (fp);
  return raws;
}

struct points *
get_points (int raws)
{
  int i = 0;
  struct points *data = NULL;
  FILE *fp = fopen ("monkey.raw", "r");
  data = (struct points *) malloc ((sizeof (struct points)) * (raws * 3));
  for (i = 0; i < raws * 3; i++)
    {
      fscanf (fp, "%lf %lf %lf ", &data[i].x, &data[i].y, &data[i].z);
      data[i].w = 1.0;    
    }
  fclose (fp);
  return data;
}

struct points *
centerOfTheObject (int raws, struct points *data)
{
  int i = 0;
  struct points *coto = (struct points *) malloc (sizeof (struct points) * 1);
  coto->x = 0;
  coto->y = 0;
  coto->z = 0;
  coto->w = 1;
  for (i = 0; i < raws * 3; i++)
    {
      coto->x += data[i].x;
      coto->y += data[i].y;
      coto->z += data[i].z;
    }
  coto->x /= (raws * 3);
  coto->y /= (raws * 3);
  coto->z /= (raws * 3);
  return coto;
}

void
translateAndProject (struct points *data, struct points *coto, int raws)
{
  double matrix[4][4] = { {1, 0, 0, -coto->x},
  {0, 1, 0, -coto->y},
  {0, 0, 1, (3 * f) - coto->z},
  {0, 0, 1 / f, (((3 * f) - coto->z)) / f}
  };
  applyMatrix (data, raws, matrix);
}

void
translation (struct points *data, struct points *coto, int raws)
{
  double matrix[4][4] = { {1, 0, 0, -coto->x},
  {0, 1, 0, -coto->y},
  {0, 0, 1, -coto->z},
  {0, 0, 0, 1}
  };
  applyMatrix (data, raws, matrix);
}

void
rotationX (struct points *data, int raws, double alfa)
{
  double cx = cos (alfa);
  double sx = sin (alfa);
  double matrix[4][4] = { {1, 0, 0, 0},
  {0, cx, -sx, 0},
  {0, sx, cx, 0},
  {0, 0, 0, 1}
  };
  applyMatrix (data, raws, matrix);
}

void
rotationY (struct points *data, int raws, double beta)
{
  double cy = cos (beta);
  double sy = sin (beta);
  double matrix[4][4] = { {cy, 0, sy, 0},
  {0, 1, 0, 0},
  {-sy, 0, cy, 0},
  {0, 0, 0, 1}
  };
  applyMatrix (data, raws, matrix);
}

void
rotationZ (struct points *data, int raws, double gamma)
{
  double cz = cos (gamma);
  double sz = sin (gamma);
  double matrix[4][4] = { {cz, -sz, 0, 0},
  {sz, cz, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
  };
  applyMatrix (data, raws, matrix);
}

void
returnTranslation (struct points *data, struct points *coto, int raws)
{
  double matrix[4][4] = { {1, 0, 0, coto->x},
  {0, 1, 0, coto->y},
  {0, 0, 1, coto->z},
  {0, 0, 0, 1}
  };
  applyMatrix (data, raws, matrix);

}

void
applyMatrix (struct points *data, int raws, double matrix[4][4])
{
  int i = 0;
  int j = 0;
  int op = 1;
  struct points aux;
  for (i = 0; i < raws * 3; i++)
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
        aux.x += (matrix[j][0] * data[i].x);
        aux.x += (matrix[j][1] * data[i].y);
        aux.x += (matrix[j][2] * data[i].z);
        aux.x += (matrix[j][3] * data[i].w);
        op = 2;
        break;
      case 2:
        aux.y += (matrix[j][0] * data[i].x);
        aux.y += (matrix[j][1] * data[i].y);
        aux.y += (matrix[j][2] * data[i].z);
        aux.y += (matrix[j][3] * data[i].w);
        op = 3;
        break;
      case 3:
        aux.z += (matrix[j][0] * data[i].x);
        aux.z += (matrix[j][1] * data[i].y);
        aux.z += (matrix[j][2] * data[i].z);
        aux.z += (matrix[j][3] * data[i].w);
        op = 4;
        break;
      case 4:
        aux.w += (matrix[j][0] * data[i].x);
        aux.w += (matrix[j][1] * data[i].y);
        aux.w += (matrix[j][2] * data[i].z);
        aux.w += (matrix[j][3] * data[i].w);
        op = 1;
        break;
      }
  }
      data[i] = aux;
    }
}

void  //3D->2D
transform_3D (int raws, struct points *data)
{
  int i = 0;
  for (i = 0; i < raws * 3; i++)
    {
      data[i].x /= data[i].w;
      data[i].y /= data[i].w;
      data[i].z /= data[i].w;
    }
}

void
scaleAndTraslation (int raws, struct points *data) //scale and translate the image
{
  int i = 0;
  for (i = 0; i < raws * 3; i++)
    {
      data[i].x *= 1000;
      data[i].y *= 1000;
      data[i].x += width;
      data[i].y += height;
    }
}

void
draw3D (int raws, struct points *data, char *name)
{
  int **points = create_Points ();
  unsigned char ***raster = create_raster ();
  int i = 0;
  for (i = 0; i < raws * 3; i += 3)
    {
      points[0][0] = data[i].x;
      points[0][1] = data[i].y;
      points[1][0] = data[i + 1].x;
      points[1][1] = data[i + 1].y;
      principalBresenhan (points, raster);
      points[0][0] = data[i + 1].x;
      points[0][1] = data[i + 1].y;
      points[1][0] = data[i + 2].x;
      points[1][1] = data[i + 2].y;
      principalBresenhan (points, raster);
      points[0][0] = data[i + 2].x;
      points[0][1] = data[i + 2].y;
      points[1][0] = data[i].x;
      points[1][1] = data[i].y;
      principalBresenhan (points, raster);
    }
  draw (raster, name);
}

int
faceHiding(struct points *data)
{
  struct points vectorA;
  struct points vectorB;
  struct points VectorN;
  struct points vectorV;
  float result;
  vectorV.x=0;
  vectorV.y=0;
  vectorV.z=1;
  vectorA.x=data[1].x-data[0].x;
  vectorA.y=data[1].y-data[0].y;
  vectorA.z=data[1].z-data[0].z;
  vectorB.x=data[2].x-data[0].x;
  vectorB.y=data[2].y-data[0].y;
  vectorB.z=data[2].z-data[0].z;
  VectorN.x=(vectorA.y*vectorB.z)-(vectorA.z*vectorB.y);
  VectorN.y=(vectorA.x*vectorB.z)-(vectorA.z*vectorB.x);
  VectorN.z=(vectorA.x*vectorB.y)-(vectorA.y*vectorB.x);
  result=(VectorN.x*vectorV.x)+(VectorN.y*vectorV.y)+(VectorN.z*vectorV.z);
  if(result>0)
    return 0;
  else
    return -1;
}
