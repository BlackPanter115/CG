#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "drawline.h"

void principalDrawline(struct point *Point, struct temp *temporalRaster)
{
	if (Point[0].x == Point[1].x)	//ya esta
	{
		specialdrawX(Point, temporalRaster);
	} else if (Point[0].y == Point[1].y)	//ya esta
	{
		specialdrawY(Point, temporalRaster);
	} else {
		double slope =
		    (double)(Point[1].y - Point[0].y) / (Point[1].x -
							 Point[0].x);
		if (slope > 1)	//ya esta
		{
			specialdrawPositive(Point, temporalRaster);
		} else if (slope < -1)	//ya esta
		{
			specialdrawNegative2(Point, temporalRaster);
		} else if ((slope < 0) && (slope > -1))	//ya esta
		{
			specialdrawNegative1(Point, temporalRaster);
		} else if (slope == 1)	//ya esta
		{
			specialdrawM1(Point, temporalRaster);
		} else if (slope == -1)	//ya esta
		{
			specialdrawM2(Point, temporalRaster);
		} else		//ya esta
		{
			calculate_line(Point, temporalRaster);
		}
	}
}

unsigned char ***create_raster()
{
	unsigned char ***raster;
	int i = 0;
	int j = 0;
	raster = (unsigned char ***)malloc(sizeof(unsigned char **) * 1920);
	for (i = 0; i < 1920; i++) {
		raster[i] =
		    (unsigned char **)malloc(sizeof(unsigned char *) * 1080);
	}
	for (i = 0; i < 1920; i++) {
		for (j = 0; j < 1080; j++) {
			raster[i][j] =
			    (unsigned char *)malloc(sizeof(unsigned char) * 3);
		}
	}
	for (i = 0; i < 1920; i++)
		for (j = 0; j < 1080; j++) {
			raster[i][j][0] = 255;
			raster[i][j][1] = 255;
			raster[i][j][2] = 255;
		}
	return raster;
}

double **create_zBuffer()
{
	double **buffer;
	int i = 0;
	int j = 0;
	buffer = (double **)malloc(sizeof(double *) * 1920);
	for (i = 0; i < 1920; i++) {
		buffer[i] = (double *)malloc(sizeof(double) * 1080);
	}
	for (i = 0; i < 1920; i++) {
		for (j = 0; j < 1080; j++) {
			buffer[i][j] = -99999.0;
		}
	}
	return buffer;
}

struct final **create_finalRaster()
{
	struct final **raster;
	int i = 0;
	int j = 0;
	raster = (struct final **)malloc(sizeof(struct final *) * 1920);
	for (i = 0; i < 1920; i++) {
		raster[i] = (struct final *)malloc(sizeof(struct final) * 1080);
	}
	for (i = 0; i < 1920; i++) {
		for (j = 0; j < 1080; j++) {
			raster[i][j].r = 255;
			raster[i][j].g = 255;
			raster[i][j].b = 255;
			raster[i][j].z = -99999.0;
		}
	}
	return raster;
}

void reset_temporalRaster(struct temp *temporalRaster)
{
	for (int i = 0; i < 1920; i++) {
		for (int j = 0; j < 1080; j++) {
			temporalRaster->raster[i][j][0] = 255;
			temporalRaster->raster[i][j][1] = 255;
			temporalRaster->raster[i][j][2] = 255;
			temporalRaster->zBuffer[i][j] = -99999.0;
		}
	}
}

void specialdrawX(struct point *Point, struct temp *temporalRaster)
{
	double aux;
	int i = 0;
	int r = 0;
	int g = 0;
	int b = 0;
	double z;
	double nextZ;
	if ((Point[1].y - Point[0].y) < 0) {
		aux = Point[0].x;
		Point[0].x = Point[1].x;
		Point[1].x = aux;
		aux = Point[0].y;
		Point[0].y = Point[1].y;
		Point[1].y = aux;
		aux = Point[0].z;
		Point[0].z = Point[1].z;
		Point[1].z = aux;
	}
	nextZ = (Point[1].z - Point[0].z) / (Point[1].y - Point[0].y);
	z = Point[0].z;
	for (i = Point[0].y; i <= Point[1].y; i++) {
		put_pixel(Point[0].x, i, z, temporalRaster, r, g, b);
		z += nextZ;
	}
}

