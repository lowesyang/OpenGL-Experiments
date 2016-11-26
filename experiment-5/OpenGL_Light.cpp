// glutEx1.cpp : 定义控制台应用程序的入口点。
//


#include <stdlib.h>
#include <gl/glut.h>

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

GLfloat light_color[][4] = {
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 0, 0, 0, 1.0 }
};
int light_index = 0;						//the index of light color
GLfloat light_pos[] = { 5, 5, 5, 1 };
GLfloat no_mat[] = { 0, 0, 0, 1.0 };

GLfloat spot_position[] = { -2, 5, 5, 1 };		//position of spot_dir light
GLfloat spot_direction[] = { 2, -5, -5};		//direction of spot_dir light
GLfloat spot_degree = 30.0;							//angle of spot direction light

void Draw_Leg(GLfloat r,GLfloat g,GLfloat b);

void Draw_Triangle() // This function draws a triangle with RGB colors
{

	glPushMatrix();
	glTranslatef(0, 0, 4 + 1);
	glRotatef(90, 1, 0, 0);
	GLfloat teaColor[] = { 1, 0.95, 0.23, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, teaColor);
	GLfloat white[] = { 1, 1, 1, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 55.0);
	glutSolidTeapot(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	GLfloat deskColor[] = { 1, 0, 0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, deskColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg(0,1,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg(1,1,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg(0,1,1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg(0,0,1);
	glPopMatrix();

}

void Draw_Leg(GLfloat r, GLfloat g, GLfloat b){
	GLfloat coeff[4];
	coeff[0] = r;
	coeff[1] = g;
	coeff[2] = b;
	coeff[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,coeff);
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	if (bPersp) {
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
		//glFrustum(-3, 3, -3, 3, 3,100);
	}
	else {
		glOrtho(-3, 3, -3, 3, -100, 100);
	}

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

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'a': {
				  eye[0] -= 0.2f;
				  center[0] -= 0.2f;
				  break;
	}
	case 'd': {
				  eye[0] += 0.2f;
				  center[0] += 0.2f;
				  break;
	}
	case 'w': {
				  eye[1] -= 0.2f;
				  center[1] -= 0.2f;
				  break;
	}
	case 's': {
				  eye[1] += 0.2f;
				  center[1] += 0.2f;
				  break;
	}
	case 'z': {
				  eye[2] -= 0.2f;
				  center[2] -= 0.2f;
				  break;
	}
	case 'c': {
				  eye[2] += 0.2f;
				  center[2] += 0.2f;
				  break;
	}
	
		//light controller
	case 'u':{
				 light_pos[1] += 0.2f;
				 break;
	}
	case 'j':{
				 light_pos[1] -= 0.2f;
				 break;
	}
	case 'h':{
				 light_pos[0] -= 0.2f;
				 break;
	}
	case 'k':{
				 light_pos[0] += 0.2f;
				 break;
	}
	case 'y':{
				 light_pos[2] += 0.2f;
				 break;
	}
	case 'i':{
				 light_pos[2] -= 0.2f;
				 break;
	}
	case 'm':{
				 light_index = light_index ? 0 : 1;
				 break;
	}

		//spot light direction controller
	case 'g':{
				 spot_direction[1] += 0.2f;
				 break;
	}
	case 'b':{
				 spot_direction[1] -= 0.2f;
				 break;
	}
	case 'v':{
				 spot_direction[0] -= 0.2f;
				 break;
	}
	case 'n':{
				 spot_direction[0] += 0.2f;
				 break;
	}
	case '[':{
				 spot_degree -= 1;
				 break;
	}
	case ']':{
				 spot_degree += 1;
				 break;
	}

	}

	updateView(wHeight, wWidth);
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color[light_index]);

	//spot direction light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color[0]);
	glLightfv(GL_LIGHT1, GL_POSITION, spot_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_degree);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.5);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Triangle();						// Draw triangle

	if (bAnim) fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


