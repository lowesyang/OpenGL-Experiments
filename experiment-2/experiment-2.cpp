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
	for (i = 0; i < 6; i++){		//有6个面需要绘制
		for (j = 0; j < 4; j++){	//每个面有4个点
			glVertex3fv(vertexs[cubic[i][j]]);
		}
	}
	glEnd();
}

void drawDesk(GLfloat x,GLfloat y,GLfloat z){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//前后面均以线框模式绘制
	glColor3f(1, 1, 1);								//线框颜色设为白色

	//绘制桌面
	drawCubic(x, y, z, desk_body, cubic);	

	//绘制四个桌腿
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

	glLoadIdentity();				//坐标系复位
	glTranslatef(0.0f,dy,0.0f);
	drawDesk(-0.6f, 0.0f, -1.4f);	//左侧平移的桌子
	glLoadIdentity();	
	glTranslatef(0.0f, 0.0f, -1.4f);
	glRotatef(thelta, 0.0f, 1.0f, 0.0f);
	drawDesk(0.0f, 0.0f, 0.0f);		//中间旋转的桌子
	glLoadIdentity();
	glScalef(spe, spe, spe);
	drawDesk(rx / spe, 0.0f, -1.4f / spe);		//右侧缩放的桌子
	glutSwapBuffers();
	transform();
	glutTimerFunc(33, display, 1);		//实现连续动画
}

void init(){

	//开启透视
	glLoadIdentity();		//重置当前矩阵为单位矩阵
	glMatrixMode(GL_PROJECTION);					//将当前矩阵指定为投影模式
	gluPerspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);	//设置透视相机
	glMatrixMode(GL_MODELVIEW);
	glutTimerFunc(33, display, 1);		//定时器,每个33毫秒运行一次
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