#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh() 
	: cntVertices(0), cntlines(0), cnttriangle(0), cntrect(0), m_fSpeed(0.01f),
	m_VAO_vtx(0), m_VAO_line(0), m_VAO_triangle(0), m_VAO_rect(0)
{
	ZeroMemory(&m_VAO, sizeof(GLuint));
	ZeroMemory(&m_VBO_vtx, sizeof(GLuint));
	ZeroMemory(&m_VBO_line, sizeof(GLuint));
	ZeroMemory(&m_VBO_triangle, sizeof(GLuint));
	ZeroMemory(&m_VBO_rect, sizeof(GLuint));
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

	if (draw_point) {
		Vertices temp{};
		temp.x = x;
		temp.y = y;
		temp.z = z;
		temp.r = uid(dre);
		temp.g = uid(dre);
		temp.b = uid(dre);
		++cntVertices;
		m_vertices_vtx.push_back(temp);
	}
	else if (draw_line) {
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
		
		cnttriangle += cnttriangle + 3;

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
