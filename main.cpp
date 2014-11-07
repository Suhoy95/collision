#include "main.h"

float colorSet[6][3] = {
	{0.0f,	0.0f,	0.0f},
	{1.0f,	1.0f,	1.0f},
	{1.0f,	0.0f,	0.0f},
	{0.0f,	1.0f,	0.0f},
	{0.0f,	0.0f,	1.0f},
	{0.5f,	0.5f,	0.5f}
};
model Model(WIDTH, HEIGHT);

void display(void)//визуализация
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Model.toDisplay();					
	Model.toDisplayDigit();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)//Обработка клавиатуры
{
	if(key == ESCAPE) // Выход, если нажали ESCAPE
		exit(0);
}

void initialize(void)// Инициализация холста 
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // фоновый цвет
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, WIDTH-5, -HEIGHT/2, HEIGHT/2, 1, -1);
	glMatrixMode(GL_MODELVIEW);	 
	glLoadIdentity();
}


int main(int argc, char* argv[])
{
	Model.getData();
	Model.toSimulate();
	glutInit( &argc, argv); // Инициализация glut
	//Инициализация окна
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow(NAME_WINDOW);
	//Ргестрирование функций
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	//Инициализация холста
	initialize();
	//Главный цикл программы
    glutMainLoop();	
}
