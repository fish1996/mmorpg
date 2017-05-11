#include "object.h"

#include <stdlib.h>
#include <stdio.h>
#include "gl/glut.h"
Object::Object(float r, float cx, float cy) :radius(r), center_x(cx), center_y(cy)
{
	color.x = (1.0*(rand() % 100) / 100);
	color.y = (1.0*(rand() % 100) / 100);
	color.z = (1.0*(rand() % 100) / 100);
	//printf("radius = %f \n", radius);
}

void Object::draw()
{
	glPushMatrix();
	glColor3f(color.x,color.y,color.z);
	//printf("%f %f %f\n", center_x - radius / 2, radius / 2, center_y - radius / 2);
	glTranslatef(center_x - radius / 2, radius / 2, center_y - radius / 2);
	glutSolidCube(radius);
	glPopMatrix();
}
