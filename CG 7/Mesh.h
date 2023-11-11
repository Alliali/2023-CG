#pragma once
class Mesh
{
public:
	Mesh();
	~Mesh();

	void initbuffer();
	void updatebuffer();
	void draw();
	void meshdata(float x, float y, float z);
	void move();
	void release();

	bool draw_point = false;
	bool draw_line = false;
	bool draw_triangle = false;
	bool draw_rect = false;

	bool draw_right = false;
	bool draw_left = false;
	bool draw_up = false;
	bool draw_down = false;

private:
	GLuint m_VAO[4];

	GLuint m_VAO_vtx;
	GLuint m_VAO_line;
	GLuint m_VAO_triangle;
	GLuint m_VAO_rect;

	GLuint m_VBO_vtx;
	GLuint m_VBO_line;
	GLuint m_VBO_triangle;
	GLuint m_VBO_rect;

	int cntVertices;
	int cntlines;
	int cnttriangle;
	int cntrect;

	GLfloat m_fSpeed;

	// vector는 zeromemory로 초기화하는거 아닌듯
	std::vector<Vertices> m_vertices_vtx;
	std::vector<Vertices> m_vertices_line;
	std::vector<Vertices> m_vertices_triangle;
	std::vector<Vertices> m_vertices_rect;
};

