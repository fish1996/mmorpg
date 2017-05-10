#include "object.h"
#include "gl/glut.h"
#include <stdio.h>
Object::Object(float r, float cx, float cy) :radius(r), center_x(cx), center_y(cy)
{
	//printf("radius = %f \n", radius);
}

void Object::draw()
{
	glPushMatrix();
	//printf("%f %f %f\n", center_x - radius / 2, radius / 2, center_y - radius / 2);
	glTranslatef(center_x - radius / 2, radius/2, center_y - radius / 2);
	glutSolidCube(radius);
	glPopMatrix();
}