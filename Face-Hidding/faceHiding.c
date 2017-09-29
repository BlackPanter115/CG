#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "faceHiding.h"




double
principalFH(struct segment *s1, struct segment *s2)
{
	struct vector *v1=createVector(s1);
	struct vector *v2=createVector(s2);
	struct vector *vN=createNormalVector(v1,v2);
	struct vector cam;
	cam.x=cam.y=0;
	cam.z=-1;
	return (vN->z*cam.z);
}

struct vector *
createVector(struct segment *aux)
{
	struct vector *v=(struct vector *)malloc(sizeof(struct vector));
	v->x=aux->x2-aux->x1;
	v->y=aux->y2-aux->y1;
	v->z=aux->z2-aux->z1;
	return v;
}

struct vector *
createNormalVector(struct vector *vectorA, struct vector *vectorB)
{
	struct vector *vectorN=(struct vector *)malloc(sizeof(struct vector));
  	vectorN->x=(vectorA->y*vectorB->z)-(vectorA->z*vectorB->y);
  	vectorN->y=(vectorA->z*vectorB->x)-(vectorA->x*vectorB->z);
  	vectorN->z=(vectorA->x*vectorB->y)-(vectorA->y*vectorB->x);
  	return vectorN;
}