void specialdrawY(struct point *Point, struct temp *temporalRaster)
{
	double aux;
	int i = 0;
	int r = 0;
	int g = 0;
	int b = 0;
	double z;
	double nextZ;
	if ((Point[1].x - Point[0].x) < 0) {
		aux = Point[0].x;
		Point[0].x = Point[1].x;
		Point[1].x = aux;
		aux = Point[0].y;
		Point[0].y = Point[1].y;
		Point[1].y = aux;
		aux = Point[0].z;
		Point[0].z = Point[1].z;
		Point[1].z = aux;

	}
	nextZ = (Point[1].z - Point[0].z) / (Point[1].x - Point[0].x);
	z = Point[0].z;
	for (i = Point[0].x; i <= Point[1].x; i++) {
		put_pixel(i, Point[0].y, z, temporalRaster, r, g, b);
		z += nextZ;
	}
}

void calculate_line(struct point *Point, struct temp *temporalRaster)
{
	int r = 0;
	int g = 0;
	int b = 0;
	double z;
	double nextZ;
	double aux = 0;
	int x = 0;
	int y = 0;
	int dx = 0;
	int dy = 0;
	int d = 0;
	int incE = 0;
	int incNE = 0;
	if ((Point[1].x - Point[0].x) < 0) {
		aux = Point[0].x;
		Point[0].x = Point[1].x;
		Point[1].x = aux;
		aux = Point[0].y;
		Point[0].y = Point[1].y;
		Point[1].y = aux;
		aux = Point[0].z;
		Point[0].z = Point[1].z;
		Point[1].z = aux;
	}
	put_pixel(Point[0].x, Point[0].y, Point[0].z, temporalRaster, r, g, b);
	put_pixel(Point[1].x, Point[1].y, Point[1].z, temporalRaster, r, g, b);
	dx = Point[1].x - Point[0].x;
	dy = Point[1].y - Point[0].y;
	d = (2 * dy) - dx;
	incE = 2 * dy;
	incNE = 2 * (dy - dx);
	y = Point[0].y;
	nextZ = (Point[1].z - Point[0].z) / (Point[1].x - Point[0].x);
	z = Point[0].z;
	for (x = Point[0].x + 1; x < Point[1].x; x++) {
		if (d <= 0) {
			d += incE;
		} else {
			d += incNE;
			y++;
		}
		z += nextZ;
		put_pixel(x, y, z, temporalRaster, r, g, b);
	}
}

void specialdrawPositive(struct point *Point, struct temp *temporalRaster)
{
	int r = 0;
	int g = 0;
	int b = 0;
	double z;
	double nextZ;
	int x = 0;
	int y = 0;
	int dx = 0;
	int dy = 0;
	int d = 0;
	double aux = 0;
	int incE = 0;
	int incNE = 0;
	put_pixel(Point[0].x, Point[0].y, Point[0].z, temporalRaster, r, g, b);
	put_pixel(Point[1].x, Point[1].y, Point[1].z, temporalRaster, r, g, b);
	if ((Point[1].y - Point[0].y) < 0) {
		aux = Point[0].x;
		Point[0].x = Point[1].x;
		Point[1].x = aux;
		aux = Point[0].y;
		Point[0].y = Point[1].y;
		Point[1].y = aux;
		aux = Point[0].z;
		Point[0].z = Point[1].z;
		Point[1].z = aux;
	}
	dx = Point[1].y - Point[0].y;
	dy = Point[1].x - Point[0].x;
	d = (2 * dy) - dx;
	incE = 2 * dy;
	incNE = 2 * (dy - dx);
	y = Point[0].x;
	nextZ = (Point[1].z - Point[0].z) / (Point[1].y - Point[0].y);
	z = Point[0].z;
	for (x = Point[0].y + 1; x < Point[1].y; x++) {
		if (d <= 0) {
			d += incE;
		} else {
			d += incNE;
			y++;
		}
		z += nextZ;
		put_pixel(y, x, z, temporalRaster, r, g, b);
	}
}

