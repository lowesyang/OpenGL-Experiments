#include <gl/glut.h>
#include <math.h>
#define PI 3.1415926536

//绘制国旗填充函数
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


//绘制五角星函数
//@params:
//	centerX: 中心点x坐标
//	centerY: 中心点y坐标
//	radius: 五角星半径
//	rotation: 旋转角度 
void drawStar(float centerX, float centerY, float radius, float rotation){
	glColor3f(1, 1, 0);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);	//使用封闭折线绘制方式
	float angle = 0.0+rotation;		//初始角度,加入旋转
	for (; radius >= 0; radius -= 0.001){	//填充五角星
		for (int i = 0; i < 5; i++){		//开始绘制五角星轮廓
			glVertex2f(centerX + radius*sin(angle*PI / 180), centerY + radius*cos(angle*PI / 180));
			angle += 144.0;
		}
	}
	glEnd();
	glFlush();
}

//绘制函数
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