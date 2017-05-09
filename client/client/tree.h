#pragma once

class Object
{
	int i;
public:
	Object(int _i);
};
struct treeNode {
	treeNode* child[4];
	Object* object; //包含的对象
	bool hasChild;   //是否有孩子
	treeNode();
};

class quadtree
{
private:
	treeNode* head;
public:
	void print();
	quadtree();
	void add(int layer, int x, int y, Object* obj);
};
