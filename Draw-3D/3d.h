#ifndef __3D_H__
#define __3D_H__

struct points
{
  double x;
  double y;
  double z;
  double w;
};

void principal3d (char *name);
int numberOfRaws ();
struct points *get_points (int raws);
struct points *centerOfTheObject (int raws, struct points *data);
void translateAndProject (struct points *data, struct points *coto, int raws);
void translation (struct points *data, struct points *coto, int raws);
void rotationX (struct points *data, int raws, double alfa);
void rotationY (struct points *data, int raws, double beta);
void rotationZ (struct points *data, int raws, double gamma);
void returnTranslation (struct points *data, struct points *coto, int raws);
void applyMatrix (struct points *data, int raws, double matrix[4][4]);
void transform_3D (int raws, struct points *data);
void scaleAndTraslation (int raws, struct points *data);
void draw3D (int raws, struct points *data, char *name);
int faceHiding(struct points *data);

#endif
