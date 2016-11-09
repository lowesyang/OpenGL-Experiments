#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>
#include <stdio.h>
#define PI 3.141593

float fTranslate;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

//variables changed by controller
float deltaDeg = 0;		//the degree of teapot rotation
float deltaX = 0;		//the offset of x in teapot coordinate
float deltaY = 0;		//the offset of y in teapot coordinate

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene()
{
	glPushMatrix();
	glTranslatef(deltaX, deltaY, 3.8 );
	glRotatef(90, 1, 0, 0); //notice the rotation here, you may have a TRY removing this line to see what it looks like.
	glRotatef(deltaDeg, 0, 1, 0);

	glutSolidTeapot(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 2.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 0.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 0.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 0.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 0.5);
	Draw_Leg();
	glPopMatrix();
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp){
		//when 'p' operation, hint: use FUNCTION gluPerspective
		gluPerspective(30.0f, whRatio,0.1f, 100.0f);
	}
	else
		glOrtho(-3, 3, -3, 3, -100, 100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float distance = 6.0;			//the distance between the basic point and camera
float eye[] = { 0, 0, 6 };
float center[] = { 0, 0, 0 };
//todo; hint: you may need another ARRAY when you operate the teapot

float ver_angle = 0, hori_angle = 0;	//the angle of the line of basic point and camera, and coordinate

float cameraAngle = 0;					//the angle of camera self rotation

float offsetX = 0, offsetY = 0;			//the carema's offset of x and y

void key(unsigned char k, int x, int y)
{
	
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth); break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'a': {//horizontal anticlockwise
				  hori_angle -= 2;
				  break;
	}
	case 'd': {//horizontal clockwise
				  hori_angle += 2;
				  break;
	}
	case 'w': {//vertical anticlockwise
				  ver_angle += 2;
				  if (ver_angle >= 90) ver_angle = 89;
				  break;
	}
	case 's': {//vertical clockwise
				  ver_angle -= 2;
				  if (ver_angle<=-90) ver_angle=-89;
				  break;
	}
	case 'z': {//self anticlockwise
				  cameraAngle += 2;
				  break;
	}
	case 'c': {//self clockwise
				  cameraAngle -= 2;
				  break;
	}


	//茶壶相关操作
	case 'l': {//right
				  deltaX += 0.1;
				  if (deltaX > 2.5) deltaX -= 0.1;
				  break;
	}
	case 'j': {//left
				  deltaX -= 0.1;
				  if (deltaX < -2.5) deltaX += 0.1;
				  break;
	}
	case 'i': {//forward
				  deltaY += 0.1;
				  if (deltaY > 2) deltaY -= 0.1;
				  break;
	}
	case 'k': {//back
				  deltaY -= 0.1;
				  if (deltaY < -2) deltaY += 0.1;
				  break;
	}
	case 'e': {//rotate
				  deltaDeg+=5;
				  break;
	}

	case 't':{//up
				 offsetY += 0.1;
				 break;
	}
	case 'g':{//down
				 offsetY -= 0.1;
				 break;
	}
	case 'f':{//left
				 offsetX -= 0.1;
				 break;
	}
	case 'h':{//right
				 offsetX += 0.1;
				 break;
	}

	case 'v':{//get closed
				 distance -= 0.2;
				 break;
	}
	case 'n':{//far awayn
				 distance += 0.2;
				 break;
	}
	}

	
	//recompute the position of camera
	eye[0] = offsetX + distance*cos(ver_angle * PI / 180)*sin(hori_angle * PI / 180);
	eye[1] = offsetY+ distance*sin(ver_angle * PI / 180);
	eye[2] = distance*cos(ver_angle * PI / 180)*cos(hori_angle * PI / 180);

}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	glRotatef(cameraAngle, 0.0, 1.0f, 0.0);				//the direction of "look at" rotate	

	gluLookAt(eye[0], eye[1], eye[2],
		offsetX+center[0], offsetY+center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 快门法向为Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();						// Draw Scene

	if (bAnim) fRotate += 0.5f;

	//todo; hint: when you want to rotate the teapot, you may like to add another line here =)

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Ex 3");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}