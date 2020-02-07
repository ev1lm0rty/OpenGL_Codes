#include<GL/glut.h>
#include<iostream>
#include<math.h>

GLint ww=400, wh=400;
int count = 0, x1=0, ya1=0, x2=0, ya2=0,r=0;
int wx1 = 0,wy1 = 0,wx2 =100,wy2 =100;

void init(void)
{
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(-200,200,-200,200.0);
}
int calculateX(int y){
  return (((ya1-y)*(x2-x1))/((ya2-ya1)*1.0))+x1;
}
int calculateY(int x){
  return ya1-(((x1-x)*(ya2-ya1))/((x2-x1)*1.0));
}
void clipline(int temp1 ,int temp2){

    if(temp1 == 0 || temp2 == 0){//If atleast one point is inside window
      int x,y,temp = temp1;
      if(temp1 == 0)
        temp = temp2;
      if(temp == 8){
        y = wy2;
        x = calculateX(y);
      }
      else if(temp == 2){
        x = wx2;
        y = calculateY(x);
      }
      else if(temp == 4){
        y = wy1;
        x = calculateX(y);
      }
      else if(temp == 1){
        x = wx1;
        y = calculateY(x);
      }
      else if(temp == 9){
        x = wx1;
        y = calculateY(x);
        if(y>wy2){
          y = wy2;
          x = calculateX(y);
        }
      }
      else if(temp == 10){
        x = wx2;
        y = calculateY(x);
        if(y>wy2){
          y = wy2;
          x = calculateX(y);
        }
      }
      else if(temp == 5){
        x = wx1;
        y = calculateY(x);
        if(y<wy1){
          y = wy1;
          x = calculateX(y);
        }
      }
      else{
        x = wx2;
        y = calculateY(x);
        if(y<wy1){
          y = wy1;
          x = calculateX(y);
        }
      }

      if(temp1 == 0){
        x2 = x;
        ya2 = y;
      }
      else{
        x1 = x;
        ya1 = y;
      }
      printf("\nIntersection points: %d %d\n",x,y);
    }
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(x1,ya1);
    glVertex2i(x2,ya2);
    glEnd();
  }
void cohenSutherland(){
  int temp1 = 0;
  if(x1<wx1)
      temp1+= 1;
  if(x1>wx2)
      temp1+= 2;
  if(ya1<wy1)
      temp1+= 4;
  if(ya1>wy2)
      temp1+= 8;

  int temp2 = 0;
  if(x2<wx1)
      temp2+= 1;
  if(x2>wx2)
      temp2+= 2;
  if(ya2<wy1)
      temp2+= 4;
  if(ya2>wy2)
      temp2+= 8;

  printf("\n%d %d",temp1,temp2);
  if((temp1|temp2) == 0){
    printf("\nVisible");
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(x1,ya1);
    glVertex2i(x2,ya2);
    glEnd();
  }
  else if((temp1&temp2) == 1||(temp1&temp2) == 2||(temp1&temp2) == 4||(temp1&temp2) == 8)
    printf("\nInvisible");
  else{
    printf("\nPartial Visible");
    clipline(temp1,temp2);
  }
}
void plotPoint(GLint x,GLint y)
{
 glPointSize(2);
 glBegin(GL_POINTS);
  glVertex2i(x,y);
 glEnd();
}
void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
 if(button == GLUT_LEFT_BUTTON && action == GLUT_UP)
 {
  if(!count)
  {
   x1=xMouse-200;
   ya1=wh-yMouse-200;
   count = 1;
   printf("First point %d, %d entered.\n",x1,ya1);
  //drawing axes
glColor3f(0.0,0.0,1.0);
 glBegin(GL_LINES);
  glVertex2i(-200,0);
  glVertex2i(200,0);
  glVertex2i(0,-200);
  glVertex2i(0,200);
 glEnd();
  }
  else
  {
    x2=xMouse-200;
    ya2=wh-yMouse-200;
    printf("Second point %d, %d entered.\n",x2,ya2);
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(x1,ya1);
    glVertex2i(x2,ya2);
    glEnd();
    cohenSutherland();
    count=0;
    printf("\nPoints reset.\n\n");
  }
 }
 glFlush();
}

void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.2,0.2,0.2);
  glBegin(GL_POLYGON);
  glVertex2f(wx1,wy1);
  glVertex2f(wx1,wy2);
  glVertex2f(wx2,wy2);
  glVertex2f(wx2,wy1);
  glEnd();
  glColor3f(0.0,0.0,1.0);
 glBegin(GL_LINES);
  glVertex2i(-200,0);
  glVertex2i(200,0);
  glVertex2i(0,-200);
  glVertex2i(0,200);
 glEnd();
}
int main(int argc, char** argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowPosition(0,0);
 glutInitWindowSize(400,400);
 glutCreateWindow("Cohen Sutherland");
  init();
 glutDisplayFunc(display);
 glutMouseFunc(mousePtPlot);
 glutMainLoop();
 return 0;
}