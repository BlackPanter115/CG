/* sun.c
Compile: gcc sun.c -lGL -lGLU -lglut

Author: Dr. Jorge Luis Rosas Trigueros
Last modification: 19apr17
modified by: Miguel Rojas Esquivel
*/


#include <GL/glut.h>

// create rotation components
GLdouble r=0.3, rE=0, rM=0, rMars=0, rVenus=0;

void display(void);
void reshape(int w, int h);
void Timer(int value);


int main (int argc, char **argv)
{
glutInit(&argc, argv);
glutInitWindowSize(1366,768);
glutCreateWindow("Solar System :v");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
Timer(0);
glutMainLoop();
return 0;
}


void display(void)
{
glMatrixMode(GL_MODELVIEW);
glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity();
//Sun
glTranslatef(0.0,0.0,-5.0); //Trasladar esfera
glColor3f(0.9, 0.9, 0.0); //Darle color a la esfera
glutSolidSphere(r,100,20); //Crear la esfera
glPushMatrix(); //insertar elemento en la matriz
//Earth
glRotatef(rE,0.0,0.0,1.0);
glTranslatef(1.0,0.0,1.0);
glColor3f(0.0, 0.0, 1.0);
glutSolidSphere(0.1,100,10);
//Moon
glRotatef(rM,0.0,0.0,1.0);
glTranslatef(0.2,0.0,0.0);
glColor3f(0.8, 0.8, 0.8);
glutSolidSphere(0.05,100,5);
glPopMatrix(); //sacar elemento de la matriz
//Mars
glPushMatrix();
glRotatef(rMars,0.0,0.0,1.0);
glTranslatef(1.9,0.0,0.0);
glColor3f(1.0, 0.0, 0.0);
glutSolidSphere(0.09,100,10.0);
glPushMatrix();
//Mars Moon(Fobos)
glRotatef(rM,0.0,0.0,1.0);
glTranslatef(0.2,0.0,0.0);
glColor3f(0.8, 0.8, 0.8);
glutSolidSphere(0.05,100,10.0);
glPopMatrix();
//Mars Moon(Deimos)
glRotatef(rM,0.0,0.0,1.0);
glTranslatef(-0.2,0.0,0.0);
glColor3f(0.8, 0.8, 0.8);
glutSolidSphere(0.05,100,10.0);
glPopMatrix();
//Venus
glRotatef(rE,0.0,0.0,1.0);
glTranslatef(0.3,0.0,1.0);
glColor3f(0.0, 0.0, 1.0);
glutSolidSphere(0.05,100,10);
rE+=1; //velocidad de la rotacion de la tierra
rM+=1.5; //velocidad de la rotacion de la luna
rMars+=0.9; //velocidad de la rotacion de marte
rVenus+=1.1;
glFlush();
glutSwapBuffers();
}

void reshape(int w, int h)
{
if (w == 0 || h == 0) return;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(39.0,(GLdouble)w/(GLdouble)h,0.6,21.0);
glMatrixMode(GL_MODELVIEW);
glViewport(0,0,w,h); 
}

void Timer(int value)
{
glutTimerFunc(10,Timer,0);
glutPostRedisplay();
}
