#include "stdafx.h"
#include "Mesh.h"
#include "shaders.h"

Mesh::Mesh() 
	: cntVertices(0), cntlines(0), cnttriangle(0), cntrect(0), m_fSpeed(0.01f),
	m_VAO_vtx(0), m_VAO_line(0), m_VAO_triangle(0), m_VAO_rect(0)
{
	ZeroMemory(&m_VAO, sizeof(GLuint));
	ZeroMemory(&m_VBO_vtx, sizeof(GLuint));
	ZeroMemory(&m_VBO_line, sizeof(GLuint));
	ZeroMemory(&m_VBO_triangle, sizeof(GLuint));
	ZeroMemory(&m_VBO_rect, sizeof(GLuint));
	ZeroMemory(&qobj, sizeof(GLUquadricObj*));
}

Mesh::~Mesh()
{
	//for (int i = 0; i < m_vertices->size(); ++i) {
	//	m_vertices[i].clear();
	//}
	
}

void Mesh::initbuffer()
{
	glGenVertexArrays(1, &m_VAO_vtx);		//--- VAO 를 지정하고 할당하기
	glBindVertexArray(m_VAO_vtx);			//--- VAO를 바인드하기
	glGenBuffers(1, &m_VBO_vtx);			//--- 2개의 VBO를 지정하고 할당하기

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_vtx);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_vtx.size() * sizeof(Vertices), &m_vertices_vtx, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &m_VAO_line);		//--- VAO 를 지정하고 할당하기
	glBindVertexArray(m_VAO_line);			//--- VAO를 바인드하기
	glGenBuffers(1, &m_VBO_line);			//--- 2개의 VBO를 지정하고 할당하기

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_line);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_line.size() * sizeof(Vertices), &m_vertices_line, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glGenVertexArrays(1, &m_VAO_triangle);	//--- VAO 를 지정하고 할당하기
	glBindVertexArray(m_VAO_triangle);		//--- VAO를 바인드하기
	glGenBuffers(1, &m_VBO_triangle);		//--- 2개의 VBO를 지정하고 할당하기

	glBindBuffer(GL_ARRAY_BUFFER, m_VAO_triangle);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_triangle.size() * sizeof(Vertices), &m_vertices_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glGenVertexArrays(1, &m_VAO_rect);		//--- VAO 를 지정하고 할당하기
	glBindVertexArray(m_VAO_rect);			//--- VAO를 바인드하기
	glGenBuffers(1, &m_VBO_rect);			//--- 2개의 VBO를 지정하고 할당하기

	glBindBuffer(GL_ARRAY_BUFFER, m_VAO_rect);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_rect.size() * sizeof(Vertices), &m_vertices_rect, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void Mesh::updatebuffer()
{
	{	// vertex
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_vtx);		// Position Color
		if (!m_vertices_vtx.empty()) 
			glBufferData(GL_ARRAY_BUFFER, m_vertices_vtx.size() * sizeof(Vertices), &m_vertices_vtx.front(), GL_STATIC_DRAW);
	}
	{	// line
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_line);		// Position Color
		if(!m_vertices_line.empty())
			glBufferData(GL_ARRAY_BUFFER, m_vertices_line.size() * sizeof(Vertices), &m_vertices_line.front(), GL_STATIC_DRAW);
	}
	{	// triangle
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_triangle);	// Position Color
		if (!m_vertices_triangle.empty())
			glBufferData(GL_ARRAY_BUFFER, m_vertices_triangle.size() * sizeof(Vertices), &m_vertices_triangle.front(), GL_STATIC_DRAW);
	}
	{	// rect
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_rect);		// Position Color
		if (!m_vertices_rect.empty())
			glBufferData(GL_ARRAY_BUFFER, m_vertices_rect.size() * sizeof(Vertices), &m_vertices_rect.front(), GL_STATIC_DRAW);
	}
}

