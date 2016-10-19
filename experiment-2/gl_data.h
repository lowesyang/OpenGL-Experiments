#include <gl/glut.h>

GLfloat dy = 0, thelta = 0, spe = 1;
GLfloat rx = 0.6f;

GLfloat desk_body[8][3] = {		//������ά������
	{ -0.2f, -0.16f, -0.025f },
	{ 0.2f, -0.16f, -0.025f },
	{ 0.2f, 0.16f, -0.025f },
	{ -0.2f, 0.16f, -0.025f },
	{ -0.2f, -0.16f, 0.025f },
	{ 0.2f, -0.16f, 0.025f },
	{ 0.2f, 0.16f, 0.025f },
	{ -0.2f, 0.16f, 0.025f }
};

GLfloat desk_leg[8][3] = {		//������ά������
	{ -0.025f, -0.025f, -0.075f },
	{ 0.025f, -0.025f, -0.075f },
	{ 0.025f, 0.025f, -0.075f },
	{ -0.025f, 0.025f, -0.075f },
	{ -0.025f, -0.025f, 0.075f },
	{ 0.025f, -0.025f, 0.075f },
	{ 0.025f, 0.025f, 0.075f },
	{ -0.025f, 0.025f, 0.075f }
};

int cubic[6][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 0, 1, 5, 4 },
	{ 3, 2, 6, 7 },
	{ 4, 5, 6, 7 },
	{ 0, 4, 7, 3 }
};

void drawCubic(GLfloat x, GLfloat y, GLfloat z, GLfloat(*vert)[3], int(*cubic)[4]);		//����������
	
void drawDesk(GLfloat x, GLfloat y, GLfloat z);											//��������

void transform();																		//ƫ��������