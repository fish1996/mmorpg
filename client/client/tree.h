#pragma once

class Object
{

public:
    int i;
	Object(int _i);
};
struct treeNode {
	treeNode* child[4];
	Object* object; //�����Ķ���
	bool hasChild;   //�Ƿ��к���
	treeNode();
};

class quadtree
{
private:
	treeNode* head;
public:
    void find(float x,float y);
	void print();
	quadtree();
	void add(int layer, int x, int y, Object* obj);
};