void Mesh::glu_draw()
{
	// 내 기준 gldraw랑 비슷 만들어놓으면 알아서 적용
	//qobj[0] = gluNewQuadric();
	//gluQuadricDrawStyle(qobj[0], GLU_LINE);
	//gluQuadricNormals(qobj[0], GLU_SMOOTH);
	//gluQuadricOrientation(qobj[0], GLU_OUTSIDE);
	//gluCylinder(qobj[0], 0.5, 0.0, 0.5, 20, 8);

	qobj[1] = gluNewQuadric();
	gluQuadricDrawStyle(qobj[1], GLU_LINE);
	gluQuadricNormals(qobj[1], GLU_SMOOTH);
	gluQuadricOrientation(qobj[1], GLU_OUTSIDE);
	gluCylinder(qobj[1], 0.5, 0.5, 0.5, 4, 1);

	m_pshader = new shaders("vertex.glsl", "fragment.glsl");	
	// // 이걸 사용하려면 shader에서 파일 읽어오는 거 조금 조정
	// 이걸 하고 있는 이유 obj 파일을 읽고 그 버텍스를 그리고 움직이고 싶은데 그 유니폼 값을 가져오려면 쉐이더id가 필요 그래서 메쉬클래스에선 현재 불가능 그래서 쉐이더 만드는 걸 쉐이더클래스 따로 만들어서 여기서도 받아오게 하려고 만드는중 결론은 여기서 shaders->shaderuse()가 되게끔 하고 싶음
	m_pshader->shaderuse();
	


	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 TR = glm::mat4(1.0f);

	//Tx = glm::translate(Tx, glm::vec3(0.0, 0.0, 0.0));
	Rz = glm::rotate(Rz, glm::radians(50.0f), glm::vec3(1.0, 1.0, 1.0));

	TR = Rz;
	m_pshader->setUniform_matrix4fv("modelTransform", TR);
}

void Mesh::draw()
{
	glPointSize(10);
	glBindVertexArray(m_VAO_vtx);
	glDrawArrays(GL_POINTS, 0, cntVertices);
	//if(!m_vertices_vtx.empty())
	//	std::cout << m_vertices_vtx.back().x << m_vertices_vtx[0].y << m_vertices_vtx[0].z << '\n';

	glBindVertexArray(m_VAO_line);
	glDrawArrays(GL_LINES, 0, cntlines);

	glBindVertexArray(m_VAO_triangle);
	glDrawArrays(GL_TRIANGLES, 0, cnttriangle);

	glBindVertexArray(m_VAO_rect);
	glDrawArrays(GL_TRIANGLES, 0, cntrect);

}

