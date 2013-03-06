#include "engine.h"
#include <string>

GLvoid Engine::SetProjectionMatrix(GLvoid){
	glMatrixMode(GL_PROJECTION);						// Действия будут производиться с матрицей проекции
	glLoadIdentity();									// Текущая матрица (проекции) сбрасывается на единичную
	glFrustum(-1, 1, -1, 1, 3, 25);						// Устанавливается перспективная проекция
}

GLvoid Engine::SetModelviewMatrix(GLvoid){
	glMatrixMode(GL_MODELVIEW);							// Действия будут производиться с матрицей модели
	glLoadIdentity();									// Текущая матрица (модели) сбрасывается на единичную
	glTranslatef(0.0, 0.0, -15.0);						// Система координат переносится на 8 единиц вглубь сцены
	
	//glRotatef(30.0, 1.0, 0.0, 0.0);						// и поворачивается на 30 градусов вокруг оси x,
	//glRotatef(70.0, 0.0, 1.0, 0.0);						// а затем на 70 градусов вокруг оси y
}

GLvoid Engine::Resize(GLsizei width, GLsizei height){
	if (height == 0)									
	{
		height = 1;										
	}

	glViewport(0, 0, width, height);					// Устанавливается область просмотра

	Height = height;
	Width = width;

	SetProjectionMatrix();
	SetModelviewMatrix();
}


//-----Инициализация (основные расчеты)-----
GLvoid Engine::Init(GLvoid){

	glClearColor(0.2f, 0.5f, 0.75f, 1.0f);				// Устанавливается синий фон
	glClearDepth(1.0f);									// Устанавливается значение для
														// заполнения буфера глубины по умолчанию
	glEnable(GL_DEPTH_TEST);							// Включается тест глубины
	glDepthFunc(GL_LEQUAL);								// Устанавливается значение, используемое
														// в сравнениях при использовании
														// буфера глубины

	glShadeModel(GL_SMOOTH);							// Включается плавное затенение
	glEnable(GL_LINE_SMOOTH);							// Включается сглаживание линий
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);				// Выбирается самый качественный
														// режим сглаживания для линий
	glEnable(GL_BLEND);									// Включается смешение цветов, необходимое
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// для работы сглаживания и задается
														// способ смешения



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



//-----Отрисовка-----
GLvoid Engine::Draw(GLvoid)									
{

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Очищается буфер кадра и буфер глубины
	glPushMatrix();										// Запоминается матрица модели
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
