//g++ -o gol -Wall gol.c -mwindows glut32.lib -lopengl32 -lglu32 && gol.exe
#include <stdlib.h>
#include <windows.h>
#include "GL/glut.h"
#include <time.h>
#include <stdio.h>


int puffer = 0;
int h_r, g, b, v_r;
int *arr, *narr;
float x, y;
int sum = 0;
int var = 0;
int flag = 0;
int win1, win2, win3;

void initial() {
	srand(time(NULL));

	arr = (int*)malloc(1601 * sizeof(int));
	if (arr == NULL) exit(0);

	narr = (int*)malloc(1601 * sizeof(int));
	if (narr == NULL) exit(0);

	for (int i = 0; i < 1600; ++i)
	{
		narr[i] = 0;
		arr[i] = 0;
	}
}
void clear(){
	for (int i = 0; i < 1600; ++i)
	{
		narr[i] = 0;
		arr[i] = 0;
	}
}

void renderbitmap(float x, float y, void* font, char* string) {
	char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void menu_screen(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GLUT_SINGLE | GLUT_RGB);
	glLoadIdentity();
	glOrtho(-1.0, 100.0, -15.0, 100.0, 0.0, 1.0);

	char buf[100] = { 0 };

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	snprintf(buf,  sizeof(buf), "MENU");
	renderbitmap(40, 80, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	glColor3f(1, 0.1, 1);
	snprintf(buf,  sizeof(buf), "1. Random Seed");
	renderbitmap(5, 50, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "2. Glider");
	renderbitmap(5, 40, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "3. Spaceship");
	renderbitmap(5, 30, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "4. Blinker");
	renderbitmap(5, 20, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "5. Rpentomino");
	renderbitmap(5, 10, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "6. 2x2 Line Puffer");
	renderbitmap(5, 0, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	glFlush();
}

void frontscreen(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GLUT_SINGLE | GLUT_RGB);
	glLoadIdentity();
	glOrtho(-1.0, 100.0, -15.0, 100.0, 0.0, 1.0);

	char buf[100] = { 0 };

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	snprintf(buf,  sizeof(buf), "SAHYADRI COLLEGE OF ENGINEERING AND MANAGEMENT");
	renderbitmap(20.0, 90.0, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "ADYAR, MANGALORE");
	renderbitmap(38.0, 84.0, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glColor3f(0.5, 0, 0.5);
	snprintf(buf,  sizeof(buf), "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	renderbitmap(20, 79, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glColor3f(0.4, 0, 1);
	snprintf(buf,  sizeof(buf), "COMPUTER GRAPHICS AND VISUALIZATION");
	renderbitmap(28, 74, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glColor3f(1, 0.5, 0);
	snprintf(buf,  sizeof(buf), "A MINI PROJECT ON");
	renderbitmap(38, 65, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glColor3f(1, 0, 0);
	snprintf(buf,  sizeof(buf), "GAME OF LIFE");
	renderbitmap(40, 60, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glColor3f(1, 0.5, 0);
	snprintf(buf,  sizeof(buf), "TEAM MEMBERS");
	renderbitmap(5, 50, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glColor3f(0.5, 0, 0.5);
	snprintf(buf,  sizeof(buf), "THANAY CHETAN     4SF18CS168");
	renderbitmap(5, 40, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "SIMRAN SUNIL           4SF18CS150");
	renderbitmap(5, 35, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "DEPT OF CSE SEC B");
	renderbitmap(5, 30, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glColor3f(1, 0.5, 0);
	snprintf(buf,  sizeof(buf), "PROJECT GUIDED BY");
	renderbitmap(68, 50, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glColor3f(0.5, 0.2, 0.2);
	snprintf(buf,  sizeof(buf), "SUPRIYA");
	renderbitmap(68, 40, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "ASSISTANT PROFESSOR");
	renderbitmap(68, 35, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	snprintf(buf,  sizeof(buf), "DEPT OF CSE");
	renderbitmap(68, 30, GLUT_BITMAP_TIMES_ROMAN_24, buf);

	glColor3f(1, 0.1, 1);
	snprintf(buf,  sizeof(buf), "MINIMIZE THIS WINDOW TO START");
	renderbitmap(35, 10, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	glFlush();
}

void pause() {
	if(var == 0)Sleep(1500);
	var++;
	return;
}

void idle(void) {
	glutPostRedisplay();
	return;
}

void line_puffer(int i) {
	if (arr[i] == 1)
	{
		if (sum == 1 || sum == 2 || sum == 5) narr[i] = 1;
		else narr[i] = 0;

	}
	if (arr[i] == 0)
	{
		if (sum == 3 || sum == 6) narr[i] = 1;
		else narr[i] = 0;

	}
}

void display()
{

	x = -1.0, y = 1.0;
	h_r = v_r = 60; g = 240; b = 10;

	glBegin(GL_QUADS);
	for (int i = 0; i < 1600; ++i)
	{
		if( i > 39 )
			if ((i % 40 == 0))
			{
					y -= 0.05;
					x = -1.0;
					v_r -= 1;
					b += 5.75;
					g -= 5.75;
					h_r = v_r;
			}

		if (arr[i] == 1) {
			glColor3ub(h_r, g, b);
			h_r += 4.25;
		}
		else { glColor3ub(0, 0, 0); h_r += 4.25; }
		
		glVertex2f(x, y - 0.05);
		glVertex2f(x, y);
		glVertex2f(x + 0.05, y);
		glVertex2f(x + 0.05, y - 0.05);

		x += 0.05;
	}
	glEnd();
	glFlush(); 

	pause();

	for (int i = 0; i < 1600; ++i)
	{
		sum = 0;
					
		if (arr[i - 41] == 1) sum += 1;
		if (arr[i - 40] == 1) sum += 1;
		if (arr[i - 39] == 1) sum += 1;
		if (arr[i - 1] == 1) sum += 1;				
		if (arr[i + 1] == 1) sum += 1;
		if (arr[i + 39] == 1) sum += 1;
		if (arr[i + 40] == 1) sum += 1;
		if (arr[i + 41] == 1) sum += 1;

		if (puffer == 1) line_puffer(i);
		else {
			if (arr[i] == 1)
			{
				if (sum < 2 || sum > 3) narr[i] = 0;
				else narr[i] = 1;

			}
			if (arr[i] == 0)
			{
				if (sum == 3) narr[i] = 1;
				else narr[i] = 0;

			}
		}
						
	}

	for (int i = 0; i < 1600; ++i) arr[i] = narr[i];
		
	Sleep(60);
}

void linepuffer() {
	clear();
	arr[41] = 1; arr[82] = 1; arr[123] = 1; arr[205] = 1; arr[245] = 1; arr[285] = 1; arr[283] = 1; arr[363] = 1; arr[242] = 1;
	puffer = 1;
	var = 0;
}
void rpentomino() {
	clear();
	arr[495] = 1; arr[496] = 1; arr[534] = 1; arr[535] = 1; arr[575] = 1;
	puffer = 0;
	var = 0;
}
void spaceship() {
	clear();
	arr[81] = 1; arr[161] = 1; arr[202] = 1; arr[204] = 1; arr[205] = 1; arr[203] = 1; arr[165] = 1; arr[125] = 1; arr[84] = 1;
	puffer = 0;
	var = 0;
}
void glider(){
	clear();
	arr[45] = 1; arr[84] = 1; arr[124] = 1; arr[125] = 1; arr[126] = 1;
	puffer = 0;
	var = 0;
}
void blinker() {
	clear();
	arr[100] = 1; arr[140] = 1; arr[180] = 1;
	puffer = 0;
	var = 0;
}
void seed() {
	clear();
	for (int i = 0; i < 1600; ++i)
	{
		narr[i] = 0;
		arr[i] = rand() % 2;
	}
	puffer = 0;
	var = 0;
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': seed(); break;
	case '2': glider(); break;
	case '3': spaceship(); break;
	case '4': blinker(); break;
	case '5': rpentomino(); break;
	case '6': linepuffer();  break;
	case 'x': glutDestroyWindow(win1); glutSetWindow(win2); break;
	}
}

int main(int argc, char** argv)
{
	initial();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(581, 30);
	glutInitWindowSize(500, 500);
	win3 = glutCreateWindow("GOL");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutKeyboardFunc(myKeyboardFunc);
	glutDisplayFunc(display);

	glutInitWindowPosition(80, 30);
	glutInitWindowSize(500, 500);
	win2 = glutCreateWindow("Menu");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutKeyboardFunc(myKeyboardFunc);
	glutDisplayFunc(menu_screen);
	
	glutInitWindowPosition(80, 30);
	glutInitWindowSize(1200, 800);
	win1 = glutCreateWindow("Front Display");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutKeyboardFunc(myKeyboardFunc);
	glutDisplayFunc(frontscreen);
	
	glutIdleFunc(idle);
	glutMainLoop();
	free(arr);
	free(narr);
	return 0;
}

