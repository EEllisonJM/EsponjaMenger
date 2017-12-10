#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ImageLoader.h"
#include <math.h>
#define M_PI 3.14159265358979323846
using namespace std;

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

GLuint _text1;
GLuint _text2;
GLuint _text3;
GLuint _text4;
GLuint _text5;
GLuint _text6;



GLuint loadTexture(Image* image) {
	GLuint idtextura;
	glGenTextures(1, &idtextura);
	glBindTexture(GL_TEXTURE_2D, idtextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return idtextura;
}


void initRendering() {
	Image* lado1 = loadBMP("1.bmp");
	_text1 = loadTexture(lado1);
	delete lado1;

	Image* lado2 = loadBMP("2.bmp");
	_text2 = loadTexture(lado2);
	delete lado2;

	Image* lado3 = loadBMP("3.bmp");
	_text3 = loadTexture(lado3);
	delete lado3;

	Image* lado4 = loadBMP("4.bmp");
	_text4 = loadTexture(lado4);
	delete lado4;

	Image* lado5 = loadBMP("5.bmp");
	_text5 = loadTexture(lado5);
	delete lado5;

	Image* lado6 = loadBMP("6.bmp");
	_text6 = loadTexture(lado6);
	delete lado6;
}

void cargarTextura(GLuint _textura) {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void graficarCubo(double x, double y, double z, double tamanio) {

	cargarTextura(_text1);
	glBegin(GL_POLYGON);
	//glColor3f(0.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y, z);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + tamanio, y, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + tamanio, y + tamanio, z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x, y + tamanio, z);
	glEnd();

	cargarTextura(_text2);
	glBegin(GL_POLYGON);
	//glColor3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x + tamanio, y, z);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + tamanio, y, z + tamanio);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + tamanio, y + tamanio, z + tamanio);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x + tamanio, y + tamanio, z);
	glEnd();


	cargarTextura(_text3);
	glBegin(GL_POLYGON);
	//glColor3f(0.5, 0.5, 0.8);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x + tamanio, y, z + tamanio);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y, z + tamanio);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x, y + tamanio, z + tamanio);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x + tamanio, y + tamanio, z + tamanio);
	glEnd();


	cargarTextura(_text4);
	glBegin(GL_POLYGON);
	//glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y, z + tamanio);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x, y + tamanio, z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x, y + tamanio, z + tamanio);
	glEnd();


	cargarTextura(_text5);
	glBegin(GL_POLYGON);
	//glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y + tamanio, z);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + tamanio, y + tamanio, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + tamanio, y + tamanio, z + tamanio);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x, y + tamanio, z + tamanio);
	glEnd();


	cargarTextura(_text6);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	//glColor3f(1.0, 0.0, 0.0);
	glVertex3f(x, y, z + tamanio);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + tamanio, y, z + tamanio);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + tamanio, y, z);
	glTexCoord2f(1.0, 1.0);
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
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glMatrixMode(GL_MODELVIEW);
	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);


	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();

	glRotatef(eje_X, 1.0f, 0.0f, 0.0f);
	glRotatef(eje_Y, 0.0f, 1.0f, 0.0f);

	graficarCuboRecursivo(x_i, y_i, z_i, tamanioCubo, iteracion);

	glPopMatrix();
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

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(550, 550);
	glutCreateWindow("Esponja de Menger");
	glEnable(GL_DEPTH_TEST);
	initRendering();
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
