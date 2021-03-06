#include "stdafx.h"
#include <GL/glut.h>
#include "ImageLoader.h"

/*Punto inicial*/
double x_i = -1.5;
double y_i = -1.5;
double z_i = -1.5;

float eye_x, eye_y= 0.0f;
float eye_z = 10.0f;

/*Tamanio*/
double tamanioCubo = 3.5;
int n = 0;

bool clickMouseIzq = false;

float giro_eje_X = 0.0f;
float giro_eje_Y = 0.0f;

float aux_x = 0.0f;
float aux_y = 0.0f;

/*Texturas*/
GLuint _text1;
GLuint _text2;
GLuint _text3;
GLuint _text4;
GLuint _text5;
GLuint _text6;
/*Método para cargar texturas [imagen]*/
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
/*Método para cargar texturas [textura] */
void cargarTextura(GLuint _textura) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
/*Graficar cubo*/
void graficarCubo(double x, double y, double z, double tamanio) {
	/*Parte de abajo con [Textura 1]*/
	cargarTextura(_text1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y, z);//Punto inicial
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + tamanio, y, z);//Punto 2
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + tamanio, y + tamanio, z);//Punto 3
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x, y + tamanio, z);//Punto 4
	glEnd();
	/*Parte lateral Izq [Textura 2]*/
	cargarTextura(_text2);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x + tamanio, y, z);//Punto 1
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + tamanio, y, z + tamanio);//Punto 2
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + tamanio, y + tamanio, z + tamanio);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x + tamanio, y + tamanio, z);
	glEnd();

	/*Arriba [Textura 3]*/
	cargarTextura(_text3);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x + tamanio, y, z + tamanio);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y, z + tamanio);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x, y + tamanio, z + tamanio);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x + tamanio, y + tamanio, z + tamanio);
	glEnd();
	/*Parte lateral Derecha [Textura 4]*/
	cargarTextura(_text4);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y, z + tamanio);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x, y, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x, y + tamanio, z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x, y + tamanio, z + tamanio);
	glEnd();
	/*Enfrente Textura 5*/
	cargarTextura(_text5);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y + tamanio, z);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + tamanio, y + tamanio, z);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + tamanio, y + tamanio, z + tamanio);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x, y + tamanio, z + tamanio);
	glEnd();
	/*Atras [Textura 6]*/
	cargarTextura(_text6);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x, y, z + tamanio);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x + tamanio, y, z + tamanio);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + tamanio, y, z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x, y, z);
	glEnd();
}

/* Método recursivo para graficar la Esponja de Menger*/
void graficarEsponjaMenger(double x, double y, double z, double tamanio, int n) {
	if (n == 0)//Caso base
		graficarCubo(x, y, z, tamanio);//Graficar un cubo	
	else {
		tamanio = tamanio / 3;
		for (int i = 0; i<3; i++) {
			for (int j = 0; j<3; j++) {
				for (int k = 0; k<3; k++) {
					/*Agujeros*/
					if (i == 1 && j == 1 ||
						i == 1 && k == 1 ||
						j == 1 && k == 1 ||
						i == 1 && j == 1 && k == 1) {
						continue;//Omitir Agujeros y continuar
					}
					else {// Graficar cubos
						graficarEsponjaMenger(
						x + i*tamanio,
						y + j*tamanio,
						z + k*tamanio,
						tamanio,
						n - 1);
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

	gluLookAt(eye_x, eye_y, eye_z, 0.0f, 0.0f, 0.0f, 0.0f, 0.01f, 0.0f);
	glPushMatrix();
	
	glRotatef(giro_eje_X, 1.0f, 0.0f, 0.0f);
	glRotatef(giro_eje_Y, 0.0f, 1.0f, 0.0f);
	//glRotatef(giro_eje_Z, 0.0f, 0.0f, 1.0f);

	graficarEsponjaMenger(x_i, y_i, z_i, tamanioCubo, n);

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
/*Remodelar*/
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
	case GLUT_KEY_UP:/*Aumentar iteracion*/
		n += 1;
		break;
	case GLUT_KEY_DOWN:/*Disminuir iteracion*/
		if (n - 1 > -1)
			n -= 1;
		break;
	}
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(1); break;
	case 'w':
		eye_z -= .2;
		break;
	case 's':
		eye_z += .2;
		break;
	case 'W':
		eye_z -= .2;
		break;
	case 'S':
		eye_z += .2;
		break;
	}
}

void mouse(int button, int state, int x, int y) {	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {/*Tecla izquierda Presionada[mouse]*/
		clickMouseIzq = true;
		aux_x = x - giro_eje_Y;
		aux_y = -y + giro_eje_X;
	}
	else
		clickMouseIzq = false;
}
/*Movimiento del Mouse*/
void mouseMotion(int x, int y) {
	if (clickMouseIzq) {
		giro_eje_Y = x - aux_x;
		giro_eje_X = y + aux_y;
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(650, 550);
	glutCreateWindow("Esponja de Menger");
	glEnable(GL_DEPTH_TEST);
	initRendering();
	glutSpecialFunc(ArrowKey);
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);/*sets the mouse callback for the current window*/
	glutMotionFunc(mouseMotion);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}