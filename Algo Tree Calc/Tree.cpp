#include <iostream>
using namespace std;
//due to the uncessary methods implmented for this binary tree expression solver, we removed the not needed once
struct nodeTree{
    double data;
    nodeTree * left;
    nodeTree * right;
    nodeTree(){
    	this->left=NULL;
    	this->right=NULL;
	}
	
};
class Tree{
    public:
        Tree(){
        	root=NULL;
		}
        nodeTree * root;
};