void specialdrawNegative1(struct point *Point, struct temp *temporalRaster)
{
	int r = 0;
	int g = 0;
	int b = 0;
	double z;
	double nextZ;
	double aux = 0;
	int x = 0;
	int y = 0;
	int dx = 0;
	int dy = 0;
	int d = 0;
	int incE = 0;
	int incNE = 0;
	if ((Point[1].x - Point[0].x) < 0) {
		aux = Point[0].x;
		Point[0].x = Point[1].x;
		Point[1].x = aux;
		aux = Point[0].y;
		Point[0].y = Point[1].y;
		Point[1].y = aux;
		aux = Point[0].z;
		Point[0].z = Point[1].z;
		Point[1].z = aux;
	}
	put_pixel(Point[0].x, Point[0].y, Point[0].z, temporalRaster, r, g, b);
	put_pixel(Point[1].x, Point[1].y, Point[1].z, temporalRaster, r, g, b);
	aux = Point[1].y;
	Point[1].y = Point[0].y;
	Point[0].y = aux;
	dx = (Point[1].x - Point[0].x);
	dy = (Point[1].y - Point[0].y);
	d = (2 * dy) - dx;
	incE = 2 * dy;
	incNE = 2 * (dy - dx);
	y = Point[0].y;
	nextZ = (Point[1].z - Point[0].z) / (Point[1].x - Point[0].x);
	z = Point[0].z;
	for (x = Point[1].x - 1; x > Point[0].x; x--) {
		if (d <= 0) {
			d += incE;
		} else {
			d += incNE;
			y++;
		}
		z += nextZ;
		put_pixel(x, y, z, temporalRaster, r, g, b);
	}
}

void specialdrawNegative2(struct point *Point, struct temp *temporalRaster)
{
	int r = 0;
	int g = 0;
	int b = 0;
	double z;
	double nextZ;
	double aux = 0;
	int x = 0;
	int y = 0;
	int dx = 0;
	int dy = 0;
	int d = 0;
	int incE = 0;
	int incNE = 0;
	if ((Point[1].x - Point[0].x) < 0) {
		aux = Point[0].x;
		Point[0].x = Point[1].x;
		Point[1].x = aux;
		aux = Point[0].y;
		Point[0].y = Point[1].y;
		Point[1].y = aux;
		aux = Point[0].z;
		Point[0].z = Point[1].z;
		Point[1].z = aux;
	}
	put_pixel(Point[0].x, Point[0].y, Point[0].z, temporalRaster, r, g, b);
	put_pixel(Point[1].x, Point[1].y, Point[1].z, temporalRaster, r, g, b);
	aux = Point[1].y;
	Point[1].y = Point[0].y;
	Point[0].y = aux;
	dx = (Point[1].y - Point[0].y);
	dy = (Point[1].x - Point[0].x);
	d = (2 * dy) - dx;
	incE = 2 * dy;
	incNE = 2 * (dy - dx);
	y = Point[0].x;
	nextZ = (Point[1].z - Point[0].z) / (Point[1].y - Point[0].y);
	z = Point[0].z;
	for (x = Point[1].y - 1; x > Point[0].y; x--) {
		if (d <= 0) {
			d += incE;
		} else {
			d += incNE;
			y++;
		}
		z += nextZ;
		put_pixel(y, x, z, temporalRaster, r, g, b);
	}
}

