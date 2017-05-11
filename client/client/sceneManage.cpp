#include "sceneManage.h"
#include <fstream>
#include <time.h>

sceneManage::sceneManage()
{
	srand(time(nullptr));
	n = pow(2.0, LAYER);
	offset = 2 * BLOCKSIZE;
	tree = new quadtree(BLOCKSIZE, LAYER);
	// block大小为1, 层数为6
	randBuildTree();
}

void sceneManage::init(float x, float y)
{
	list[0] = tree->find(x - offset, y + offset, LAYER);
	list[1] = tree->find(x - offset, y, LAYER);
	list[2] = tree->find(x - offset, y - offset, LAYER);
	list[3] = tree->find(x, y - offset, LAYER);
	list[4] = tree->find(x + offset, y - offset, LAYER);
	list[5] = tree->find(x + offset, y, LAYER);
	list[6] = tree->find(x + offset, y + offset, LAYER);
	list[7] = tree->find(x, y + offset, LAYER);
}

void sceneManage::printMap()
{
	std::ofstream out("map.txt");
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			if (isUsed[64 * i + j]) {
				out << "X ";
			}
			else {
				out << ". ";
			}
		}
		out << "\n";
	}
	out << "\n";
}

void sceneManage::randBuildTree()
{
	isUsed = new bool[4096];
	for (int i = 0; i < 4096; i++) {
		isUsed[i] = false;
	}
	int num[6];
	num[0] = 0; // 4
	num[1] = 1; // 16
	num[2] = 3; // 64
	num[3] = 20; // 256
	num[4] = 40; // 1024
	num[5] = 200; // 4096

	int size = 64;
	int half = size >> 1;
	int nsize = 2;
	for (int k = 0; k < 6; k++) {
		//printf("size = %d half=%d\n", size,half);
		for (int i = 0; i < num[k]; i++) {
			int r;
			do {
				r = rand() % 4096;
			} while (isUsed[r]);
			int r1 = (r / 64) % nsize;//x
			int r2 = (r % 64) % nsize;//y
			float h = 1.0 * half / 2;
			//printf("h = %.1f\n", h);
			//printf("r1 = %f r2 = %f\n", -32 + h + r2 *half, -32 + h + r1 *half);
			//printf("h = %.0f r = %.0f cx = %.0f cy = %.0f ", h, half, -h + r2 *half, -h + r1 *half);
			Object* obj = new Object(half, -32 + h + r2 *half, -32 + h + r1 *half);
			tree->add(k + 1, r1, r2, obj);

			for (int k1 = r1 * half; k1 < (r1 + 1) * half; k1++) {
				for (int k2 = r2 * half; k2 < (r2 + 1) * half; k2++) {
					isUsed[k1 * 64 + k2] = true;
				}
			}
		}
		size = half;
		half = size >> 1;
		nsize = nsize << 1;
	}
	//tree->print();
	printMap();
}

void sceneManage::removeSet(int i)
{
	std::list<Object*>::iterator it;
	for (it = list[i].begin(); it != list[i].end(); it++) {
		set.erase(*it);
	}
}

void sceneManage::removeSet(int i, int j, int k)
{
	std::list<Object*>::iterator it;
	for (it = list[i].begin(); it != list[i].end(); it++) {
		set.erase(*it);
	}
	for (it = list[j].begin(); it != list[j].end(); it++) {
		set.erase(*it);
	}
	for (it = list[k].begin(); it != list[k].end(); it++) {
		set.erase(*it);
	}
}

void sceneManage::updateSet(int i)
{
	std::list<Object*>::iterator it;
	for (it = list[i].begin(); it != list[i].end(); it++) {
		set.insert(*it);
	}
}

void sceneManage::updateSet(int i, int j, int k)
{
	std::list<Object*>::iterator it;
	for (it = list[i].begin(); it != list[i].end(); it++) {
		set.insert(*it);
	}
	for (it = list[j].begin(); it != list[j].end(); it++) {
		set.insert(*it);
	}
	for (it = list[k].begin(); it != list[k].end(); it++) {
		set.insert(*it);
	}
}

std::list<Object*>& sceneManage::getAllObj()
{
	return tree->findAll();
}

std::set<Object*>& sceneManage::getObj()
{
	return set;
}

void sceneManage::moveTo(float x, float y)
{
	if (x == cur_x && y == cur_y) {
		return;
	}
	if (x == cur_x + 1) {
		printf("move right\n");
		removeSet(0, 1, 2);
		list[0] = tree->find(x - offset, y + offset, CURLAYER);
		list[1] = tree->find(x - offset, y, CURLAYER);
		list[2] = tree->find(x - offset, y - offset, CURLAYER);
		updateSet(0, 1, 2);
	}
	else if (y == cur_y + 1) {
		printf("move front\n");
		removeSet(2, 3, 4);
		list[2] = tree->find(x - offset, y - offset, CURLAYER);
		list[3] = tree->find(x, y - offset, CURLAYER);
		list[4] = tree->find(x + offset, y - offset, CURLAYER);
		updateSet(2, 3, 4);
	}
	else if (x == cur_x - 1) {
		printf("move left\n");
		removeSet(4, 5, 6);
		list[4] = tree->find(x + offset, y - offset, CURLAYER);
		list[5] = tree->find(x + offset, y, CURLAYER);
		list[6] = tree->find(x + offset, y + offset, CURLAYER);
		updateSet(4, 5, 6);
	}
	else if (y == cur_y - 1) {
		printf("move back\n");
		removeSet(0, 7, 6);
		list[0] = tree->find(x - offset, y + offset, CURLAYER);
		list[7] = tree->find(x, y + offset, CURLAYER);
		list[6] = tree->find(x + offset, y + offset, CURLAYER);
		updateSet(0, 7, 6);
	}
	list[8] = tree->find(x, y, CURLAYER);
	updateSet(8);
	cur_x = x;
	cur_y = y;
}