#define  GL_SILENCE_DEPRECATION
#include <GLUT/glu.h>
#include <iostream>
#include <math.h>

//function protypes
void matrixmultiply(float trans[3][3],float org_points[3][3]);
void scaling();
void choice();
void rotation();

using namespace std;



float x1,x2,x3,y,y2,y3;
float new_points[3][3],p[3][3];

int flag=0;
char selection{};




void myInit()
{
glClearColor(0,0,0,1);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(-300,300,-300,300);


}

void figuredisplay(float a1,float a2,float b1,float b2,float c1,float c2)
{
    
glColor4f(1,0,0,1);
glBegin(GL_POLYGON);
glVertex2f(a1,a2);
glVertex2f(b1,b2);
glVertex2f(c1,c2);
glEnd();
glFlush();
}

void transform()
{
glClear(GL_COLOR_BUFFER_BIT);
    
    
   if(flag==0)
   {
    cout << "Enter x coordinate for 1 corner of a triangle" << endl;
    cin >> x1;
    cout << "Enter y coordinate for 1 corner of a triangle" << endl;
    cin >> y;
    cout << "Enter x coordinate for 2 corner of a triangle" << endl;
    cin >> x2;
    cout << "Enter y coordinate for 2 corner of a triangle" << endl;
    cin >> y2;
    cout << "Enter x coordinate for 3 corner of a triangle" << endl;
    cin >> x3;
    cout << "Enter y coordinate for 3 corner of a triangle" << endl;
    cin >> y3;
   }

p[0][0]=x1;
p[0][1]=x2;
p[0][2]=x3;
p[1][0]=y;
p[1][1]=y2;
p[1][2]=y3;
p[2][0]=1;
p[2][1]=1;
p[2][2]=1;

if(flag==0)
figuredisplay(x1,y,x2,y2,x3,y3);

    if(flag == 1)
    {
        choice();
    }
    
}

void choice()
{
    cout << "enter s for scaling " << endl;
    cout << "enter r for rotation " << endl;
    cin >> selection;
    
    if (selection == 's' || selection == 'S')
    {
         glClearColor(0.0,0.0,0,1.0);
              scaling();
         flag=1;
        
    }
    
    if (selection == 'r' || selection == 'R')
    {
         glClearColor(0.0,1.0,0,1.0);
              rotation();
         flag=1;
        
    }
}

void scaling()
{
float sx,sy;
float t[3][3];
cout<<"For scaling the figure you need to provide scaling factors"<<endl;
cout<<"sx";
cin>>sx;
cout<<"sy";
cin>>sy;


t[0][0]=sx;
t[0][1]=0;
t[0][2]=0;
t[1][0]=0;
t[1][1]=sy;
t[1][2]=0;
t[2][0]=0;
t[2][1]=0;
t[2][2]=1;

matrixmultiply(t,p);

}

void rotation()
{
float theta_deg,theta_rad;
char ch;
float t[3][3];
cout<<"For rotating the figure you need to provide rotation angle"<<endl;
cout<<"Enter Rotation Angle: ";
cin>>theta_deg;
cout<<"Do you want to rotate it anticlockwise or clockwise? Enter a for anticlockwise and c for clockwise:";
cin>>ch;

theta_rad=(3.14/180)*theta_deg;
if(ch=='a')
{
t[0][0]=cos(theta_rad);
cout<<t[0][0];
t[0][1]=-sin(theta_rad);
t[0][2]=0;
t[1][0]=sin(theta_rad);
t[1][1]=cos(theta_rad);
t[1][2]=0;
t[2][0]=0;
t[2][1]=0;
t[2][2]=1;
}

else if(ch=='c')
{
t[0][0]=cos(theta_rad);
t[0][1]=sin(theta_rad);
t[0][2]=0;
t[1][0]=-sin(theta_rad);
t[1][1]=cos(theta_rad);
t[1][2]=0;
t[2][0]=0;
t[2][1]=0;
t[2][2]=1;
}

matrixmultiply(t,p);

}


void matrixmultiply(float trans[3][3],float org_points[3][3])
{

int x1f,x2f,x3f,y1f,y2f,y3f;

int i,j,k;
for(i=0;i<3;i++)
{
    for(j=0;j<3;j++)
        {
        new_points[i][j]=0;
            for(k=0;k<3;k++)
                {
                    new_points[i][j]+=trans[i][k]*org_points[k][j];
                }
        }
}

x1f=new_points[0][0];
x2f=new_points[0][1];
x3f=new_points[0][2];
y1f=new_points[1][0];
y2f=new_points[1][1];
y3f=new_points[1][2];

figuredisplay(x1f,y1f,x2f,y2f,x3f,y3f);


p[0][0]=x1f;
p[0][1]=x2f;
p[0][2]=x3f;
p[1][0]=y1f;
p[1][1]=y2f;
p[1][2]=y3f;
p[2][0]=1;
p[2][1]=1;
p[2][2]=1;
}



void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        flag=1;
        glutPostRedisplay();
        
    }
}


int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600,600);
glutInitWindowPosition(10,10);
glutCreateWindow("Transformation");

myInit();

glutDisplayFunc(transform);
glutMouseFunc(mouse);
cout<<endl;
cout<<"\t2D Transformations \n Right Click and choose from Drop Down Menus"<<endl<<endl;

glutMainLoop();
return 0;
}
