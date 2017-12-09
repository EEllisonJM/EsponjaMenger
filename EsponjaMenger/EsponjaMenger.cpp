#include "stdafx.h"
#include <GL/glut.h>

double x_i = -1.5;
double y_i = -1.5;
double z_i = -1.5;

double tamanioCubo = 3.5;
int iteracion = 0;

bool clickMouseIzq = false;

float eje_X = 0.0f;
float eje_Y = 0.0f;

float aux_x = 0.0f;
float aux_y = 0.0f;

void graficarCubo(double x, double y, double z, double tamanio) {
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(x, y, z);
	glVertex3f(x + tamanio, y, z);
	glVertex3f(x + tamanio, y + tamanio, z);
	glVertex3f(x, y + tamanio, z);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(x + tamanio, y, z);
	glVertex3f(x + tamanio, y, z + tamanio);
	glVertex3f(x + tamanio, y + tamanio, z + tamanio);
	glVertex3f(x + tamanio, y + tamanio, z);

	glColor3f(0.5, 0.5, 0.8);
	glVertex3f(x + tamanio, y, z + tamanio);
	glVertex3f(x, y, z + tamanio);
	glVertex3f(x, y + tamanio, z + tamanio);
	glVertex3f(x + tamanio, y + tamanio, z + tamanio);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(x, y, z + tamanio);
	glVertex3f(x, y, z);
	glVertex3f(x, y + tamanio, z);
	glVertex3f(x, y + tamanio, z + tamanio);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(x, y + tamanio, z);
	glVertex3f(x + tamanio, y + tamanio, z);
	glVertex3f(x + tamanio, y + tamanio, z + tamanio);
	glVertex3f(x, y + tamanio, z + tamanio);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(x, y, z + tamanio);
	glVertex3f(x + tamanio, y, z + tamanio);
	glVertex3f(x + tamanio, y, z);
	glVertex3f(x, y, z);
	glEnd();
}

/* Funcion recursiva*/
void graficarCuboRecursivo(double x, double y, double z, double tamanio, int iteracion) {
	if (iteracion == 0) {//Caso base
		graficarCubo(x, y, z, tamanio);
	}
	else {
		tamanio = tamanio / 3;
		for (int i = 0; i<3; i++) {
			for (int j = 0; j<3; j++) {
				for (int k = 0; k<3; k++) {
					/*Agujeros*/
					if (i == 1 && j == 1 || i == 1 && k == 1 || j == 1 && k == 1 || i == 1 && j == 1 && k == 1) { 
						continue;//Omitir Agujeros y continuar
					}
					else {
						graficarCuboRecursivo(x + i*tamanio, y + j*tamanio, z + k*tamanio, tamanio, iteracion - 1); // Graficar cubo
					}
				}
			}
		}
	}
}

void init() {
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glRotatef(eje_X, 1.0f, 0.0f, 0.0f);
	glRotatef(eje_Y, 0.0f, 1.0f, 0.0f);

	graficarCuboRecursivo(x_i, y_i, z_i, tamanioCubo, iteracion);

	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h) {//Tamanio
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void ArrowKey(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		iteracion += 1;
		break;
	case GLUT_KEY_DOWN://Abajo
		if (iteracion - 1 > -1)
		{
			iteracion -= 1;
		}
		break;
	}
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(1); break;
	}	
}

void mouse(int button, int state, int x, int y) {
	//Tecla izquierda Presionada
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		clickMouseIzq = true;
		//Objtener coordenadas
		aux_x = x - eje_Y;
		aux_y = -y + eje_X;
	}
	else
		clickMouseIzq = false;
}

void mouseMotion(int x, int y) {
	if (clickMouseIzq) {
		//Girar
		eje_Y = x - aux_x;
		eje_X = y + aux_y;
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(550, 550);
	glutCreateWindow("Esponja de Menger");
	glutSpecialFunc(ArrowKey);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}