#define _CRT_SECURE_NO_WARNINGS //--- 프로그램 맨 앞에 선언할 것

#pragma once

//--- 필요한 헤더파일 include
#include <iostream>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm/glm.hpp>
#include <gl/glm/glm/ext.hpp>
#include <gl/glm/glm/gtc/matrix_transform.hpp>


#include <vector>
#include <random>

#include "FileRead.h"


//--- 필요한 정의
#define WINSIZEX 800
#define WINSIZEY 600
#define WIDTH 0.05f
#define HEIGHT WIDTH*WINSIZEX/WINSIZEY


struct Vertices {
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat r;
	GLfloat g;
	GLfloat b;
};