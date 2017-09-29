#ifndef __DRAWLINE_H__
#define __DRAWLINE_H__

struct temp {
	unsigned char ***raster;
	double **zBuffer;
};

struct final {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	double z;
};

struct point {
	int x;
	int y;
	double z;
};

void principalDrawline(struct point *Point, struct temp *temporalRaster);
unsigned char ***create_raster();
double **create_zBuffer();
struct final **create_finalRaster();
void reset_temporalRaster(struct temp *temporalRaster);
void specialdrawX(struct point *Point, struct temp *temporalRaster);
void specialdrawY(struct point *Point, struct temp *temporalRaster);
void calculate_line(struct point *Point, struct temp *temporalRaster);
void specialdrawPositive(struct point *Point, struct temp *temporalRaster);
void specialdrawNegative1(struct point *Point, struct temp *temporalRaster);
void specialdrawNegative2(struct point *Point, struct temp *temporalRaster);
void specialdrawM1(struct point *Point, struct temp *temporalRaster);
void specialdrawM2(struct point *Point, struct temp *temporalRaster);
void put_pixel(int x, int y, double z, struct temp *temporalRaster, int r,
	       int g, int b);
void fillFace(struct temp *contour, int r, int g, int b);
void insertInFinal(struct final **finalRaster, struct temp *temporalRaster);
void draw(struct final **finalRaster, char *name);;
#endif
