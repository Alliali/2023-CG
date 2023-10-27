#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh() 
	: cntVertices(0), cntlines(0), cnttriangle(0), cntrect(0),
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

	//glGenVertexArrays(1, &m_VAO_triangle);	//--- VAO 를 지정하고 할당하기
	//glGenVertexArrays(1, &m_VAO_rect);		//--- VAO 를 지정하고 할당하기


	//glBindVertexArray(m_VAO_triangle);		//--- VAO를 바인드하기
	//glBindVertexArray(m_VAO_rect);			//--- VAO를 바인드하기

	//glGenBuffers(1, &m_VBO_triangle);		//--- 2개의 VBO를 지정하고 할당하기
	//glGenBuffers(1, &m_VBO_rect);			//--- 2개의 VBO를 지정하고 할당하기

	glGenVertexArrays(1, &m_VAO_line);		//--- VAO 를 지정하고 할당하기
	glBindVertexArray(m_VAO_line);			//--- VAO를 바인드하기
	glGenBuffers(1, &m_VBO_line);			//--- 2개의 VBO를 지정하고 할당하기

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_line);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_line.size() * sizeof(Vertices), &m_vertices_line, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

}

void Mesh::updatebuffer()
{
	{	// vertex
		//glBindVertexArray(m_VAO_vtx);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_vtx);		// Position Color
		if (!m_vertices_vtx.empty()) {
			std::cout << m_vertices_vtx.back().x << m_vertices_vtx.back().y << '\n';
			std::cout << m_vertices_vtx.back().r << m_vertices_vtx.back().g << m_vertices_vtx.back().b << '\n';
			glBufferData(GL_ARRAY_BUFFER, m_vertices_vtx.size() * sizeof(Vertices), &m_vertices_vtx.front(), GL_STATIC_DRAW);

		}
	}
	{	// line
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_line);		// Position Color
		if(!m_vertices_line.empty())
			glBufferData(GL_ARRAY_BUFFER, m_vertices_line.size() * sizeof(Vertices), &m_vertices_line.front(), GL_STATIC_DRAW);

	}
	//{	// triangle
	//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_triangle);	// Position Color
	//	glBufferData(GL_ARRAY_BUFFER, m_vertices_triangle.size() * sizeof(Vertices), &m_vertices_triangle, GL_STATIC_DRAW);
	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(0));
	//	glEnableVertexAttribArray(0);
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GLfloat)));
	//	glEnableVertexAttribArray(1);
	//}
	//{	// rect
	//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_rect);		// Position Color
	//	glBufferData(GL_ARRAY_BUFFER, m_vertices_rect.size() * sizeof(Vertices), &m_vertices_rect, GL_STATIC_DRAW);
	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(0));
	//	glEnableVertexAttribArray(0);
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GLfloat)));
	//	glEnableVertexAttribArray(1);
	//}
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

	//glBindVertexArray(m_VAO_triangle);
	//glDrawArrays(GL_TRIANGLES, 0, cnttriangle);

	//glBindVertexArray(m_VAO_rect);
	//glDrawArrays(GL_TRIANGLES, 0, cntrect);

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
		Vertices tline[2]{};
		for (int i = 0; i < 2; ++i) {
			tline[i].x = x;
			tline[i].y = y;
			tline[i].z = z;
			tline[i].r = uid(dre);
			tline[i].g = uid(dre);
			tline[i].b = uid(dre);
			++cntlines;
		}
		m_vertices_line.push_back(*tline);
	}
	else if (draw_triangle) {
		Vertices ttri[3]{};
		for (int i = 0; i < 2; ++i) {
			ttri[i].x = x;
			ttri[i].y = y;
			ttri[i].z = z;
			ttri[i].r = uid(dre);
			ttri[i].g = uid(dre);
			ttri[i].b = uid(dre);
			++cnttriangle;
		}
		m_vertices_triangle.push_back(*ttri);
	}
	else if (draw_rect) {
		Vertices trect[6]{};
		for (int i = 0; i < 2; ++i) {
			trect[i].x = x;
			trect[i].y = y;
			trect[i].z = z;
			trect[i].r = uid(dre);
			trect[i].g = uid(dre);
			trect[i].b = uid(dre);
			++cntrect;
		}
		m_vertices_rect.push_back(*trect);
	}
}
