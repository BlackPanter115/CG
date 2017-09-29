#include <stdio.h>
#include <stdlib.h>
#include "vertexListFormat.h"
#include "3d.h"

int nVertexList = 0;
int nEdgeList = 0;
int nFaceList = 0;

void
principalVLF (char *name, char *alfa, char *beta, char *gamma, char *vScale,
	      char *translationX, char *translationY)
{
  int raws = numberOfRaws ();
  struct vertex *vertexList = getVertexList (raws);
  vertexList = finalVertexList (vertexList);
  printVertexList (vertexList);
  struct edge *edgeList = getEdgeList (raws, vertexList);
  edgeList = finalEdgeList (edgeList);
  printEdgeList (edgeList);
  struct face *faceList = getFaceList (raws, vertexList, edgeList);
  printFaceList (faceList);
  principal3d (vertexList, edgeList, faceList, nVertexList, nEdgeList,
	       nFaceList, name, alfa, beta, gamma, vScale, translationX,
	       translationY);
}

int
numberOfRaws ()
{
  int raws = 0;
  FILE *fp = fopen ("fate.raw", "r");
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

struct vertex *
getVertexList (int raws)
{
  int i = 0;
  int j = 0;
  int k = 0;
  int exist = 0;
  struct vertex *vertexList = NULL;
  struct vertex tmp;
  FILE *fp = fopen ("fate.raw", "r");
  vertexList =
    (struct vertex *) malloc ((sizeof (struct vertex)) * (raws * 3));
  inicializateVertexList (vertexList, raws);
  for (i = 0, k = 0; i < raws * 3; i++)
    {
      fscanf (fp, "%lf %lf %lf ", &tmp.x, &tmp.y, &tmp.z);
      tmp.w = 1.0;
      tmp.hash = tmp.x + tmp.y + tmp.z;
      exist = 0;
      for (j = 0; j < i; j++)
	{
	  if (tmp.hash == vertexList[j].hash)
	    {
	      if ((tmp.x == vertexList[j].x) && (tmp.y == vertexList[j].y)
		  && (tmp.z == vertexList[j].z))
		{
		  exist = 1;
		  break;
		}
	    }
	}
      if (exist == 0)
	{
	  vertexList[k].num = k + 1;
	  vertexList[k].x = tmp.x;
	  vertexList[k].y = tmp.y;
	  vertexList[k].z = tmp.z;
	  vertexList[k].w = 1.0;
	  vertexList[k].hash = tmp.hash;
	  k++;
	  nVertexList++;
	}
    }
  fclose (fp);
  return vertexList;
}

void
inicializateVertexList (struct vertex *vertexList, int raws)
{
  for (int i = 0; i < raws * 3; i++)
    vertexList[i].x = vertexList[i].y = vertexList[i].z = vertexList[i].w =
      vertexList[i].hash = 0.0;
}

void
printVertexList (struct vertex *vertexList)
{
  remove ("vertexList.txt");
  FILE *fp = fopen ("vertexList.txt", "w");
  fprintf (fp,
	   "#               X                    Y                   Z\n");
  for (int i = 0; i < nVertexList; i++)
    {
      fprintf (fp,
	       "%d			%lf			%lf			%lf\n",
	       vertexList
	       [i].num, vertexList[i].x, vertexList[i].y, vertexList[i].z);
    }
  fclose (fp);
}

struct vertex *
finalVertexList (struct vertex *vertexList)
{
  struct vertex *new =
    (struct vertex *) malloc (sizeof (struct vertex) * nVertexList);
  for (int i = 0; i < nVertexList; i++)
    new[i] = vertexList[i];
  free (vertexList);
  return new;
}

struct edge *
getEdgeList (int raws, struct vertex *vertexList)
{
  int i = 0;
  int j = 0;
  int k = 0;
  int exist1 = 0;
  int exist2 = 0;
  int exist3 = 0;
  struct edge *edgeList = NULL;
  struct vertex v1;
  struct vertex v2;
  struct vertex v3;
  struct vertex *a1;
  struct vertex *a2;
  struct vertex *a3;
  struct edge e1;
  struct edge e3;
  struct edge e2;
  FILE *fp = fopen ("fate.raw", "r");
  edgeList = (struct edge *) malloc ((sizeof (struct edge)) * (raws * 3));
  inicializateEdgeList (edgeList, raws);
  for (i = 0, k = 0; i < raws * 3; i += 3)
    {
      fscanf (fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf ", &v1.x, &v1.y, &v1.z,
	      &v2.x, &v2.y, &v2.z, &v3.x, &v3.y, &v3.z);
      v1.w = 1.0;
      v1.hash = v1.x + v1.y + v1.z;
      v2.w = 1.0;
      v2.hash = v2.x + v2.y + v2.z;
      v3.w = 1.0;
      v3.hash = v3.x + v3.y + v3.z;
      exist1 = 0;
      exist2 = 0;
      exist3 = 0;
      for (j = 0; j < nVertexList; j++)
	{
	  if (v1.hash == vertexList[j].hash)
	    {
	      if ((v1.x == vertexList[j].x) && (v1.y == vertexList[j].y)
		  && (v1.z == vertexList[j].z))
		{
		  a1 = &vertexList[j];
		  break;
		}
	    }
	}
      for (j = 0; j < nVertexList; j++)
	{
	  if (v2.hash == vertexList[j].hash)
	    {
	      if ((v2.x == vertexList[j].x) && (v2.y == vertexList[j].y)
		  && (v2.z == vertexList[j].z))
		{
		  a2 = &vertexList[j];
		  break;
		}
	    }
	}
      for (j = 0; j < nVertexList; j++)
	{
	  if (v3.hash == vertexList[j].hash)
	    {
	      if ((v3.x == vertexList[j].x) && (v3.y == vertexList[j].y)
		  && (v3.z == vertexList[j].z))
		{
		  a3 = &vertexList[j];
		  break;
		}
	    }
	}
      e1.start = a1;
      e1.end = a2;
      e1.hash = (e1.start->hash) + (e1.end->hash);
      e2.start = a2;
      e2.end = a3;
      e2.hash = (e2.start->hash) + (e2.end->hash);
      e3.start = a3;
      e3.end = a1;
      e3.hash = (e3.start->hash) + (e3.end->hash);
      for (int m = 0; m < i; m++)
	{
	  if (e1.hash == edgeList[m].hash)
	    {
	      if (((e1.start == edgeList[m].start)
		   && (e1.end == edgeList[m].end))
		  || ((e1.start == edgeList[m].end)
		      && (e1.end == edgeList[m].start)))
		{
		  exist1 = 1;
		  break;
		}
	    }
	}
      for (int m = 0; m < i; m++)
	{
	  if (e2.hash == edgeList[m].hash)
	    {
	      if (((e2.start == edgeList[m].start)
		   && (e2.end == edgeList[m].end))
		  || ((e2.start == edgeList[m].end)
		      && (e2.end == edgeList[m].start)))
		{
		  exist2 = 1;
		  break;
		}
	    }
	}
      for (int m = 0; m < i; m++)
	{
	  if (e3.hash == edgeList[m].hash)
	    {
	      if (((e3.start == edgeList[m].start)
		   && (e3.end == edgeList[m].end))
		  || ((e3.start == edgeList[m].end)
		      && (e3.end == edgeList[m].start)))
		{
		  exist3 = 1;
		  break;
		}
	    }
	}
      if (exist1 == 0)
	{
	  edgeList[k].num = k + 1;
	  edgeList[k].start = e1.start;
	  edgeList[k].end = e1.end;
	  edgeList[k].hash = e1.hash;
	  k++;
	  nEdgeList++;
	}
      if (exist2 == 0)
	{
	  edgeList[k].num = k + 1;
	  edgeList[k].start = e2.start;
	  edgeList[k].end = e2.end;
	  edgeList[k].hash = e2.hash;
	  k++;
	  nEdgeList++;
	}
      if (exist3 == 0)
	{
	  edgeList[k].num = k + 1;
	  edgeList[k].start = e3.start;
	  edgeList[k].end = e3.end;
	  edgeList[k].hash = e3.hash;
	  k++;
	  nEdgeList++;
	}
    }
  fclose (fp);
  return edgeList;
}

void
inicializateEdgeList (struct edge *edgeList, int raws)
{
  for (int i = 0; i < raws * 3; i++)
    {
      edgeList[i].start = edgeList[i].end = NULL;
      edgeList[i].hash = 0;
    }
}

struct edge *
finalEdgeList (struct edge *edgeList)
{
  struct edge *new =
    (struct edge *) malloc (sizeof (struct edge) * nEdgeList);
  for (int i = 0; i < nEdgeList; i++)
    new[i] = edgeList[i];
  free (edgeList);
  return new;
}

void
printEdgeList (struct edge *edgeList)
{
  remove ("edgeList.txt");
  FILE *fp = fopen ("edgeList.txt", "w");
  fprintf (fp, "#      V1     V2\n");
  for (int i = 0; i < nEdgeList; i++)
    {
      fprintf (fp, "%d      %d     %d\n", edgeList[i].num,
	       edgeList[i].start->num, edgeList[i].end->num);
    }
  fclose (fp);
}

struct face *
getFaceList (int raws, struct vertex *vertexList, struct edge *edgeList)
{
  int i = 0;
  int j = 0;
  int k = 0;
  struct face *faceList = NULL;
  struct vertex v1;
  struct vertex v2;
  struct vertex v3;
  struct vertex *a1;
  struct vertex *a2;
  struct vertex *a3;
  struct edge e1;
  struct edge e2;
  struct edge e3;
  struct edge *b1;
  struct edge *b2;
  struct edge *b3;
  FILE *fp = fopen ("fate.raw", "r");
  faceList = (struct face *) malloc ((sizeof (struct face)) * (raws));
  inicializateFaceList (faceList, raws);
  for (i = 0, k = 0; i < raws * 3; i += 3, k++)
    {
      fscanf (fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf ", &v1.x, &v1.y, &v1.z,
	      &v2.x, &v2.y, &v2.z, &v3.x, &v3.y, &v3.z);
      v1.w = 1.0;
      v1.hash = v1.x + v1.y + v1.z;
      v2.w = 1.0;
      v2.hash = v2.x + v2.y + v2.z;
      v3.w = 1.0;
      v3.hash = v3.x + v3.y + v3.z;
      for (j = 0; j < nVertexList; j++)
	{
	  if (v1.hash == vertexList[j].hash)
	    {
	      if ((v1.x == vertexList[j].x) && (v1.y == vertexList[j].y)
		  && (v1.z == vertexList[j].z))
		{
		  a1 = &vertexList[j];
		  break;
		}
	    }
	}
      for (j = 0; j < nVertexList; j++)
	{
	  if (v2.hash == vertexList[j].hash)
	    {
	      if ((v2.x == vertexList[j].x) && (v2.y == vertexList[j].y)
		  && (v2.z == vertexList[j].z))
		{
		  a2 = &vertexList[j];
		  break;
		}
	    }
	}
      for (j = 0; j < nVertexList; j++)
	{
	  if (v3.hash == vertexList[j].hash)
	    {
	      if ((v3.x == vertexList[j].x) && (v3.y == vertexList[j].y)
		  && (v3.z == vertexList[j].z))
		{
		  a3 = &vertexList[j];
		  break;
		}
	    }
	}
      e1.start = a1;
      e1.end = a2;
      e1.hash = (e1.start->hash) + (e1.end->hash);
      e2.start = a2;
      e2.end = a3;
      e2.hash = (e2.start->hash) + (e2.end->hash);
      e3.start = a3;
      e3.end = a1;
      e3.hash = (e3.start->hash) + (e3.end->hash);
      for (int m = 0; m < nEdgeList; m++)
	{
	  if (e1.hash == edgeList[m].hash)
	    {
	      if (((e1.start == edgeList[m].start)
		   && (e1.end == edgeList[m].end))
		  || ((e1.start == edgeList[m].end)
		      && (e1.end == edgeList[m].start)))
		{
		  b1 = &edgeList[m];
		  break;
		}
	    }
	}
      for (int m = 0; m < nEdgeList; m++)
	{
	  if (e2.hash == edgeList[m].hash)
	    {
	      if (((e2.start == edgeList[m].start)
		   && (e2.end == edgeList[m].end))
		  || ((e2.start == edgeList[m].end)
		      && (e2.end == edgeList[m].start)))
		{
		  b2 = &edgeList[m];
		  break;
		}
	    }
	}
      for (int m = 0; m < nEdgeList; m++)
	{
	  if (e3.hash == edgeList[m].hash)
	    {
	      if (((e3.start == edgeList[m].start)
		   && (e3.end == edgeList[m].end))
		  || ((e3.start == edgeList[m].end)
		      && (e3.end == edgeList[m].start)))
		{
		  b3 = &edgeList[m];
		  break;
		}
	    }
	}
      if((k%2)==0)
      {
      	faceList[k].num = k + 1;
      	faceList[k].e1 = b2;
      	faceList[k].e2 = b3;
      	faceList[k].e3 = b1;
      }
      else
      {
      	faceList[k].num = k + 1;
      	faceList[k].e1 = b3;
      	faceList[k].e2 = b1;
      	faceList[k].e3 = b2;
      }
      nFaceList++;
    }
  fclose (fp);
  return faceList;
}

void
inicializateFaceList (struct face *faceList, int raws)
{
  for (int i = 0; i < raws; i++)
    {
      faceList[i].e1 = faceList[i].e2 = faceList[i].e3 = NULL;
    }
}

void
printFaceList (struct face *faceList)
{
  remove ("faceList.txt");
  FILE *fp = fopen ("faceList.txt", "w");
  fprintf (fp, "#      E1     E2     E3\n");
  for (int i = 0; i < nFaceList; i++)
    {
      fprintf (fp, "%d      %d     %d     %d\n", faceList[i].num,
	       faceList[i].e1->num, faceList[i].e2->num, faceList[i].e3->num);
    }
  fclose (fp);
}