void Mesh::meshdata(float x, float y, float z)
{
	std::default_random_engine dre;
	std::uniform_real_distribution<float> uid{ 0, 1 };

	Vertices tempx1{}, tempx2{};
	Vertices tempy1{}, tempy2{};
	Vertices tempz1{}, tempz2{};

	tempx1.x = -1,	tempx2.x = 1;
	tempx1.y = 0,	tempx2.y = 0;
	tempx1.z = 0,	tempx2.z = 0;
	tempx1.r = 0,	tempx2.r = 0;
	tempx1.g = 0,	tempx2.g = 0;
	tempx1.b = 0,	tempx2.b = 0;
	m_vertices_line.push_back(tempx1);
	m_vertices_line.push_back(tempx2);

	tempy1.x = 0,	tempy2.x = 0;
	tempy1.y = -1,	tempy2.y = 1;
	tempy1.z = 0,	tempy2.z = 0;
	tempy1.r = 0,	tempy2.r = 0;
	tempy1.g = 0,	tempy2.g = 0;
	tempy1.b = 0,	tempy2.b = 0;
	m_vertices_line.push_back(tempy1);
	m_vertices_line.push_back(tempy2);

	tempz1.x = 0,	tempz2.x = 0;
	tempz1.y = 0,	tempz2.y = 0;
	tempz1.z = -1,	tempz2.z = 1;
	tempz1.r = 0,	tempz2.r = 0;
	tempz1.g = 0,	tempz2.g = 0;
	tempz1.b = 0,	tempz2.b = 0;
	m_vertices_line.push_back(tempz1);
	m_vertices_line.push_back(tempz2);

	if (draw_line) {
		Vertices tline1{};
		Vertices tline2{};

		tline1.x = x;
		tline1.y = y;
		tline1.z = z;
		tline1.r = uid(dre);
		tline1.g = uid(dre);
		tline1.b = uid(dre);

		if (!(tline1.x == x && tline1.y == y)) {
			tline2.x = x;
			tline2.y = y;
			tline2.z = z;
			tline2.r = uid(dre);
			tline2.g = uid(dre);
			tline2.b = uid(dre);
		}
			
		++++cntlines;
		m_vertices_line.push_back(tline1);
		m_vertices_line.push_back(tline2);
	}
	else if (draw_triangle) {
		Vertices ttri1{};
		Vertices ttri2{};
		Vertices ttri3{};

		ttri1.x = x;			ttri1.r = uid(dre);
		ttri1.y = y + 0.2f;		ttri1.g = uid(dre);
		ttri1.z = z;			ttri1.b = uid(dre);

		ttri2.x = x - 0.2f;		ttri2.r = uid(dre);
		ttri2.y = y - 0.15f;	ttri2.g = uid(dre);
		ttri2.z = z;			ttri2.b = uid(dre);

		ttri3.x = x + 0.2f;		ttri3.r = uid(dre);
		ttri3.y = y - 0.15f;	ttri3.g = uid(dre);
		ttri3.z = z;			ttri3.b = uid(dre);
		
		cnttriangle = cnttriangle + 3;

		m_vertices_triangle.push_back(ttri1);
		m_vertices_triangle.push_back(ttri2);
		m_vertices_triangle.push_back(ttri3);

	}
	else if (draw_rect) {
		Vertices trect1{};
		Vertices trect2{};
		Vertices trect3{};
		Vertices trect4{};
		Vertices trect5{};
		Vertices trect6{};

		{								//vtx
			trect1.x = x - 0.2f;		trect2.x = x + 0.2f;
			trect1.y = y + 0.2f;		trect2.y = y + 0.2f;
			trect1.z = z;				trect2.z = z;

			trect3.x = x - 0.2f;		trect4.x = x - 0.2f;
			trect3.y = y - 0.2f;		trect4.y = y - 0.2f;
			trect3.z = z;				trect4.z = z;

			trect5.x = x + 0.2f;		trect6.x = x + 0.2f;
			trect5.y = y + 0.2f;		trect6.y = y - 0.2f;
			trect5.z = z;				trect6.z = z;
		}
		{
			trect1.r = uid(dre);		trect2.r = uid(dre);
			trect1.g = uid(dre);		trect2.g = uid(dre);
			trect1.b = uid(dre);		trect2.b = uid(dre);

			trect3.r = uid(dre);		trect4.r = uid(dre);
			trect3.g = uid(dre);		trect4.g = uid(dre);
			trect3.b = uid(dre);		trect4.b = uid(dre);

			trect5.r = uid(dre);		trect6.r = uid(dre);
			trect5.g = uid(dre);		trect6.g = uid(dre);
			trect5.b = uid(dre);		trect6.b = uid(dre);
		}

		cntrect = cntrect + 6;

		m_vertices_rect.push_back(trect1);
		m_vertices_rect.push_back(trect2);
		m_vertices_rect.push_back(trect3);
		m_vertices_rect.push_back(trect4);
		m_vertices_rect.push_back(trect5);
		m_vertices_rect.push_back(trect6);
	}
}

