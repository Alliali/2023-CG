#version 330 core
//out vec4 color;

in vec3 out_Color;
out vec4 FragColor;

void main ()
{
	//color = vec4 (1.0, 0.0, 0.0, 1.0); //--- ���������� ���� ����
	FragColor = vec4(out_Color, 1.0);
}
//Ȯ�� -> ���� -> �˻� -> opengl -> GLSL language~ �ٿ�ε