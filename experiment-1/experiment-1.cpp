#include <gl/glut.h>
#include <math.h>
#define PI 3.1415926536

//���ƹ�����亯��
void drawFlag(){
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();
	glFlush();
}


//��������Ǻ���
//@params:
//	centerX: ���ĵ�x����
//	centerY: ���ĵ�y����
//	radius: ����ǰ뾶
//	rotation: ��ת�Ƕ� 
void drawStar(float centerX, float centerY, float radius, float rotation){
	glColor3f(1, 1, 0);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);	//ʹ�÷�����߻��Ʒ�ʽ
	float angle = 0.0+rotation;		//��ʼ�Ƕ�,������ת
	for (; radius >= 0; radius -= 0.001){	//��������
		for (int i = 0; i < 5; i++){		//��ʼ�������������
			glVertex2f(centerX + radius*sin(angle*PI / 180), centerY + radius*cos(angle*PI / 180));
			angle += 144.0;
		}
	}
	glEnd();
	glFlush();
}

//���ƺ���
void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawFlag();
	drawStar(-0.35, 0.32, 0.1, 0.0);
	drawStar(-0.14, 0.45, 0.03, 30.0);
	drawStar(-0.1, 0.32, 0.03, 45.0);
	drawStar(-0.125, 0.18, 0.03, 0.0);
	drawStar(-0.125, 0.18, 0.03, 0.0);
	drawStar(-0.2, 0.06, 0.03, 25.0);
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800, 600);
	glutCreateWindow("The Flag of China");

	glutDisplayFunc(display);		

	glutMainLoop();

	return 0;
}