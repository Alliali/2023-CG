#pragma once
#include "stdafx.h"

class shaders
{
public:
	shaders() = default;
	shaders(const char* vertexfile, const char* fragmentfile);
	~shaders();

public:
	void shaderuse();
	void setUniform_matrix4fv(const char* shaderid, glm::mat4 matrix);

private:
	char* filetobuf(const char* file);


private:
	GLchar* vertexSource;
	GLchar* fragmentSource;

	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint shaderProgramID;

};

