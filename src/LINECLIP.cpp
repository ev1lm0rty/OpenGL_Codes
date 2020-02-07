//COHEN-SUTHERLAND LINE CLIPPING CODE
#include <GL/glut.h>
#include <stdio.h>

static int LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8,xl=200,yl=200,xh=400,yh=400,a1=0,b1=0,a2=0,b2=0;
GLint ww = 600, wh = 600, count = 0;
GLint accept = 0; 	//decides if line is to be drawn

int getCode(int x,int y)
{
int code = 0;
if(y > yh) code |=TOP;
if(y < yl) code |=BOTTOM;
if(x < xl) code |=LEFT;
if(x > xh) code |=RIGHT;
return code;
}

void setPixel(GLint x, GLint y)
{
glColor3f(0.0,1.0,0.0);
glBegin(GL_POINTS);
glVertex2i(x,y);
glEnd();
}

void drawline()
{
 glColor3f(0.0,1.0,0.0);
 glBegin(GL_LINES);
  glVertex2i(a1,b1);
  glVertex2i(a2,b2);
 glEnd();
}


void lineclip()
{
    //clipping window
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0,0.0,0.0);
        glVertex2i(xl,yl);
        glVertex2i(xh,yl);
        glVertex2i(xh,yh);
        glVertex2i(xl,yh);
    glEnd();

    glFlush();
}

void check()
{
    int outcode1=getCode(a1,b1), outcode2=getCode(a2,b2);

	while(1){
		float m =(float)(b2-b1)/(a2-a1);
		//Both points inside. Accept line
		if(outcode1==0 && outcode2==0){
			accept = 1;
			break;
		}
		//AND of both codes != 0.Line is outside. Reject line
		else if((outcode1 & outcode2)!=0){
			break;
		}else{
			int x,y;
			int temp;
			//Decide if point1 is inside, if not, calculate intersection
			if(outcode1==0)
				temp = outcode2;
			else
				temp = outcode1;
			//Line clips top edge
			if(temp & TOP){
				x = a1+ (yh-b1)/m;
				y = yh;
			}
			else if(temp & BOTTOM){ 	//Line clips bottom edge
				x = a1+ (yl-b1)/m;
				y = yl;
			}else if(temp & LEFT){ 	//Line clips left edge
				x = xl;
				y = b1+ m*(xl-a1);
			}else if(temp & RIGHT){ 	//Line clips right edge
				x = xh;
				y = b1+ m*(xh-a1);
			}
			//Check which point we had selected earlier as temp, and replace its co-ordinates
			if(temp == outcode1){
				a1 = x;
				b1 = y;
				outcode1 = getCode(a1,b1);
			}else{
				a2 = x;
				b2 = y;
				outcode2 = getCode(a2,b2);
			}
		}
	}
    if(accept)
    {
        drawline();
    }
}



void mousePt(GLint button, GLint action, GLint xmouse, GLint ymouse)
{
    if(button == GLUT_LEFT_BUTTON && action == GLUT_UP)
    {
        if(!count)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            a1 = xmouse;
            b1 = wh - ymouse;
            setPixel(a1,b1);
            count = 1;
        }
        else
        {
            a2 = xmouse;
            b2 = wh - ymouse;
            setPixel(a2,b2);
            drawline();
            count = 0;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && action == GLUT_UP)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        check();
    }
    glFlush();
}

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,600.0,0.0,600.0);
}


int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(50,100);
glutInitWindowSize(600,600);
glutCreateWindow("Cohen-Sutherland Line Clipping");
init();
glutDisplayFunc(lineclip);
glutMouseFunc(mousePt);

glutMainLoop();
return 0;
}
