#pragma once
struct vec {
	float x;
	float y;
	float z;
};
class Object
{
public:
	float radius;
	float center_x;
	float center_y;
	vec color;
	Object(float _radius, float cx, float cy);
	void draw();
};