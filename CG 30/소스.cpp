#define _CRT_SECURE_NO_WARNINGS //--- ���α׷� �� �տ� ������ ��
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
// git branch dev
#include <vector>
// �ʿ��� ��� include ���� �߰��ϼž� �մϴ�~

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm/glm.hpp>

#include <gl/glm/glm/ext.hpp>
#include <gl/glm/glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//--- ���� �Լ�
//--- �Լ� ���� �߰��ϱ�

glm::vec3 cameraPos = glm::vec3(-0.25, +1.0, -1); //--- ī�޶� ��ġ

float light_x = 7;
float light_y = 10;
float light_z = 10;
float zcamera;

struct Vertices {
	glm::vec3 pos;
	glm::vec3 nor;
	glm::vec2 tex;
};
std::vector<Vertices> m_vertices;


GLuint vao, vbo[2], line_vao, line_vbo[2], ebo, fvao, febo, fvbo[2], obit_vao, obit_vbo[2], obit_ebo, con_vao, con_vbo[2];
GLuint TriPosVbo[15], TriColorVbo[15];

GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint shaderProgramID;//--- ���̴� ���α׷�

void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void InitBuffer();
void UpdateBuffer();
char* filetobuf(const char*);
void InitTexture();
void ReadObj(const char* fileName);

glm::vec3 Tsphere;

unsigned int texture;


void timerfunc(int value) {

	glutPostRedisplay();
	glutTimerFunc(10000, timerfunc, 1);

}

void Motion(int x, int y) {

	float dot_x = ((float)x - 400) / 400.0;
	float dot_y = (300.0 - (float)y) / 300.0;

	glutPostRedisplay();

}


void Mouse(int button, int state, int x, int y) {
	float dot_x = ((float)x - 400) / 400.0;
	float dot_y = (300.0 - (float)y) / 300.0;

	glutPostRedisplay();


}
void specialKeyCallback(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
	{
		//cameraPos.y += 0.1;
		cameraPos.x += 0.1;
		//cameraPos.z += 0.1;

	}
		break;
	case GLUT_KEY_DOWN:
		cameraPos.y -= 0.1;
		cameraPos.x -= 0.1;

		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	}
	glutPostRedisplay();

}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key)
	{
	case 'c': case 'C':
		break;
	case 'p': case 'P':
		break;
	case 'x': case 'X':
		break;
	case 'y': case 'Y':
		break;
	case 's': case 'S':
		break;
	}
	glutPostRedisplay();

}

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Sphere Example");
	glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
	}

	ReadObj("cube2.obj");

	make_shaderProgram();
	InitBuffer();
	InitTexture();
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeyCallback);
	glutDisplayFunc(drawScene);

	glEnable(GL_DEPTH_TEST);  // ���� �׽�Ʈ Ȱ��ȭ
	glutMainLoop();


}

GLvoid drawScene()
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����

	glUseProgram(shaderProgramID);
	glBindVertexArray(vao);


	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	//--- ����� VAO �ҷ�����
	glm::mat4 Tx = glm::mat4(1.0f); //--- �̵� ��� ����
	glm::mat4 Rz = glm::mat4(1.0f); //--- ȸ�� ��� ����
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Sc = glm::mat4(1.0f);
	glm::mat4 box = glm::mat4(1.0f);
	glm::mat4 box_scale = glm::mat4(1.0f);

	GLuint modelLoc = glGetUniformLocation(shaderProgramID, "model");
	GLuint viewLoc = glGetUniformLocation(shaderProgramID, "view");
	GLuint projLoc = glGetUniformLocation(shaderProgramID, "projection");

	GLuint texLoc = glGetUniformLocation(shaderProgramID, "outTexture");
	glUniform1i(texLoc, 0);
	//glActiveTexture(texLoc);
	

	glm::vec3 newColor(0.0f, 0.0f, 0.0f);

	glm::mat4 mTransform = glm::mat4(1.0f);
	Tx = glm::translate(glm::mat4(1.0f), Tsphere);
	Rz = glm::rotate(mTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	Sc = glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 0.1));

	//mTransform = Sc*Tx;

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mTransform));

	glm::mat4 vTransform = glm::mat4(1.0f);
	vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	vTransform = vTransform; //ī�޶���ġ ������ �տ��θ� ī�޶� ����, �ڿ� �θ� ī�޶� ����
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &vTransform[0][0]);

	glm::mat4 pTransform = glm::mat4(1.0f);
	pTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f); //��������


	//{   //���� ��ġ
	//	glm::vec4 lightPosInModelSpace = glm::vec4(light_x, light_y, light_z, 1.0f);
	//	lightPosInModelSpace = lightPosInModelSpace;
	//	// ���̴��� ��ȯ�� ���� ��ġ ����
	//	GLuint lightPosLoc = glGetUniformLocation(shaderProgramID, "lightPos");
	//	glUniform3f(lightPosLoc, lightPosInModelSpace.x, lightPosInModelSpace.y, lightPosInModelSpace.z);

	//}

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &pTransform[0][0]);
	newColor.r = 1.0; newColor.g = 1.0; newColor.b = 1.0;

	UpdateBuffer();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

	glutSwapBuffers();

}

