#include "api.h"

#ifndef __ENGINE
#define __ENGINE

 
class Engine {
	GLsizei Height, Width;
	int state;
	int dx;
	GLvoid SetProjectionMatrix(GLvoid);						// Задание проективного преобразования
	GLvoid SetModelviewMatrix(GLvoid);						// Задание преобразования модели-вида
public:
	GLvoid Resize(GLsizei width, GLsizei height);			// Функция, вызываемая при изменении размеров окна
	GLvoid Init(GLvoid);									// Функция, для задания начальных параметров
	GLvoid Draw(GLvoid);									// Отрисовка (render) сцены
	GLvoid SetState(int state);
	GLvoid SetDx(GLfloat dx);
	
};

#endif