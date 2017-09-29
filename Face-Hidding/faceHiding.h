#ifndef __FACEHIDING_H__
#define __FACEHIDING_H__

struct segment
{
  double x1;
  double y1;
  double z1;
  double x2;
  double y2;
  double z2;
};

struct vector
{
  double x;
  double y;
  double z;
};

double principalFH(struct segment *s1, struct segment *s2);
struct vector *createVector(struct segment *aux);
struct vector *createNormalVector(struct vector *vectorA, struct vector *vectorB);
#endif
