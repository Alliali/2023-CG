#include <stdio.h>
#include <stdlib.h>

inline char* filetobuf(const char* file)
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

inline void ReadObj(FILE* path) {
	char count[128];
	int vertexnum = 0;
	int facenum = 0;
	int uvnum = 0;

	//--- 1. ��ü ���ؽ� ���� �� �ﰢ�� ���� ����
	while (!feof(path)) {
		fscanf(path, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexnum++;
		else if (count[0] == 'f' && count[1] == '\0')
			facenum++;	// face�� ��
		else if (count[0] == 'v' && count[1] == 'n' && count[3] == '\0')
			uvnum++;	// �ϴ��� �������Ͽ� vt�� ��� vn����
		memset(count, '\0', sizeof(count));
	}
	rewind(path);

	int vertIndex = 0;
	int faceIndex = 0;
	int uvIndex = 0;

	//--- 2. �޸� �Ҵ�
	glm::vec3* vertex = new glm::vec3[vertexnum];
	glm::vec3* face = new glm::vec3[facenum];
	glm::vec3* uvdata = new glm::vec3[facenum];
	glm::vec2* uv = new glm::vec2[uvnum];

	char bind[128];

	//--- 3. �Ҵ�� �޸𸮿� �� ���ؽ�, ���̽�, uv ���� �Է�
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
	//--- �ʿ��� ��� �о�� ���� ���� ���� � ����
}
