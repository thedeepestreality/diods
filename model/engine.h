#include "api.h"

#ifndef __ENGINE
#define __ENGINE

 
class Engine {
	GLsizei Height, Width;
	int state;
	int dx;
	GLvoid SetProjectionMatrix(GLvoid);						// ������� ������������ ��������������
	GLvoid SetModelviewMatrix(GLvoid);						// ������� �������������� ������-����
public:
	GLvoid Resize(GLsizei width, GLsizei height);			// �������, ���������� ��� ��������� �������� ����
	GLvoid Init(GLvoid);									// �������, ��� ������� ��������� ����������
	GLvoid Draw(GLvoid);									// ��������� (render) �����
	GLvoid SetState(int state);
	GLvoid SetDx(GLfloat dx);
	
};

#endif