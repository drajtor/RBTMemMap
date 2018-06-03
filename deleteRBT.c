#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "deleteStrategiesRBT.h"
#include "redBlackTree.h"
#include "relations.h"

static void nodeIsLeafNode(Node_t* node, Node_t** root);
static void nodeHasOneChild(Node_t* node, Node_t* child, Node_t** root);
static void InorderSuccessorSwitch(Node_t* node, Node_t** root);
static void nodeHasTwoChildren (Node_t* node, Node_t** root);

void deleteNodeAndFixRBTree (Node_t* node, Node_t** root){
	ChildrenStatus_t childrenStatus;

#ifdef DEBUG_DELETIONS
	printf("Deleting node %d \n",node->value);
#endif
	childrenStatus = checkChildrenStatus(node);

	switch(childrenStatus ){
		case NO_CHILDREN: {
			nodeIsLeafNode(node, root);
			break;
		}
		case ONE_LEFT_CHILD: {
			nodeHasOneChild(node, node->leftChild, root);
			break;
		}
		case ONE_RIGHT_CHILD: {
			nodeHasOneChild(node, node->rightChild, root);
			break;
		}
		case TWO_CHILDREN: {
			nodeHasTwoChildren(node, root);
			break;
		}
	}
}

static void nodeIsLeafNode(Node_t* node, Node_t** root){
	Node_t* parent = node->parent;

	DoubleBlackDeleteStrategy(node, root);

	if (node == parent->leftChild ) {
		parent->leftChild = NULL;
	}else{
		parent->rightChild = NULL;
	}
#ifdef DEBUG_DELETIONS
	printf("Deleted leaf Node %d\n",node->value);
#endif
	free(node);
	node = NULL;
}


static void nodeHasOneChild(Node_t* node, Node_t* child, Node_t** root){
	Node_t* parent = node->parent;

	if (child->color == RED){
		child->color = BLACK;
	}
	if (NULL == parent){
		*root = child;
	}else{
		if (node == parent->leftChild ) {
			parent->leftChild = child;
		}else{
			parent->rightChild = child;
		}
		child->parent = parent;
	}
#ifdef DEBUG_DELETIONS
	printf("Deleted Node with one Child %d\n",node->value);
#endif
	free(node);
	node = NULL;
}

static void InorderSuccessorSwitch(Node_t* node, Node_t** root){
	Node_t* succesor;
	succesor = node->rightChild;

	while (succesor->leftChild != NULL){
		succesor = succesor->leftChild;
	}

	node->value = succesor->value;
	node->treeObject = succesor->treeObject;
	deleteNodeAndFixRBTree (succesor, root);

}

static void InorderPredecessorSwitch(Node_t* node, Node_t** root){
	Node_t* succesor;
	succesor = node->leftChild;

	while (succesor->rightChild != NULL){
		succesor = succesor->rightChild;
	}

	node->value = succesor->value;
	node->treeObject = succesor->treeObject;
	deleteNodeAndFixRBTree (succesor, root);

}

static void nodeHasTwoChildren (Node_t* node, Node_t** root){
	static char swap = 0;
	if (swap%2){
		InorderSuccessorSwitch(node, root);
	}else{
		InorderPredecessorSwitch(node, root);
	}
	swap++;
}


