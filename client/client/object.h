#pragma once
class Object
{
public:
	float radius;
	float center_x;
	float center_y;
	Object(float _radius,float cx,float cy);
	void draw();
};