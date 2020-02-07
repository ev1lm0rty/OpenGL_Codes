#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
using namespace std; 
int pntX1, pntY1, r;

void plot(int x, int y)
{
glBegin(GL_POINTS);
glVertex2i(x+pntX1, y+pntY1);
glEnd();
}

void myInit (void)
{
glClearColor(1.0, 1.0, 1.0, 0.0);
glColor3f(0.0f, 0.0f, 0.0f);
glPointSize(2.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-200.0, 200.0, -200.0, 200.0);
}

void midPointCircleAlgo()
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
glPointSize(2);
glBegin(GL_POINTS);
glVertex2i(0,0);
glEnd();
glColor3f(1.0,0.0,0.0);



int x = 0;
int y = r;
float decision = 1 - r;
plot(x, y);

while (x <= y)
{
    if (decision < 0)
    {
        x++; 
        decision += 2*x+3;
    }
    else
    {
        y--;
        x++;
        decision += 2*(x-y)+5;
    }
    plot(x, y);
    plot(x, -y);
    plot(-x, y);
    plot(-x, -y);
    plot(y, x);
    plot(-y, x);
    plot(y, -x);
    plot(-y, -x);
}

}

void myDisplay(void)
{

glClear (GL_COLOR_BUFFER_BIT);
glColor3f (0.0, 0.0, 0.0);
glPointSize(1.0);

midPointCircleAlgo();

glFlush ();

}

int main(int argc, char** argv)
{
cout << "Enter the coordinates of the center:\n\n" << endl;

cout << "X-coordinate   : "; cin >> pntX1;
cout << "\nY-coordinate : "; cin >> pntY1;
cout << "\nEnter radius : "; cin >> r;

glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (400, 400);
glutInitWindowPosition (200, 200);
glutCreateWindow ("CIRCLE ");
glutDisplayFunc(myDisplay);
myInit ();
glutMainLoop();
return 0;

} 