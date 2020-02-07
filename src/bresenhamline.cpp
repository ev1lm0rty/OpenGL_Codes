#include<GL/glut.h>
#include<iostream>

GLint x1=0,y1=0,x2=0,y2=0;
GLint count = 0;

void init(void)
{
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(-200,200,-200,200.0);
}

void draw_pixel(GLfloat x,GLfloat y)
{
 glPointSize(2);
 glBegin(GL_POINTS);
  glVertex2f(x,y);
 glEnd();
}

void BresLine(GLint x1,GLint y1,GLint x2,GLint y2)
{
 //drawing axes
 glColor3f(0.0,0.0,1.0);
 glBegin(GL_LINES);
  glVertex2i(-200,0);
  glVertex2i(200,0);
  glVertex2i(0,-200);
  glVertex2i(0,200);
 glEnd();

 //plot origin
 glColor3f(0.1,1.0,0.1);
 glPointSize(6);
 glBegin(GL_POINTS);
  glVertex2i(0,0);
 glEnd();
 glColor3f(1.0,0.0,0.0);

 //drawing intended line using Bresenham 
 int dx, dy, i, e;
int incx, incy, inc1, inc2;
int x,y;

dx = x2-x1;
dy = y2-y1;

if (dx < 0) dx = -dx;
if (dy < 0) dy = -dy;
incx = 1;
if (x2 < x1) incx = -1;
incy = 1;
if (y2 < y1) incy = -1;
x = x1; y = y1;
if (dx > dy) {
draw_pixel(x, y);
e = 2 * dy-dx;
inc1 = 2*(dy-dx);
inc2 = 2*dy;
for (i=0; i<dx; i++) {
if (e >= 0) {
y += incy;
e += inc1;
}
else
e += inc2;
x += incx;
draw_pixel(x, y);
}

} else {
draw_pixel(x, y);
e = 2*dx-dy;
inc1 = 2*(dx-dy);
inc2 = 2*dx;
for (i=0; i<dy; i++) {
if (e >= 0) {
x += incx;
e += inc1;
}
else
e += inc2;
y += incy;
draw_pixel(x, y);
}
}
}


void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
 BresLine(-70,-10,-50,90); //m > 1 steep,positive
 BresLine(-10,-70,90,-50); //m < 1 gentle positive
 BresLine(-10,70,90,50);   //m > -1 gentle negative
 BresLine(70,-10,50,90);   //m < -1 steep negative
glFlush();
}

//dont use winReshape
/*void winReshape(GLint nw, GLint nh)
{
 glViewport(0,0,nw,nh);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(0.0,GLdouble(nw),0.0,GLdouble(nh));
 ww = nw;
 wh = nh;
}*/

int main(int argc, char** argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowPosition(50,100);
 glutInitWindowSize(400,400);
 glutCreateWindow("Line Drawing: Bresenham");
 
 init();
 glutDisplayFunc(display);
 //glutReshapeFunc(winReshape);

 glutMainLoop();
 return 0;
}
