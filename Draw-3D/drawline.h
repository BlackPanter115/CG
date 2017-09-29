#ifndef __DRAWLINE_H__
#define __DRAWLINE_H__

void principalBresenhan (int **points, unsigned char ***raster);
int **create_Points ();
unsigned char ***create_raster ();
void specialdrawX (int **points, unsigned char ***raster);
void specialdrawY (int **points, unsigned char ***raster);
void calculate_line (int **points, unsigned char ***raster);
void specialdrawPositive (int **points, unsigned char ***raster);
void specialdrawNegative1 (int **points, unsigned char ***raster);
void specialdrawNegative2 (int **points, unsigned char ***raster);
void specialdrawM1 (int **points, unsigned char ***raster);
void specialdrawM2 (int **points, unsigned char ***raster);
void put_pixel (int x1, int y1, unsigned char ***raster, int r, int g, int b);
void draw (unsigned char ***raster, char *name);
#endif