//--- �ٽñ׸��� �ݹ� �Լ�
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void InitBuffer()
{

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo[0]);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertices), &m_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)0); //--- ��ġ �Ӽ�
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)offsetof(Vertices, nor)); //--- �븻 �Ӽ�
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)offsetof(Vertices, tex)); //--- �ؽ�ó ��ǥ �Ӽ�
	glEnableVertexAttribArray(2);


	glUseProgram(shaderProgramID);

	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor"); //--- lightColor �� ����: (1.0, 1.0, 1.0) ���
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor"); //--- object Color�� ����: (1.0, 0.5, 0.3)�� ��
	glUniform3f(objColorLocation, 1.0, 0.5, 0.3);
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos"); //--- viewPos �� ����: ī�޶� ��ġ
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

}

void UpdateBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);		// Position Color
	if (!m_vertices.empty())
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertices), &m_vertices.front(), GL_STATIC_DRAW);
}

void InitTexture()
{
	int widthImage, heightImage, numberOfChannel;

	glGenTextures(1, &texture); //--- �ؽ�ó ����
	glBindTexture(GL_TEXTURE_2D, texture); //--- �ؽ�ó ���ε�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char* data = LoadDIBitmap("texture.bmp", &bmp); //--- �ؽ�ó�� ����� ��Ʈ�� �̹��� �ε��ϱ�
	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("A.png", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //---�ؽ�ó �̹��� ����
	stbi_image_free(data);
}

void make_shaderProgram()
{
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cout << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cout << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}

void ReadObj(const char* fileName)
{
	FILE* fp = fopen(fileName, "r");

	if (fp == NULL) {
		std::cerr << "Invalid Object File!!\n";
		exit(100);
	}

	char buff[100];
	int faceNum = 0;
	std::vector<glm::vec3> vtx;
	std::vector<glm::vec3> nor;
	std::vector<glm::vec2> tex;

	while (!feof(fp)) {
		if (fscanf(fp, "%s", buff) == 3) printf("hello it's 3");

		// vertex or element buffer
		if (buff[0] == 'v' && buff[1] == '\0') {
			glm::vec3 pos;
			if (fscanf(fp, "%f %f %f", &pos.x, &pos.y, &pos.z) != 3) exit(1);
			vtx.push_back(pos);
		}
		// vertex normal
		else if (buff[0] == 'v' && buff[1] == 'n' && buff[2] == '\0') {
			glm::vec3 pos;
			if (fscanf(fp, "%f %f %f", &pos.x, &pos.y, &pos.z) != 3) exit(1);
			nor.push_back(pos);
		}
		// vertex texture coordinate
		else if (buff[0] == 'v' && buff[1] == 't' && buff[2] == '\0') {
			glm::vec2 pos;
			float temp;
			if (fscanf(fp, "%f %f %f", &pos.x, &pos.y, &temp) != 3) exit(1);
			tex.push_back(pos);
		}
		else if (buff[0] == 'f' && buff[1] == '\0') {
			Vertices temp;
			int v, t, n;
			if (fscanf(fp, "%d/%d/%d", &v, &t, &n) != 3) exit(1);
			temp.pos = vtx[v - 1];
			temp.nor = nor[n - 1];
			temp.tex = tex[t - 1];
			m_vertices.push_back(temp);

			if (fscanf(fp, "%d/%d/%d", &v, &t, &n) != 3) exit(1);
			temp.pos = vtx[v - 1];
			temp.nor = nor[n - 1];
			temp.tex = tex[t - 1];
			m_vertices.push_back(temp);

			if (fscanf(fp, "%d/%d/%d", &v, &t, &n) != 3) exit(1);
			temp.pos = vtx[v - 1];
			temp.nor = nor[n - 1];
			temp.tex = tex[t - 1];
			m_vertices.push_back(temp);
		}

		memset(buff, NULL, sizeof(buff));
	}


	vtx.clear();
	nor.clear();
	tex.clear();

	fclose(fp);
}


//--- out_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- FragColor: ����� ������ ������ ������ ���۷� ���� ��.