void specialdrawM1(struct point *Point, struct temp *temporalRaster)
{
	int r = 0;
	int g = 0;
	int b = 0;
	double z;
	double nextZ;
	int i = 0;
	int j = 0;
	double aux = 0;
	if ((Point[1].x - Point[0].x) < 0) {
		aux = Point[0].x;
		Point[0].x = Point[1].x;
		Point[1].x = aux;
		aux = Point[0].y;
		Point[0].y = Point[1].y;
		Point[1].y = aux;
		aux = Point[0].z;
		Point[0].z = Point[1].z;
		Point[1].z = aux;
	}
	nextZ = (Point[1].z - Point[0].z) / (Point[1].x - Point[0].x);
	z = Point[0].z;
	for (i = Point[0].x, j = Point[0].y; i < Point[1].x; i++, j++) {
		put_pixel(i, j, z, temporalRaster, r, g, b);
		z += nextZ;
	}
}

void specialdrawM2(struct point *Point, struct temp *temporalRaster)
{
	int r = 0;
	int g = 0;
	int b = 0;
	double z;
	double nextZ;
	int i = 0;
	int j = 0;
	double aux = 0;
	if ((Point[1].x - Point[0].x) < 0) {
		aux = Point[0].x;
		Point[0].x = Point[1].x;
		Point[1].x = aux;
		aux = Point[0].y;
		Point[0].y = Point[1].y;
		Point[1].y = aux;
		aux = Point[0].z;
		Point[0].z = Point[1].z;
		Point[1].z = aux;
	}
	nextZ = (Point[1].z - Point[0].z) / (Point[1].x - Point[0].x);
	z = Point[0].z;
	for (i = Point[0].x, j = Point[1].y; i < Point[1].x; i++, j--) {
		put_pixel(i, j, z, temporalRaster, r, g, b);
		z += nextZ;
	}
}

void put_pixel(int x, int y, double z, struct temp *temporalRaster, int r,
	       int g, int b)
{
	//printf("x=%d y=%d z=%lf\n", x,y,z);
	if ((x >= 0) && (x < 1920) && (y >= 0) && y < 1080) {
		temporalRaster->raster[x][y][0] = r;
		temporalRaster->raster[x][y][1] = g;
		temporalRaster->raster[x][y][2] = b;
		temporalRaster->zBuffer[x][y] = z;
	}
}

void fillFace(struct temp *contour, int r, int g, int b)
{
	int i;
	int j;
	int y1;
	int flag;
	double z;
	double nextZ;
	for (i = 0; i < 1920; i++) {
		flag = 0;
		for (j = 0; j < 1080; j++) {
			if ((contour->zBuffer[i][j] > -99999.0)
			    && (flag == 0)) {
				y1 = j;
				flag = 1;
			} else
			    if ((contour->zBuffer[i][j] >
				 -99999.0) && (flag == 1)) {
				nextZ =
				    (contour->zBuffer[i][j] -
				     contour->zBuffer[i][y1]) / (j - y1);
				z = contour->zBuffer[i][y1];
				for (int y = y1 + 1; y < j; y++) {
					z += nextZ;
					contour->raster[i][y][0] = r;
					contour->raster[i][y][1] = g;
					contour->raster[i][y][2] = b;
					contour->zBuffer[i][y] = z;
				}
			}
		}
	}
}

void insertInFinal(struct final **finalRaster, struct temp *temporalRaster)
{
	for (int i = 0; i < 1920; i++) {
		for (int j = 0; j < 1080; j++) {
			if (temporalRaster->zBuffer[i][j] > finalRaster[i][j].z) {
				finalRaster[i][j].r =
				    temporalRaster->raster[i][j][0];
				finalRaster[i][j].g =
				    temporalRaster->raster[i][j][1];
				finalRaster[i][j].b =
				    temporalRaster->raster[i][j][2];
				finalRaster[i][j].z =
				    temporalRaster->zBuffer[i][j];
			}

		}
	}
}

void draw(struct final **finalRaster, char *name)
{
	int j = 0;
	int i = 0;
	FILE *fp = NULL;
	fp = fopen(name, "w");
	fprintf(fp, "P3\n");
	fprintf(fp, "1920 1080\n");
	fprintf(fp, "256\n");
	for (i = 1079; i >= 0; i--) {
		for (j = 0; j < 1920; j++) {
			fprintf(fp, "  %d %d %d  ", finalRaster[j][i].r,
				finalRaster[j][i].g, finalRaster[j][i].b);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
