#include "engine.h"
#include <string>

GLvoid Engine::SetProjectionMatrix(GLvoid){
	glMatrixMode(GL_PROJECTION);						// �������� ����� ������������� � �������� ��������
	glLoadIdentity();									// ������� ������� (��������) ������������ �� ���������
	glFrustum(-1, 1, -1, 1, 3, 25);						// ��������������� ������������� ��������
}

GLvoid Engine::SetModelviewMatrix(GLvoid){
	glMatrixMode(GL_MODELVIEW);							// �������� ����� ������������� � �������� ������
	glLoadIdentity();									// ������� ������� (������) ������������ �� ���������
	glTranslatef(0.0, 0.0, -15.0);						// ������� ��������� ����������� �� 8 ������ ������ �����
	
	//glRotatef(30.0, 1.0, 0.0, 0.0);						// � �������������� �� 30 �������� ������ ��� x,
	//glRotatef(70.0, 0.0, 1.0, 0.0);						// � ����� �� 70 �������� ������ ��� y
}

GLvoid Engine::Resize(GLsizei width, GLsizei height){
	if (height == 0)									
	{
		height = 1;										
	}

	glViewport(0, 0, width, height);					// ��������������� ������� ���������

	Height = height;
	Width = width;

	SetProjectionMatrix();
	SetModelviewMatrix();
}


//-----������������� (�������� �������)-----
GLvoid Engine::Init(GLvoid){

	glClearColor(0.2f, 0.5f, 0.75f, 1.0f);				// ��������������� ����� ���
	glClearDepth(1.0f);									// ��������������� �������� ���
														// ���������� ������ ������� �� ���������
	glEnable(GL_DEPTH_TEST);							// ���������� ���� �������
	glDepthFunc(GL_LEQUAL);								// ��������������� ��������, ������������
														// � ���������� ��� �������������
														// ������ �������

	glShadeModel(GL_SMOOTH);							// ���������� ������� ���������
	glEnable(GL_LINE_SMOOTH);							// ���������� ����������� �����
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);				// ���������� ����� ������������
														// ����� ����������� ��� �����
	glEnable(GL_BLEND);									// ���������� �������� ������, �����������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// ��� ������ ����������� � ��������
														// ������ ��������



}

GLvoid Engine::SetState(int st)
{
	state=st;
}

GLvoid Engine::SetDx(GLfloat x)
{
	dx+=x;
}

std::string convertInt(double number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}



//-----���������-----
GLvoid Engine::Draw(GLvoid)									
{

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// ��������� ����� ����� � ����� �������
	glPushMatrix();										// ������������ ������� ������
	{
		glRotatef(30.0f,0.0f,0.0f,1.0f);
	
		glColor3f(1.0f,1.0f,1.0f);
		glBegin(GL_QUADS);
			glVertex3f(-0.5f,-0.5f,0.0f);
			glVertex3f(-0.5f,0.5f,0.0f);
			glVertex3f(0.5f,0.5f,0.0f);
			glVertex3f(0.5f,-0.5f,0.0f);
		glEnd();
	}
	glPopMatrix();


}
