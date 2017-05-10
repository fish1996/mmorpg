#pragma once
#include "tree.h"
#include "object.h"
#include <set>
#include <list>

class sceneManage
{
private:

	enum{
		MAX        = 8,
		SIZE       = 3,
		LAYER      = 6,
		CURLAYER   = 5,
		BLOCKSIZE  = 1,
	};
	bool *isUsed;
	quadtree* tree;
	std::set<Object*> set;
	std::list<Object*> list[MAX];
	int cur_x;
	int cur_y;
	int n;
	int offset;
	void removeSet(int i, int j, int k);
	void updateSet(int i, int j, int k);
	void updateSet(int i);
	void randBuildTree();
	void printMap();
public:
	void init(float x, float y);
	std::set<Object*>& getObj();
	void moveTo(float x, float y);
	sceneManage();
};