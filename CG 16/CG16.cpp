#include "stdafx.h"
#include "Mesh.h"
#include "shaders.h"

//void make_vertexShaders();
//void make_fragmentShaders();

//GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);

//--- �ʿ��� ���� ����
GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷� �̸�
GLchar* vertexSource;
GLchar* fragmentSource;

GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��ü


int draw_mode(0);
int draw_vertex(0);
int numVertices(0);

Mesh mesh;
shaders* m_pShader;


//--- ���� �Լ�
int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINSIZEX, WINSIZEY);
	glutCreateWindow("Example1");

	glEnable(GL_DEPTH_TEST);

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();

	//--- ���̴� �о�ͼ� ���̴� ���α׷� �����

	//make_shaderProgram();
	//m_pShader = new shaders("vertex.glsl", "fragment.glsl");
	
	mesh.initbuffer();
	//--- ���̴� ���α׷� �����

	glutDisplayFunc(drawScene); //--- ��� �ݹ� �Լ�
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

//void make_vertexShaders()
//{
//	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
//	//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
//
//	vertexSource = filetobuf("vertex.glsl");
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);	// ���̴� ��ü �����
//	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);	 //���̴� ��ü�� ���̴� �ڵ� ���̱�
//	glCompileShader(vertexShader);	//���̴� ��ü �������ϱ�
//
//	GLint result;
//	GLchar errorLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
//	if (!result)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
//		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
//		return;
//	}
//}
//
//void make_fragmentShaders()
//{
//	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
//	fragmentSource = filetobuf("fragment.glsl"); // �����׼��̴� �о����
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
//	glCompileShader(fragmentShader);
//
//	GLint result;
//	GLchar errorLog[512];
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
//	if (!result)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
//		std::cerr << "ERROR: frag_shader ������ ����\n" << errorLog << std::endl;
//		return;
//	}
//}
//
//GLuint make_shaderProgram()
//{
//	make_vertexShaders(); //--- ���ؽ� ���̴� �����
//	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
//
//	shaderProgramID = glCreateProgram(); //--- ���̴� ���α׷� �����
//
//	glAttachShader(shaderProgramID, vertexShader); //--- ���̴� ���α׷��� ���ؽ� ���̴� ���̱�
//	glAttachShader(shaderProgramID, fragmentShader); //--- ���̴� ���α׷��� �����׸�Ʈ ���̴� ���̱�
//
//	glLinkProgram(shaderProgramID); //--- ���̴� ���α׷� ��ũ�ϱ�
//
//	glDeleteShader(vertexShader); //--- ���̴� ��ü�� ���̴� ���α׷��� ��ũ��������, ���̴� ��ü ��ü�� ���� ����
//	glDeleteShader(fragmentShader);
//
//	GLint result;
//	GLchar errorLog[512];
//	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result); // ---���̴��� �� ����Ǿ����� üũ�ϱ�
//	if (!result) {
//		glGetProgramInfoLog(shaderProgramID, 512, NULL, errorLog);
//		std::cerr << "ERROR: shader program ���� ����\n" << errorLog << std::endl;
//		return false;
//	}
//
//	glUseProgram(shaderProgramID); //--- ������� ���̴� ���α׷� ����ϱ�
//	//--- ���� ���� ���̴����α׷� ���� �� �ְ�, �� �� �Ѱ��� ���α׷��� ����Ϸ���
//	//--- glUseProgram �Լ��� ȣ���Ͽ� ��� �� Ư�� ���α׷��� �����Ѵ�.
//	//--- ����ϱ� ������ ȣ���� �� �ִ�.
//}

GLvoid drawScene()
{
	GLfloat rColor, gColor, bColor;

	rColor = gColor = bColor = 0.75; //--- ������ �Ķ������� ����
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glUseProgram(shaderProgramID);

	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
	//model = glm::scale(model, glm::vec3(0.5f, 2.0f, 1.0f));

	//m_pShader->shaderuse();

	mesh.glu_draw();

	mesh.updatebuffer();

	mesh.draw();


	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':	// �� �׸���
		if (!mesh.draw_point) {
			mesh.draw_point = true;
			mesh.draw_line = false;
			mesh.draw_triangle = false;
			mesh.draw_rect = false;
		}
		
		break;
	case 'l':	// �� �׸���
		if (!mesh.draw_line) {
			mesh.draw_line = true;
			mesh.draw_point = false;
			mesh.draw_triangle = false;
			mesh.draw_rect = false;
		}

		break;
	case 't':	// �ﰢ�� �׸���
		if (!mesh.draw_triangle) {
			mesh.draw_triangle = true;
			mesh.draw_point = false;
			mesh.draw_line = false;
			mesh.draw_rect = false;
		}
		break;
	case 'r':	// �簢�� �׸���
		if (!mesh.draw_rect) {
			mesh.draw_rect = true;
			mesh.draw_point = false;
			mesh.draw_line = false;
			mesh.draw_triangle = false;
		}
		break;
	case 'w':
		mesh.draw_up = true;
		mesh.move();
		break;
	case 'a':
		mesh.draw_left = true;
		mesh.move();
		break;
	case 's':
		mesh.draw_down = true;
		mesh.move();
		break;
	case 'd':
		mesh.draw_right = true;
		mesh.move();
		break;
	case 'c':	// ��� ������ ����
		mesh.release();
		break;
	case 27:
		exit(0);
	}
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}


void Mouse(int button, int state, int x, int y)
{
	float conversionX = (2.0f * x) / WINSIZEX - 1.0f;
	float conversionY = 1.0f - (2.0f * y) / WINSIZEY;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//std::cout << conversionX << '\t' << conversionY << '\n';
		if (mesh.draw_point || mesh.draw_line || mesh.draw_triangle || mesh.draw_rect) {
			mesh.meshdata(conversionX, conversionY, 0.f);
			//glutPostRedisplay();
		}
	}
	else;



}