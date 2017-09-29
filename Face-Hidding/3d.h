#ifndef __3D_H__
#define __3D_H__

struct vertex
{
  int num;
  double x;
  double y;
  double z;
  double zBuff;
  double w;
  double hash;
};

struct edge
{
  int num;
  struct vertex *start;
  struct vertex *end;
  double hash;
};

struct face
{
  int num;
  struct edge *e1;
  struct edge *e2;
  struct edge *e3;
  int hide;
};

struct points
{
  double x;
  double y;
  double z;
  double w;
};

void principal3d (struct vertex *vertexList,struct edge *edgeList,struct face *faceList,int nVertexList,int nEdgeList,int nFaceList,char *name);
struct points *centerOfTheObject (struct vertex *vertexList,int nVertexList);
void translateAndProject (struct vertex *vertexList,int nVertexList, struct points *coto);
void translation (struct vertex *vertexList,int nVertexList, struct points *coto);
void rotationX (struct vertex *vertexList,int nVertexList, double alfa);
void rotationY (struct vertex *vertexList,int nVertexList, double beta);
void rotationZ (struct vertex *vertexList,int nVertexList, double gamma);
void returnTranslation (struct vertex *vertexList,int nVertexList, struct points *coto);
void applyMatrix (struct vertex *vertexList,int nVertexList, double matrix[4][4]);
void fh(struct face *faceList,int nFaceList);
void transform_3D (struct vertex *vertexList,int nVertexList);
void scaleAndTraslation (struct vertex *vertexList,int nVertexList);
void draw3D (struct face *faceList,int nFaceList, char *name);

#endif
