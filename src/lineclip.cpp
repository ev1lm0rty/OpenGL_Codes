#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include<math.h>
using namespace std;


GLint ww=200, wh=200;
double x1=0,Y1=0,x2=0,y2=0,gx1=0,gx2=0,gy1=0,gy2=0,radius=0;
GLint count = 0;

void plot(GLint x, GLint y)
{
    glColor3f(0,0,1);
    glPointSize(5);
    printf("Ploted %d and %d\n",x,y);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void drawLine(int x1,int y1,int x2,int y2)
{
    glColor3f(0,0,1);
    glPointSize(4);
    glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2,y2);
	glEnd();
	glFlush();

}


void myInit (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
}




const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000


const int x_max = 100;
const int y_max = 100;
const int x_min = -150;
const int y_min = -150;


int computeCode(double x, double y)
{

    int code = INSIDE;

    if (x < x_min)       // to the left of rectangle
        code |= LEFT;
    else if (x > x_max)  // to the right of rectangle
        code |= RIGHT;
    if (y < y_min)       // below the rectangle
        code |= BOTTOM;
    else if (y > y_max)  // above the rectangle
        code |= TOP;

    return code;
}

void clip(double x1, double y1,
                         double x2, double y2)
{

    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

        bool accept = false;

    while (true)
    {
        if ((code1 == 0) && (code2 == 0))
        {

            accept = true;
            break;
        }
        else if (code1 & code2)
        {

            break;
        }
        else
        {
            int code_out;
            double x, y;

            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP)
            {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept)
    {
        printf("Line accepted from %f,%f to %f,%f",x1,y1,x2,y2);
        gx1=x1;
        gx2=x2;
        gy2=y2;
        gy1=y1;

            }
    else
        printf("Line rejected\n");
}


void myDisplay(void)
{

	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 1.0, 0.0);
	glPointSize(2.0);
    glBegin(GL_LINES);
    glVertex2i(x_min,y_min);
    glVertex2i(x_max,y_min);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(x_max,y_max);
    glVertex2i(x_max,y_min);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(x_max,y_max);
    glVertex2i(x_min,y_max);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(x_min,y_max);
    glVertex2i(x_min,y_min);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2i(250,0);
    glVertex2i(-250,0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(0,250);
    glVertex2i(0,-250);
    glEnd();

    drawLine(gx1,gy1,gx2,gy2);



	glFlush ();
}


void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
 if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
 {
  if(!count)
  {

   x1=(xMouse-250);
   Y1=-(yMouse-250);
   count = 1;
  gx1=x1;

    gy1=Y1;
    plot(x1,Y1);
   printf("First point %f, %f entered.\n",x1,Y1);
  }
  else
  {
   x2=(xMouse-250);
   y2=-(yMouse-250);
   printf("Second point %f, %f entered.\n",x2,y2);
   gx2=x2;
    gy2=y2;
    plot(x2,y2);
    drawLine(gx1,gy1,gx2,gy2);
   count=0;
   printf("Points reset.\n");
  }
 }
 if(button==GLUT_RIGHT_BUTTON && action==GLUT_DOWN)
 {
     clip(gx1,gy1,gx2,gy2);
     printf("LINES CLIPPED..!!\n");
 }
 glFlush();
}



int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500,500);
	glutInitWindowPosition (0,0);
	glutCreateWindow ("Line Drawing Alogrithms");

	myInit ();
	glutMouseFunc(mousePtPlot);
	glutDisplayFunc(myDisplay);
	glutMainLoop();

}
