#include "types.h"

#include <stdlib.h>
#include <stdio.h>

#include "deleteRBT.h"
#include "insertionStrategiesRBT.h"
#include "redBlackTree.h"
#include "rulesCheckers.h"

Node_t* addNodeColor (value_t value, int color, Node_t* root );
Node_t* createRootNode(value_t value, Node_t** root);

Node_t** initTreeRoot(void){
	Node_t** root;
	root = calloc (1, sizeof(Node_t*));
	return root;
}

Node_t** getNextBinaryBranchNode (Node_t* node, value_t value){
	if (value < node->value){
		return &(node->leftChild);
	}else if (value > node->value){
		return &(node->rightChild);
	}else{
		return NULL;
	}
}

Node_t* addNode (value_t value, Node_t** root ){
	Node_t* node;

	if (NULL == *root){
		/*first element*/
		return createRootNode(value, root);
	}
	node = addNodeColor(value, RED, *root);
	if (NULL == node) {
		return NULL;
	}
	if (node->parent->color == RED){
		fixNodeToFitRBTRules(node,root);
	}
	return node;
}

void rotate(Node_t* const node, int side, Node_t** root){
	Node_t* parent = node->parent;
	Node_t* childNodeToSwitchWith =  (side == LEFT) ? node->rightChild : node->leftChild;

	/*Update parent link*/
	if (NULL == parent){
		*root = childNodeToSwitchWith;
		childNodeToSwitchWith->parent = NULL;
	}else{
		if (parent->leftChild == node){
			parent->leftChild = childNodeToSwitchWith;
		}else{
			parent->rightChild = childNodeToSwitchWith;
		}
		childNodeToSwitchWith->parent = parent;
	}

	/*make original child parent to rotated node*/
	node->parent = childNodeToSwitchWith;
	if (side == LEFT){
		node->rightChild = childNodeToSwitchWith->leftChild;
		if (node->rightChild != NULL){
			node->rightChild->parent = node;
		}
		childNodeToSwitchWith->leftChild = node;
	}else{
		node->leftChild = childNodeToSwitchWith->rightChild;
		if (node->leftChild != NULL){
			node->leftChild->parent = node;
		}
		childNodeToSwitchWith->rightChild = node;
	}
}


Node_t* createRootNode(value_t value, Node_t** root){
	Node_t* node;

	node = calloc (1, sizeof (Node_t));
	node->value = value;
	node->color = BLACK;
	node->parent = NULL;
	*root = node;
	return node;
}

Node_t* addNodeColor (value_t value, int color, Node_t* root ){
	Node_t* node = root;
	Node_t** newNode;

	while (node != NULL){
		if (node->value == value){
			/*node with this value already exists*/
			return NULL;
		}
		newNode = getNextBinaryBranchNode (node,value);
		if (NULL == *newNode){
			break;
		}
		node = *newNode;
	}
	*newNode = calloc (1, sizeof (Node_t));
	if (NULL == *newNode){
		printf ("Out of Memory\n");
		return NULL;
	}
	(*newNode)->value = value;
	(*newNode)->color = color;
	(*newNode)->parent = node;

	return *newNode;
}

Node_t* getNode (value_t value, Node_t** root ){
	Node_t* node = *root;
	Node_t** newNode;

	while (node != NULL){
		if (node->value == value){
			return node;
		}
		newNode = getNextBinaryBranchNode (node,value);
		node = *newNode;
	}
	return NULL;
}

void deleteNode(value_t value, Node_t** root){
	Node_t* node = *root;

	if (NULL == *root){
		return;
	}
	if (value == (*root)->value){
		if (NULL == (*root)->leftChild && NULL == (*root)->rightChild){
			free(*root);
			*root = NULL;
			return;
		}
	}
	while (node != NULL){
		if (node->value == value){
			deleteNodeAndFixRBTree(node, root);
			return;
		}
		node = * (getNextBinaryBranchNode (node,value));
	}
}
