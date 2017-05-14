
#include <math.h>
#include <queue>
#include "tree.h"
//#include <QTextStream>
//static QTextStream cout(stdout, QIODevice::WriteOnly);


Box::Box() {}
Box::Box(float _xmin, float _xmax, float _ymin, float _ymax) :
xmin(_xmin), xmax(_xmax), ymin(_ymin), ymax(_ymax)
{

}



treeNode::treeNode()
{
	for (int i = 0; i < 4; i++) {
		child[i] = nullptr;
	}
	hasChild = false;
}

void treeNode::setBox(treeNode* parent, int i)
{
	switch (i) {
	case 0: {
				box.xmax = parent->box.xmin + (parent->box.xmax - parent->box.xmin) / 2;
				box.xmin = parent->box.xmin;
				box.ymax = parent->box.ymax;
				box.ymin = parent->box.ymin + (parent->box.ymax - parent->box.ymin) / 2;
				break;
	}
	case 1: {
				box.xmax = parent->box.xmin + (parent->box.xmax - parent->box.xmin) / 2;
				box.xmin = parent->box.xmin;
				box.ymax = parent->box.ymin + (parent->box.ymax - parent->box.ymin) / 2;
				box.ymin = parent->box.ymin;
				break;
	}
	case 2: {
				box.xmax = parent->box.xmax;
				box.xmin = parent->box.xmin + (parent->box.xmax - parent->box.xmin) / 2;
				box.ymax = parent->box.ymin + (parent->box.ymax - parent->box.ymin) / 2;
				box.ymin = parent->box.ymin;
				break;
	}
	case 3: {
				box.xmax = parent->box.xmax;
				box.xmin = parent->box.xmin + (parent->box.xmax - parent->box.xmin) / 2;
				box.ymax = parent->box.ymax;
				box.ymin = parent->box.ymin + (parent->box.ymax - parent->box.ymin) / 2;
				break;
	}
	}
}

std::list<Object*> quadtree::findAll()
{
	return allObj;
}

quadtree::quadtree(float size, int l)
{
	int n = pow(2, l - 1);
	blockSize = size;
	layer = l;
	head = new treeNode();
	head->box.xmin = -n * size;
	head->box.xmax = n * size;
	head->box.ymin = -n * size;
	head->box.ymax = n * size;
}

std::list<Object*> quadtree::find(float x, float y, int layer)
{
	treeNode* node = head;
	treeNode* parent = nullptr;
	int count = 0;
	while (node != nullptr) {
		//	printf("count = %d\n", count);
		if (count == layer) {
			break;
		}
		int index;
		//	printf("%f %f\n", node->box.xmax - node->box.xmin, node->box.ymax - node->box.ymin);
		int i = 2 * (x + head->box.xmax) / (node->box.xmax - node->box.xmin);
		i = i % 2;
		int j = 2 * (y + head->box.ymax) / (node->box.ymax - node->box.ymin);
		j = j % 2;
		if (i == 0 && j == 0) {
			index = 1;
		}
		else if (i == 0 && j == 1) {
			index = 0;
		}
		else if (i == 1 && j == 0) {
			index = 2;
		}
		else if (i == 1 && j == 1) {
			index = 3;
		}
		parent = node;
		node = node->child[index];
		//	printf("index = %d\n", index);
		count++;
	}
	return parent->List;
}

void quadtree::add(int layer, int x, int y, Object* obj)
{
	allObj.push_back(obj);
	int n = pow(2, layer);
	int *index = new int[layer];
	int half = n >> 1;
	for (int i = layer - 1; i >= 0; i--) {
		if (x % 2 == 1) {
			if (y % 2 == 1) {
				index[i] = 2;
			}
			else {
				index[i] = 1;
			}
		}
		else {
			if (y % 2 == 1) {
				index[i] = 3;
			}
			else {
				index[i] = 0;
			}
		}
		x >>= 1;
		y >>= 1;
	}
	treeNode* node = head;
	for (int i = 0; i < layer - 1; i++) {
		if (!node->child[index[i]]) {
			node->child[index[i]] = new treeNode();
			node->child[index[i]]->setBox(node, index[i]);
		}
		if (node != head)node->List.push_back(obj);
		node->hasChild = true;
		node = node->child[index[i]];
	}
	treeNode* childNode = new treeNode();
	childNode->List.push_back(obj);
	if (node != head)node->List.push_back(obj);
	node->child[index[layer - 1]] = childNode;
	childNode->setBox(node, index[layer - 1]);
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
	while (!q.empty()) {
		tmp = q.front();
		q.pop();
		if (tmp->hasChild) {
			curnum--;
			//cout << "[";
			printf("[");
			for (int i = 0; i < 4; i++) {
				if (tmp->child[i]) {
					std::list<Object*>::iterator it;
					for (it = tmp->child[i]->List.begin(); it != tmp->child[i]->List.end(); it++) {
						printf("{%.0f %.0f %.0f}", (*it)->radius, (*it)->center_x, (*it)->center_y);
					}
					q.push(tmp->child[i]);
					nextnum++;
				}
				else printf("_");
				if (i != 3)printf(",");

			}
			printf("]");
		}
		if (curnum == 0) {
			printf("\n");
			cur++;
			curnum = nextnum;
			nextnum = 0;
		}
	}
}
