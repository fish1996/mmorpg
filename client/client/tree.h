#pragma once
#include <list>
#include "object.h"

struct Box
{
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	Box();
	Box(float _xmin, float _xmax, float _ymin, float _ymax);
};

struct treeNode {
	Box box;
	treeNode* child[4];
	std::list<Object*> List;
	bool hasChild;
	treeNode();
	void setBox(treeNode* parent, int i);
};

class quadtree
{
private:
	float blockSize;
	int layer;
	treeNode* head;
	std::list<Object*> allObj;
public:
	void print();
	std::list<Object*> findAll();
	std::list<Object*> find(float x, float y, int layer = -1);
	quadtree(float size, int l);
	void add(int layer, int x, int y, Object* obj);
};