void Mesh::move()
{
	if (draw_right) 
		for (auto iter = m_vertices_vtx.begin(); iter != m_vertices_vtx.end(); ++iter)
			iter->x += m_fSpeed;
	if (draw_left)
		for (auto iter = m_vertices_vtx.begin(); iter != m_vertices_vtx.end(); ++iter)
			iter->x -= m_fSpeed;
	if (draw_up)
		for (auto iter = m_vertices_vtx.begin(); iter != m_vertices_vtx.end(); ++iter)
			iter->y += m_fSpeed;
	if (draw_down)
		for (auto iter = m_vertices_vtx.begin(); iter != m_vertices_vtx.end(); ++iter)
			iter->y -= m_fSpeed;

	if (draw_right)
		for (auto iter = m_vertices_line.begin(); iter != m_vertices_line.end(); ++iter)
			iter->x += m_fSpeed;
	if (draw_left)
		for (auto iter = m_vertices_line.begin(); iter != m_vertices_line.end(); ++iter)
			iter->x -= m_fSpeed;
	if (draw_up)
		for (auto iter = m_vertices_line.begin(); iter != m_vertices_line.end(); ++iter)
			iter->y += m_fSpeed;
	if (draw_down)
		for (auto iter = m_vertices_line.begin(); iter != m_vertices_line.end(); ++iter)
			iter->y -= m_fSpeed;

	if (draw_right)
		for (auto iter = m_vertices_triangle.begin(); iter != m_vertices_triangle.end(); ++iter)
			iter->x += m_fSpeed;
	if (draw_left)
		for (auto iter = m_vertices_triangle.begin(); iter != m_vertices_triangle.end(); ++iter)
			iter->x -= m_fSpeed;
	if (draw_up)
		for (auto iter = m_vertices_triangle.begin(); iter != m_vertices_triangle.end(); ++iter)
			iter->y += m_fSpeed;
	if (draw_down)
		for (auto iter = m_vertices_triangle.begin(); iter != m_vertices_triangle.end(); ++iter)
			iter->y -= m_fSpeed;

	if (draw_right)
		for (auto iter = m_vertices_rect.begin(); iter != m_vertices_rect.end(); ++iter)
			iter->x += m_fSpeed;
	if (draw_left)
		for (auto iter = m_vertices_rect.begin(); iter != m_vertices_rect.end(); ++iter)
			iter->x -= m_fSpeed;
	if (draw_up)
		for (auto iter = m_vertices_rect.begin(); iter != m_vertices_rect.end(); ++iter)
			iter->y += m_fSpeed;
	if (draw_down)
		for (auto iter = m_vertices_rect.begin(); iter != m_vertices_rect.end(); ++iter)
			iter->y -= m_fSpeed;

	draw_right = false;
	draw_left = false;
	draw_up = false;
	draw_down = false;

	glutPostRedisplay();
}

void Mesh::release()
{
	m_vertices_vtx.clear();
	m_vertices_line.clear();
	m_vertices_triangle.clear();
	m_vertices_rect.clear();


	cntVertices = 0;
	cntlines = 0;
	cnttriangle = 0;
	cntrect = 0;
	//std::vector<Vertices>().swap(m_vertices_vtx);

	glutPostRedisplay();

}

void Mesh::ReadObj(FILE* path)
{
	char count[128];
	int vertexnum = 0;
	int facenum = 0;
	int uvnum = 0;

	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	while (!feof(path)) {
		fscanf(path, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexnum++;
		else if (count[0] == 'f' && count[1] == '\0')
			facenum++;	// face가 면
		else if (count[0] == 'v' && count[1] == 'n' && count[3] == '\0')
			uvnum++;	// 일단은 샘플파일에 vt가 없어서 vn으로
		memset(count, '\0', sizeof(count));
	}
	rewind(path);

	int vertIndex = 0;
	int faceIndex = 0;
	int uvIndex = 0;

	//--- 2. 메모리 할당
	glm::vec3* vertex = new glm::vec3[vertexnum];
	glm::vec3* face = new glm::vec3[facenum];
	glm::vec3* uvdata = new glm::vec3[facenum];
	glm::vec2* uv = new glm::vec2[uvnum];

	char bind[128];

	//--- 3. 할당된 메모리에 각 버텍스, 페이스, uv 정보 입력
	while (!feof(path)) {
		fscanf(path, "%s", bind);

		if (bind[0] == 'v' && bind[1] == '\0') {
			fscanf(path, "%f %f %f\n",
				&vertex[vertIndex].x,
				&vertex[vertIndex].y,
				&vertex[vertIndex].z);
			vertIndex++;
		}
		else if (bind[0] == 'f' && bind[1] == '\0') {
			unsigned int temp_face[3], temp_uv[3], temp_normal[3];

			fscanf(path, "%d//%d %d//%d %d//%d\n",
				&temp_face[0], &temp_uv[0], &temp_normal[0],
				&temp_face[1], &temp_uv[1], &temp_normal[1],
				&temp_face[2], &temp_uv[2], &temp_normal[2]);

			face[faceIndex].x = temp_face[0];
			face[faceIndex].y = temp_face[1];
			face[faceIndex].z = temp_face[2];
			//uvdata[faceIndex].x = temp_uv[0];
			//uvdata[faceIndex].y = temp_uv[1];
			//uvdata[faceIndex].z = temp_uv[2];
			faceIndex++;
		}
		else if (bind[0] == 'v' && bind[1] == 'n' && bind[2] == '\0') {
			fscanf(path, "%f %f\n", &uv[uvIndex].x, &uv[uvIndex].y);
			uvIndex++;
		}
	}
	//--- 필요한 경우 읽어온 값을 전역 변수 등에 저장
}
