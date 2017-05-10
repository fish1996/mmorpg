#pragma once
#include "tree.h"
#include "object.h"
#include <set>
#include <list>

class sceneManage
{
private:
	
	enum{MAX = 8,
		SIZE = 3,
	    LAYER = 5,
	    BLOCKSIZE = 1,
	};
	quadtree* tree;
	std::set<Object*> set;
	std::list<Object*> list[MAX];
	int cur_x;
	int cur_y;
	int n;
	int offset;
	void updateSet();
public:
	void moveTo(float x, float y);
	sceneManage();
};