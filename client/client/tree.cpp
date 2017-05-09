#include "tree.h"
#include <math.h>
#include <queue>
#include <QTextStream>
static QTextStream cout(stdout, QIODevice::WriteOnly);
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

void quadtree::find(float x,float y)
{

}

void quadtree::add(int layer, int x, int y,Object* obj)
{

	int n = pow(2, layer);
	int *index = new int[layer];
	int half = n >> 1;
  //  cout << "n = "<<n<<" half = "<<half;
	for (int i = layer - 1; i >= 0; i--) {
       // cout << " x = "<<x<<" y = "<<y;
       // cout << " x & half = "<<(x & half);
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
       // cout <<" index = "<<index[i]<<endl;
        x >>= 1;
        y >>= 1;
	}
	treeNode* node = head;
	for (int i = 0; i < layer - 1; i++) {
        if(!node->child[index[i]]) {
            node->child[index[i]] = new treeNode();
        }
        node->hasChild = true;
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
    while (!q.empty()) {
		tmp = q.front();
		q.pop();
		if (tmp->hasChild) {
			curnum--;
            cout<<"[";
			for (int i = 0; i < 4; i++) {
				if (tmp->child[i]) {
                    if(tmp->child[i]->object)cout<<tmp->child[i]->object->i;
					q.push(tmp->child[i]);
					nextnum++;
				}
                if(i!=3)cout<<",";
			}
            cout<<"]";

			if (curnum == 0) {
                cout<<"\n";
                //printf("\n");
				cur++;
				curnum = nextnum;
				nextnum = 0;
			}

		}
	}
    //printf("\n");
}
