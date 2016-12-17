#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <gl/glut.h>
#include "glext.h"

#define BITMAP_ID 0x4D42
#define selfHeight 16
#define selfWidth 16

extern GLuint texture[4];		//three kinds of texture
extern GLubyte selfTex[selfHeight][selfWidth][3];	//self texture

// �����ʾ�����飬������������ı�ʾ��
// ����: ͨ��ָ�룬����filename ָ����bitmap�ļ������ݡ�
// ͬʱҲ����bitmap��Ϣͷ.����֧��-bitλͼ��
unsigned char *LoadBitmapFile(char *filename,BITMAPINFOHEADER *bitmapInfoHeader);

// ��������ʱ�ĺ���
void textload(int i, char *filename);

//��������ĺ���
void initTexture();

//���ɺ���������
void generateTex();