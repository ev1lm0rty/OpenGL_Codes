#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
float shift=0; //variable to move boat right or left
void init(void)
{
glClearColor(1.0,1.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0,200,0,150);
}
void lineSegment(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0,0.0,1.0);
glPointSize(4.0);

glBegin(GL_QUADS); // river
glVertex2i(200,0);
glVertex2i(200,100);
glVertex2i(0,100);
glVertex2i(0,0);
glEnd();

glFlush();

glColor3f(1.0,0.0,0.0);
glPointSize(4.0);

glBegin(GL_QUADS); // boat
glVertex2i(100,50);
glVertex2i(125,75);
glVertex2i(50,75);
glVertex2i(75,50);
glEnd();

glFlush();


glColor3f(1.0,0.0,1.0);
glPointSize(4.0);

glBegin(GL_TRIANGLES); // boat
glVertex2i(95,75);
glVertex2i(80,90);
glVertex2i(65,75);

glEnd();

glFlush();
glColor3f(0.0,0.0,0.0);
glPointSize(4.0);
glBegin(GL_LINES);
glVertex2i(80,90); //verticle line1
glVertex2i(80,110);
glEnd();
glFlush();
glColor3f(1.0,0.0,0.5);
glPointSize(4.0);
glBegin(GL_TRIANGLES); // boat
glVertex2i(80,100);
glVertex2i(80,110);
glVertex2i(70,105);
glEnd();
glFlush();
}
void key(int key, int x, int y)
{
switch(key)
{
case GLUT_KEY_LEFT:
shift--;
glutPostRedisplay();
break;
case GLUT_KEY_RIGHT:
shift++;
glutPostRedisplay();
break;
}
}
int main(int argc, char**argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(0,0);
glutInitWindowSize(1000,600);
glutCreateWindow("Sample Programs");
init();
glutDisplayFunc(lineSegment);
glutSpecialFunc(key);
glutMainLoop();
return 0;
}
