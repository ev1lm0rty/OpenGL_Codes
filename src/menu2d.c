void drawBitmapText(char *string,float x,float y,float z) 
{  
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; *c != ''; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}


void render(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();

	drawBitmapText("Osama Hosam's OpenGL Tutorials",200,200,0);
	glutSwapBuffers(); 
}