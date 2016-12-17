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

// 纹理标示符数组，保存两个纹理的标示符
// 描述: 通过指针，返回filename 指定的bitmap文件中数据。
// 同时也返回bitmap信息头.（不支持-bit位图）
unsigned char *LoadBitmapFile(char *filename,BITMAPINFOHEADER *bitmapInfoHeader);

// 加载纹理时的函数
void textload(int i, char *filename);

//定义纹理的函数
void initTexture();

//生成红黑相间纹理
void generateTex();