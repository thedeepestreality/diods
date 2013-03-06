#include "engine.h"
BOOL keys[256];
 
Engine *engine;
 static int lx=0, ly=0;
 int dy;
 //int dx;
 

GLvoid display(GLvoid)
{
      engine->Draw();
      glutSwapBuffers();
}
 
GLvoid reshape(GLsizei width, GLsizei height)
{
      engine->Resize(width, height);
}


//-----Обработка нажатий клавиш
GLvoid key_func(unsigned char key,int x,int y) 
{ 
	//glLoadIdentity();
	switch (key)
	{
		case '0':
		{
			engine->SetState(0);
			break;
		}
		case '1':
		{
			engine->SetState(1);
			break;
		}
		case '2':
		{
			engine->SetState(2);
			break;
		}
		case 'w':
		{
			glTranslatef(0.0f,0.0f,0.1f);
			break;
		}
		case 's':
		{
			glTranslatef(0.0f,0.0f,-0.1f);
			break;
		}

	}
	glutPostRedisplay();
}

//-----Разность координат мышки по сравнению с прошлым положением
void motionleft (int mousex,int mousey)
{

		//dy=(ly-mousey);        //wrong: only measures movments
		engine->SetDx(lx-mousex);

		lx=mousex;			//worng : only choosen first time 
		//ly=mousey;
		
		//if (dy>0)
		//glRotatef(dy,1.0f,0.0f,0.0f);
		//glRotatef(dx,0.0f,1.0f,0.0f);
		glutPostRedisplay();
}


//-----Обработка дивжений мышки
GLvoid mouse(int button,int state,int x,int y) 
{ 
	switch (button)
	{
		
		case GLUT_LEFT_BUTTON:
			{
				if(state == GLUT_DOWN)
				{
					lx=x;
					ly=y;
					glutMotionFunc(motionleft);
				}
				break;
			}
	}
	//glutPostRedisplay();
}
 

//-----Основная функция-----
int main(int argc, char** argv)
{
		
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
      glutInitWindowSize(800, 600);
      glutInitWindowPosition(100, 100);
      glutCreateWindow("Cluster 1.0");

	  //здесь вся отрисовка и расчеты
      engine = new Engine();
      engine->Init();
	  engine->SetDx(0.0f);

	  //присваивание функций
	  glutDisplayFunc(display);
      glutReshapeFunc(reshape);
	  glutKeyboardFunc(key_func);
	  glutMouseFunc(mouse);
      glutMainLoop();
	  
      return 0;
}