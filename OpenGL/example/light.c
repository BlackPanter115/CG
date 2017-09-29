/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 *  light.c
 *  This program demonstrates the use of the OpenGL lighting
 *  model.  A sphere is drawn using a grey material characteristic.
 *  A single light source illuminates the object.
 */
#include <GL/glut.h>
#include <stdlib.h>

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
   GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 1.0 }; //color of specular light, if you change this values you change the color of the specular
   GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 }; //color of ambient light, if you change this values you change the color of the ambient(the sphere's color change)
   GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 }; //color of diffuse light, if you change this values you change the color of the diffuse(the sphere's color change)
   GLfloat mat_shininess[] = { 50.0 }; //the shininess of the sphere
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; //position of the light

   glClearColor (0.0, 0.0, 0.0, 0.0);//change the color of the background
   glShadeModel (GL_SMOOTH);
   //glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient); //set the ambient light
   //glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse); //set the ambient light
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set the specular light
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); //set the shinniness
   glLightfv(GL_LIGHT0, GL_POSITION, light_position); //set the light position
   glEnable(GL_LIGHTING); //enable the light(the default state of the light is disabled, so you need to "Turn it on")
   glEnable(GL_LIGHT0); //the same ^
   glEnable(GL_DEPTH_TEST); //
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears the OpenGL color and depth buffers
   glutSolidSphere (1.0, 20, 16); //set the sphere
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);     //multiply the current matrix with an orthogonal matrix
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); //window's size
   glutInitWindowPosition (100, 100); //window's position 
   glutCreateWindow (argv[0]); //create the window (the name has 'a.out')
   init (); //prepare the lights and the background color  
   glutDisplayFunc(display); //display the sphere
   glutReshapeFunc(reshape); //adjust the camera
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}