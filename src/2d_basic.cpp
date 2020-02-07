#include<GL/glut.h>
#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;
int numberOfPoints;
int count = 0;
float arr[20][2];
float ox = 200, oy = 200; //Origin Coordinates
void drawLine(float x1, float ya1, float x2, float ya2){
  glColor3f(0,0,1);
  glBegin(GL_LINES);
    glVertex2f(x1,ya1);
    glVertex2f(x2,ya2);
  glEnd();
  glFlush();
}


void drawPolygon(float (*arr)[2], int n){
  glColor3f(1,0,0);
  glBegin(GL_LINE_LOOP);
    for(int i = 0; i < n; i++)
      glVertex2f(arr[i][0],arr[i][1]);
  glEnd();
  glFlush();
}
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  //drawing axes
  drawLine(-200,0,200,0);
  drawLine(0,-200,0,200);
  drawPolygon(arr,numberOfPoints);

}
void init(void)
{
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(-200,200,-200,200.0);
}

void tranformation(float arr[][2], int n, float matrix[][3])
{
	display();
	drawPolygon(arr,numberOfPoints);
  for(int p = 0; p<n; p++){
    float tar[][1] = {{0},{0},{0}};
    float ar[][1] = {{arr[p][0]},{arr[p][1]},{1}};
    for(int i=0;i<3;i++)
    {
        for(int k=0;k<1;k++)
        {
            for(int j=0;j<3;j++)
              tar[i][k] += matrix[i][j]*ar[j][k];
        }
    }
      arr[p][0] = tar[0][0];
      arr[p][1] = tar[1][0];
  }

void keyboard(unsigned char key, int x, int y)
{
  float theta,sx,sy;
  switch (key)
  {
    case 'a': case 'A':{
        printf("anticlockwise rotation\n");
      theta = 5;
      theta *= (3.1415926/180);//converting degree into radians
      float sine = sin(theta);
      float cosine = cos(theta);
      float matrix[][3] = {{cosine,-sine,0},{sine,cosine,0},{0,0,1}};
      tranformation(arr,numberOfPoints,matrix);
    break;
  }
    case 'c': case 'C':{
      printf("clockwise rotation\n");
      theta = -5;
      theta *= (3.1415926/180);//converting degree into radians
      float sine = sin(theta);
      float cosine = cos(theta);
      float matrix[][3] = {{cosine,-sine,0},{sine,cosine,0},{0,0,1}};
      tranformation(arr,numberOfPoints,matrix);
    break;
  }
    case 'b': case 'B':{
        printf("make it big\n");
      sx=1.5;
      sy=1.5;
      float matrix[][3] = {{sx,0,0},{0,sy,0},{0,0,1}};
      tranformation(arr,numberOfPoints,matrix);
    break;
  }
    case 's': case 'S':{
        printf("make it small\n");
      sx=0.75;
      sy=0.75;
      float matrix[][3] = {{sx,0,0},{0,sy,0},{0,0,1}};
      tranformation(arr,numberOfPoints,matrix);
    break;
  }
  }
}
int main(int argc, char** argv)
{
    printf("Enter the number of points:\n");
    cin>>numberOfPoints;

    for(int i=0;i<numberOfPoints;i++)
    {
        printf("Enter %d points:\n",i+1);
        cin>>arr[i][0];
        cin>>arr[i][1];
    }

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(400,400);
  glutCreateWindow("Tranformations:");

  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
