#include "types.h"
#include "redBlackTree.h"
#include "relations.h"


Node_t* getUncle(Node_t* node){
	Node_t* grandparent = node->parent->parent;
	Node_t* parent = node->parent;

	if (NULL == grandparent){
		return NULL;
	}
	if (parent == grandparent->leftChild){
		return grandparent->rightChild;
	}else{
		return grandparent->leftChild;
	}
}

Node_t* getSibling(Node_t* node){
	Node_t* parent = node->parent;

	if (NULL == parent){
		return NULL;
	}
	if (node == parent->leftChild){
		return parent->rightChild;
	}else{
		return parent->leftChild;
	}
}

Node_t* getInorderSuccessor(Node_t* node){
	Node_t* successor = node->rightChild;
	if (successor != NULL){
		while(successor->leftChild != NULL){
			successor = successor->leftChild;
		}
	}
	return successor;
}

Node_t* getInorderAncestor(Node_t* node){
	Node_t* parent = node->parent;

	if (NULL == parent){
		/*Root Node*/
		return NULL;
	}
	if (node == parent->leftChild){
		return parent;
	}else{
		return getInorderAncestor(parent);
	}
}

ChildrenStatus_t checkChildrenStatus(Node_t* node){
	if (NULL == node->leftChild && NULL == node->rightChild){
		return NO_CHILDREN;
	}else if (node->leftChild != NULL && NULL == node->rightChild){
		return ONE_LEFT_CHILD;
	}else if (node->rightChild != NULL && NULL == node->leftChild){
		return ONE_RIGHT_CHILD;
	}else{
		return TWO_CHILDREN;
	}
}
