#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
int x,y;
void init(void)
{
glClearColor(1.0,1.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0,200,0,150);
}
void lineSegment(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,1.0,0.0);
glPointSize(4.0);
glBegin(GL_QUADS);  //roof
glVertex2i(180,100);
glVertex2i(160,125);
glVertex2i(100,125);
glVertex2i(80,100);
glEnd();
glFlush();

glColor3f(1.0,0.0,0.0);
glPointSize(4.0);

glBegin(GL_QUADS); // frame
glVertex2i(160,50);
glVertex2i(160,100);
glVertex2i(100,100);
glVertex2i(100,50);
glEnd();

glFlush();

glColor3f(1.0,1.0,1.0);
glPointSize(4.0);

glBegin(GL_QUADS);  //door
glVertex2i(120,50);
glVertex2i(120,75);
glVertex2i(110,75);
glVertex2i(110,50);
glEnd();

glFlush();

glColor3f(1.0,0.5,0.5);
glPointSize(4.0);

glBegin(GL_QUADS);  // window
glVertex2i(150,75);
glVertex2i(150,90);
glVertex2i(135,90);
glVertex2i(135,75);
glEnd();

glFlush();

glColor3f(1.0,0.5,1.0);
glPointSize(4.0);

glBegin(GL_QUADS);
glVertex2i(150,125);  // chimney
glVertex2i(150,135);
glVertex2i(135,135);
glVertex2i(135,125);
glEnd();

glFlush();

glColor3f(0.0,0.0,0.0);
glPointSize(4.0);

glBegin(GL_LINES);
glVertex2i(150,80); //verticle line1
glVertex2i(135,80);
glEnd();

glFlush();

glColor3f(0.0,0.0,0.0);
glPointSize(4.0);

glBegin(GL_LINES);  //verticle line 2
glVertex2i(150,85);
glVertex2i(135,85);
glEnd();

glFlush();

glColor3f(0.0,0.0,0.0);
glPointSize(4.0);

glBegin(GL_LINES);  // horizontal line 1
glVertex2i(145,90);
glVertex2i(145,75);
glEnd();

glFlush();

glColor3f(0.0,0.0,0.0);
glPointSize(4.0);

glBegin(GL_LINES);
glVertex2i(140,90);   // horizontal line 2
glVertex2i(140,75);
glEnd();

glFlush();



glColor3f(1.0,0.0,0.0);
glPointSize(4.0);

glBegin(GL_LINES);  //line below the door
glVertex2i(120,50);   
glVertex2i(110,50);
glEnd();

glFlush();


}

void mouse(int button, int state, int mousex, int mousey)
{
x=mousex-0;
y=150-mousey;
if(button==GLUT_LEFT_BUTTON && button==GLUT_DOWN)
{
if(mousex>110 && mousex<120 && mousey>10 && mousey<20)
{
glColor3f(0,1,0);
}
else if(mousex> 130 && mousex<140 && mousey>10 && mousey<20)
{
glColor3f(1,1,1);
}
if (mousex>150 && mousex<160 && mousey>10 && mousey<20)
{
glColor3f(1,0,1);
}
glBegin(GL_QUADS);
glVertex2i(150,125);  // chimney
glVertex2i(150,135);
glVertex2i(135,135);
glVertex2i(135,125);
glEnd();
 glFlush();
}
}
int main(int argc, char**argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(50,100);
glutInitWindowSize(400,300);
glutCreateWindow("Sample Programs");
init();
glutDisplayFunc(lineSegment);
glutMouseFunc(mouse);
glutMainLoop();
return 0;
}