// glutEx1.cpp : 定义控制台应用程序的入口点。
//
//注意FPS函数的应用

#include <stdlib.h>
#include <gl/glut.h>
#include <stdio.h>
#include <string.h>

#include "stanford_bunny.h"

float eye[] = { 0, 4, 6 };
float center[] = { 0, 0, 0 };
float fDistance = 0.2f;
float fRotate = 0;
bool bAnim = false;

bool bDrawList = false;
GLint tableList = 0;

int bunnyNum = 1;						//the number of bunny
GLfloat tableLen = 2.5, tableWid = 2.0;		//initial size of table
GLfloat spaceX = 1.5, spaceZ=1.0;						//the space between two adjacent bunnies

void DrawTable()
{
	glPushMatrix();
	glTranslatef(0, 3.7, 0);
	glScalef(2*tableLen, 0.5, 2*tableWid);
	glutSolidCube(1.0); 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(tableLen*3/5, 2, tableWid*3/5);
	glScalef(0.7, 3, 0.7);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-tableLen * 3 / 5, 2, -tableWid * 3 / 5);
	glScalef(0.7, 3, 0.7);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(tableLen * 3 / 5, 2, -tableWid * 3 / 5);
	glScalef(0.7, 3, 0.7);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-tableLen * 3 / 5, 2, tableWid * 3 / 5);
	glScalef(0.7, 3, 0.7);
	glutSolidCube(1.0);
	glPopMatrix();
}

//draw list of bunny
void DrawBunnyList(){
	int i;
	int row, col;					//max number in row and column
	int isDraw = 0;					//the number of bunnies have been drawed
	row = 2 * tableLen / 1.6;
	col = 2 * tableWid / 0.9 - 1;

	if (row * col < bunnyNum){
		tableLen += 1.5;
		tableWid += 1.0;
		row = 2 * tableLen / 1.6;
		col = 2 * tableWid / 0.9 - 1;
	}

	GLfloat initX = ((row - 1)*spaceX) / 2 - 1.5;		//the initial x of the first bunny
	GLfloat initZ = ((col - 1)*spaceZ + 0.6) / 2 - 0.36;	//the initial z of the first bunny
	GLfloat x = initX;

	for (i = 0; i < bunnyNum; i++){
		DrawBunny(x, initZ);
		x -= spaceX;
		isDraw++;
		if (isDraw % row == 0){
			x = initX;
			initZ -= spaceZ;
		}
	}
}

GLint GenTableList()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);

	glPushMatrix();
	glTranslatef(1.5, 4.5, 0);
	glScalef(2, 2, 2);
	DrawBunnyList();
	glPopMatrix();

	DrawTable();

	glEndList();
	return lid;
}

void Draw_Table_List()
{
	glCallList(tableList);
}


void DrawScene()
{
	glPushMatrix();
	glTranslatef(1.5, 4.5, 0);
	glScalef(2, 2, 2);
	DrawBunnyList();
	glPopMatrix();
	DrawTable();
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45, whRatio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }

	case 'a':
	{
				eye[0] += fDistance;
				center[0] += fDistance;
				break;
	}
	case 'd':
	{
				eye[0] -= fDistance;
				center[0] -= fDistance;
				break;
	}
	case 'w':
	{
				eye[1] -= fDistance;
				center[1] -= fDistance;
				break;
	}
	case 's':
	{
				eye[1] += fDistance;
				center[1] += fDistance;
				break;
	}
	case 'z':
	{
				eye[2] *= 0.95;
				break;
	}
	case 'c':
	{
				eye[2] *= 1.05;
				break;
	}
	case 'l':
	{
				bDrawList = !bDrawList;	// 切换显示列表和非显示列表绘制方式
				break;
	}
	case ' ':
	{
				bAnim = !bAnim;
				break;
	}

	// add and sub bunny
	case 'i':	//add bunny
	{	
				bunnyNum++;
				glDeleteLists(tableList, 1);
				tableList = GenTableList();			//redraw display list
				break;
	}
	case 'k':	//sub bunny
	{
				bunnyNum--;
				if (bunnyNum < 0) bunnyNum = 0;
				glDeleteLists(tableList, 1);
				tableList = GenTableList();			//redraw display list
				break;
	}
	default: break;
	}
}

void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	if (bDrawList)
		strcpy(mode, "display list");
	else
		strcpy(mode, "naive");

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(buffer, "FPS:%4.2f %s",
			frame*1000.0 / (time - timebase), mode);
		timebase = time;
		frame = 0;
	}

	char *c;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glOrtho(0, 480, 0, 480, -1, 1);    // 位置正投影
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glRasterPos2f(10, 10);
	for (c = buffer; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glEnable(GL_DEPTH_TEST);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0.5, 0, 1);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0, 5, 50)，Y轴向上

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat gray[] = { 0.4, 0.4, 0.2, 1.0 };
	GLfloat light_pos[] = { 10, 80, 10, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glEnable(GL_LIGHT0);

	if (bAnim)
		fRotate += 0.5f;
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis

	glScalef(0.4, 0.4, 0.4);
	if (!bDrawList)
		DrawScene();						// old way
	else
		Draw_Table_List();                  // new way

	getFPS();
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Exercise 4");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	tableList = GenTableList();

	glutMainLoop();
	return 0;
}


