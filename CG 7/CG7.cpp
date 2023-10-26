#include "stdafx.h"
#include "Mesh.h"

void make_vertexShaders();
void make_fragmentShaders();

GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);

//--- 필요한 변수 선언
GLint width, height;
GLuint shaderProgramID; //--- 세이더 프로그램 이름
GLchar* vertexSource;
GLchar* fragmentSource;

GLuint vertexShader; //--- 버텍스 세이더 객체
GLuint fragmentShader; //--- 프래그먼트 세이더 객체


int draw_mode(0);
int draw_vertex(0);
int numVertices(0);

Mesh mesh;

//--- 메인 함수
int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINSIZEX, WINSIZEY);
	glutCreateWindow("Example1");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	//--- 세이더 읽어와서 세이더 프로그램 만들기

	make_shaderProgram();
	
	mesh.initbuffer();
	//--- 세이더 프로그램 만들기

	glutDisplayFunc(drawScene); //--- 출력 콜백 함수
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

void make_vertexShaders()
{
	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수

	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);	// 셰이더 객체 만들기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);	 //셰이더 객체에 셰이더 코드 붙이기
	glCompileShader(vertexShader);	//셰이더 객체 컴파일하기

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	fragmentSource = filetobuf("fragment.glsl"); // 프래그세이더 읽어오기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

GLuint make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기

	shaderProgramID = glCreateProgram(); //--- 세이더 프로그램 만들기

	glAttachShader(shaderProgramID, vertexShader); //--- 세이더 프로그램에 버텍스 세이더 붙이기
	glAttachShader(shaderProgramID, fragmentShader); //--- 세이더 프로그램에 프래그먼트 세이더 붙이기

	glLinkProgram(shaderProgramID); //--- 세이더 프로그램 링크하기

	glDeleteShader(vertexShader); //--- 세이더 객체를 세이더 프로그램에 링크했음으로, 세이더 객체 자체는 삭제 가능
	glDeleteShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result); // ---세이더가 잘 연결되었는지 체크하기
	if (!result) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		return false;
	}

	glUseProgram(shaderProgramID); //--- 만들어진 세이더 프로그램 사용하기
	//--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
	//--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
	//--- 사용하기 직전에 호출할 수 있다.
}

GLvoid drawScene()
{
	GLfloat rColor, gColor, bColor;

	rColor = gColor = bColor = 0.75; //--- 배경색을 파랑색으로 설정
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramID);

	mesh.updatebuffer();

	mesh.draw();

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':	// 점 그리기
		if (!mesh.draw_point) {
			mesh.draw_point = true;
			mesh.draw_line = false;
			mesh.draw_triangle = false;
			mesh.draw_rect = false;
		}
		
		break;
	case 'l':	// 선 그리기
		if (!mesh.draw_line) {
			mesh.draw_line = true;
			mesh.draw_point = false;
			mesh.draw_triangle = false;
			mesh.draw_rect = false;
		}

		break;
	case 't':	// 삼각형 그리기
		if (!mesh.draw_triangle) {
			mesh.draw_triangle = true;
			mesh.draw_point = false;
			mesh.draw_line = false;
			mesh.draw_rect = false;
		}
		break;
	case 'r':	// 사각형 그리기
		if (!mesh.draw_rect) {
			mesh.draw_rect = true;
			mesh.draw_point = false;
			mesh.draw_line = false;
			mesh.draw_triangle = false;
		}
		break;
	case 'w':
		break;
	case 'a':
		break;
	case 's':
		break;
	case 'd':
		break;
	case 'c':	// 모든 도형을 삭제
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