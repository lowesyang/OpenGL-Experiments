#include "gl_data.h"

void drawCubic(GLfloat x,GLfloat y,GLfloat z,GLfloat (*vert)[3], int (*cubic)[4]){
	int i, j;
	GLfloat vertexs[8][3];
	for (i = 0; i < 8; i++){
		vertexs[i][0] = vert[i][0] + x;
		vertexs[i][1] = vert[i][1] + y;
		vertexs[i][2] = vert[i][2] + z;
	}
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++){		//��6������Ҫ����
		for (j = 0; j < 4; j++){	//ÿ������4����
			glVertex3fv(vertexs[cubic[i][j]]);
		}
	}
	glEnd();
}

void drawDesk(GLfloat x,GLfloat y,GLfloat z){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//ǰ��������߿�ģʽ����
	glColor3f(1, 1, 1);								//�߿���ɫ��Ϊ��ɫ

	//��������
	drawCubic(x, y, z, desk_body, cubic);	

	//�����ĸ�����
	drawCubic(x - 0.12f, y - 0.12f, z + 0.1f, desk_leg, cubic);
	drawCubic(x + 0.12f, y - 0.12f, z + 0.1f, desk_leg, cubic);
	drawCubic(x + 0.12f, y + 0.12f, z + 0.1f, desk_leg, cubic);
	drawCubic(x - 0.12f, y + 0.12f, z + 0.1f, desk_leg, cubic);

	glFlush();
}

void transform(){
	dy += 0.01f;
	if (dy >= 0.6f)
		dy = 0.0f;
	thelta += 1;
	if (thelta > 360)
		thelta = 0;
	spe -= 0.02f;
	if (spe < 0.4f)
		spe = 1;
}

void display(int value){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear display window

	glLoadIdentity();				//����ϵ��λ
	glTranslatef(0.0f,dy,0.0f);
	drawDesk(-0.6f, 0.0f, -1.4f);	//���ƽ�Ƶ�����
	glLoadIdentity();	
	glTranslatef(0.0f, 0.0f, -1.4f);
	glRotatef(thelta, 0.0f, 1.0f, 0.0f);
	drawDesk(0.0f, 0.0f, 0.0f);		//�м���ת������
	glLoadIdentity();
	glScalef(spe, spe, spe);
	drawDesk(rx / spe, 0.0f, -1.4f / spe);		//�Ҳ����ŵ�����
	glutSwapBuffers();
	transform();
	glutTimerFunc(33, display, 1);		//ʵ����������
}

void init(){

	//����͸��
	glLoadIdentity();		//���õ�ǰ����Ϊ��λ����
	glMatrixMode(GL_PROJECTION);					//����ǰ����ָ��ΪͶӰģʽ
	gluPerspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);	//����͸�����
	glMatrixMode(GL_MODELVIEW);
	glutTimerFunc(33, display, 1);		//��ʱ��,ÿ��33��������һ��
}


int main(int argc,char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Desk");

	glutDisplayFunc(init);

	glutMainLoop();

	return 0;
}