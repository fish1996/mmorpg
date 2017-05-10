#include "sceneManage.h"

sceneManage::sceneManage() 
{
	n = pow(2, LAYER + 1);
	offset = 2 * BLOCKSIZE;
	tree = new quadtree(BLOCKSIZE, LAYER + 1);
	Object* obj1 = new Object(1);
	Object* obj2 = new Object(2);
	Object* obj3 = new Object(3);
	Object* obj4 = new Object(4);
	tree->add(1, 0, 1, obj1);
	tree->add(2, 0, 0, obj2);
	tree->add(2, 3, 2, obj3);
	tree->add(3, 5, 7, obj4);
}

void sceneManage::updateSet()
{

}

void sceneManage::moveTo(float x, float y)
{
	if (x == cur_x && y == cur_y) {
		return;
	}
	if (x == cur_x + 1) {
		list[0] = tree->find(x - offset, y + offset, LAYER);
		list[1] = tree->find(x - offset, y, LAYER);
		list[2] = tree->find(x - offset, y - offset, LAYER);
	}
	else if (y == cur_y + 1) {
		list[2] = tree->find(x - offset, y - offset, LAYER);
		list[3] = tree->find(x         , y - offset, LAYER);
		list[4] = tree->find(x + offset, y - offset, LAYER);
	}
	else if (x == cur_x - 1) {
		list[4] = tree->find(x + offset, y - offset, LAYER);
		list[5] = tree->find(x + offset, y, LAYER);
		list[6] = tree->find(x + offset, y + offset, LAYER);
	}
	else if (y == cur_y - 1) {
		list[0] = tree->find(x - offset, y + offset, LAYER);
		list[7] = tree->find(x         , y + offset, LAYER);
		list[6] = tree->find(x + offset, y + offset, LAYER);
	}
	cur_x = x;
	cur_y = y;
}