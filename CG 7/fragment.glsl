#version 330 core
//out vec4 color;

in vec3 out_Color;
out vec4 FragColor;

void main ()
{
	//color = vec4 (1.0, 0.0, 0.0, 1.0); //--- 빨강색으로 색상 고정
	FragColor = vec4(out_Color, 1.0);
}
//확장 -> 관리 -> 검색 -> opengl -> GLSL language~ 다운로드