#define _CRT_SECURE_NO_WARNINGS        

#include <stdlib.h>         
#include <time.h>      
#include"gl/glut.h"        
#include "sceneManage.h"

float cx = 0, cz = -1;
float center[] = { 0, 0, 0 };
float eye[] = { 0,100, 1 };
float tx, ty = 10, ax, ay = 10, mx, my, zoom = 0;
bool isLine = false;
bool isDown = false;
bool isDrawAll = false;
sceneManage* scene;
float step = 1;

void reshape(int width, int height)
{
	if (height == 0) height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45, whRatio, 1, 500);
	glMatrixMode(GL_MODELVIEW);
}

void idle()
{
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	scene = new sceneManage();
	scene->init(cx,-cz);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);

	if (isLine)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glColor3f(0.3f, 0, 0);
	glTranslatef(cx, 0.1f, cz);
	glutSolidSphere(0.1f, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cx, 0.1, cz);
	glColor3f(0, 0, 0);
	glRotatef(90, 1, 0, 0);
	glRectd(-2, -2, 2, 2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glRotatef(90, 1, 0, 0);
	glRectd(-32, -32, 32, 32);
	glPopMatrix();

	if (isDrawAll) {
		std::list<Object*>::iterator it;
		std::list<Object*> list = scene->getAllObj();
		printf("size = %d\n", list.size());
		for (it = list.begin(); it != list.end(); it++) {
			(*it)->draw();
		}
	}
	else {
		scene->moveTo(cx, -cz);
		glColor3f(0, 0, 0);
		glPushMatrix();
		//glutSolidCube(3);
		std::set<Object*> set = scene->getObj();
		std::set<Object*>::iterator it;
		int count = 0;
		for (it = set.begin(); it != set.end(); it++) {
			count++;
			(*it)->draw();
		}
		//if(count!=0)printf("count = %d\n",count);
		glPopMatrix();
	}
	glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			isDown = true;
			mx = x;
			my = y;
		}
		else if (state == GLUT_UP) {
			isDown = false;
		}
	}
	glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
	if (isDown) {
		ax += 1.0f*(y - my) / 10.0f;
		ay += 1.0f*(x - mx) / 10.0f;
		mx = x;
		my = y;
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
//	printf("%d\n",key);
	switch (key)
	{
	case 'a': { //左移 
		cx -= step;
		eye[0] -= step;
		center[0] -= step;
		if (cx < -32) {
			cx = -32;
			eye[0] = -32;
			center[0] = -32;
		}
		break;
	}
	case 'd': { //右移    
		cx += step;
		eye[0] += step;
		center[0] += step;
		if (cx > 32) {
			cx = 32;
			eye[0] = 32;
			center[0] = 32;
		}
		break;
	}
	case 'w': { //上移    
		cz -= step;
		eye[2] -= step;
		center[2] -= step;
		if (cz < -32) {
			cz = -32;
			eye[2] = -32;
			center[2] = -32;
		}
		break;
	}
	case 's': { //下移    
		cz += step;
		eye[2] += step;
		center[2] += step;
		if (cz > 32) {
			cz = 32;
			eye[2] = 32;
			center[2] = 32;
		}
		break;
	}
	case 'z': { //后移    
		zoom += 1;
		break;
	}
	case 'c': { //前移    
		zoom -= 1;
		break;
	}
	case 'p': {
		// 切换绘制模式  
		if (isLine) {
			isLine = false;
		}
		else isLine = true;
		break;
	}
	case 'm': {
		if (isDrawAll) {
			isDrawAll = false;
		}
		else isDrawAll = true;
	}
	}
	//glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	int windowHandle = glutCreateWindow("Simple GLUT App");
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutMouseFunc(myMouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
	//system("pause");
	return 0;
}