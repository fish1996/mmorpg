#include "tree.h"
#include <math.h>
#include <queue>

Object::Object(int _i) : i(_i)
{

}

treeNode::treeNode()
{
	for (int i = 0; i < 4; i++) {
		child[i] = nullptr;
	}
	hasChild = false;
	object = nullptr;
}

quadtree::quadtree()
{
	head = new treeNode();
}

void quadtree::add(int layer, int x, int y,Object* obj)
{
	int n = pow(2, layer);
	int *index = new int[layer];
	int half = n >> 1;
	for (int i = layer - 1; i >= 0; i--) {
		if (x & half == 1) {
			if (y & half == 1) {
				index[i] = 2;
			}
			else {
				index[i] = 1;
			}
		}
		else {
			if (y & half == 1) {
				index[i] = 3;
			}
			else {
				index[i] = 0;
			}
		}
		x >> 1;
		y >> 1;
	}
	treeNode* node = head;
	for (int i = 0; i < layer - 1; i++) {
		node = node->child[index[i]];
	}
	treeNode* childNode = new treeNode();
	childNode->object = obj;
	node->child[index[layer - 1]] = childNode;
	node->hasChild = true;
}

void quadtree::print()
{
	treeNode* tmp;
	std::queue<treeNode*>q;
	q.push(head);
	int cur = 1;
	int curnum = 1;
	int nextnum = 0;
	while (!q.empty) {
		tmp = q.front();
		q.pop();
		if (tmp->hasChild) {
			curnum--;
			printf("[");
			for (int i = 0; i < 4; i++) {
				if (tmp->child[i]) {
					printf("%d", tmp->child[0]);
					q.push(tmp->child[i]);
					nextnum++;
				}
				if(i!=3)printf(", ");
			}
			printf("]");
			if (curnum == 0) {
				printf("\n");
				cur++;
				curnum = nextnum;
				nextnum = 0;
			}

		}
	}
	printf("\n");
}