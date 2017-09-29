#ifndef __VERTEXLISTFORMAT_H__
#define __VERTEXLISTFORMAT_H__


void principalVLF(char *name);
int numberOfRaws();
struct vertex *getVertexList(int raws);
void inicializateVertexList(struct vertex *vertexList, int raws);
struct vertex *finalVertexList(struct vertex *vertexList);
void printVertexList(struct vertex *vertexList);
struct edge *getEdgeList(int raws, struct vertex *vertexList);
void inicializateEdgeList(struct edge *edgeList, int raws);
struct edge *finalEdgeList(struct edge *edgeList);
void printEdgeList(struct edge *edgeList);
struct face *getFaceList (int raws, struct vertex *vertexList, struct edge *edgeList);
void inicializateFaceList(struct face *faceList, int raws);
void printFaceList(struct face *faceList);

#endif
