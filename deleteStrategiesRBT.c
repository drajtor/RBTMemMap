#include "insertionStrategiesRBT.h"
#include "types.h"
#include "redBlackTree.h"
#include "relations.h"

/*Sibling and its child situation. rightLeft mean Sibling is right child, and siblings child is left child*/
typedef enum {
	LEFT_LEFT,
	LEFT_RIGHT,
	RIGHT_RIGHT,
	RIGHT_LEFT
}SiblingBlackAndChildrenRedCases_t;

static void siblingIsBlack (Node_t* node, Node_t* sibling, Node_t** root);
static void sibingIsRed(Node_t* node, Node_t* sibling, Node_t** root);
static void rightLeft_leftRightStrategy (Node_t* sibling, Node_t* siblingsChild, Node_t** root_);
static void rightRight_leftLeftStrategy (Node_t* node, Node_t** root_);
static void siblingIsBlackAndChildrenAreBlackToo (Node_t* node, Node_t* sibling, Node_t** root);
static void siblingIsBlackAndMinOneChildIsRed (Node_t* node, Node_t* sibling, Node_t** root);
static SiblingBlackAndChildrenRedCases_t checkAfterDeletonStrategyForBlackSiblingAndOneRedChild (Node_t* sibling);


void DoubleBlackDeleteStrategy(Node_t* node, Node_t** root){
	Node_t* sibling = getSibling(node);

	if (NULL == sibling){
		return;
	}
	if ( sibling->color == BLACK){
		siblingIsBlack (node, sibling, root);
	}else{
		sibingIsRed(node, sibling, root);
	}
}

static void siblingIsBlack (Node_t* node, Node_t* sibling, Node_t** root){

	if (( sibling->leftChild != NULL && RED == sibling->leftChild->color) ||
			(sibling->rightChild != NULL && RED == sibling->rightChild->color)){
		siblingIsBlackAndMinOneChildIsRed(node, sibling, root);
	}else{
		siblingIsBlackAndChildrenAreBlackToo(node, sibling, root);
	}
}

static void sibingIsRed(Node_t* node, Node_t* sibling, Node_t** root){
	Node_t* parent = node->parent;
	int color = BLACK;

	if (node == parent->leftChild){
		rotate(parent,LEFT, root);
	}else{
		rotate(parent,RIGHT, root);
	}
	Node_t* grandParent = parent->parent;

	color = parent->color;
	parent->color = grandParent->color;
	grandParent->color = color;

	if (NULL == sibling){
		parent->color = BLACK;
	}else{
		DoubleBlackDeleteStrategy(node, root);
	}
}

/*Sibling and its child situation. rightLeft means Sibling is right child, and siblings child is left child*/
static void rightLeft_leftRightStrategy (Node_t* sibling, Node_t* siblingsChild, Node_t** root){
	int color = BLACK;

	if (siblingsChild == sibling->rightChild){
		rotate(sibling, LEFT, root);
	}else{
		rotate(sibling, RIGHT, root);
	}
	color = siblingsChild->color;
	siblingsChild->color = sibling->color;
	sibling->color = color;
	rightRight_leftLeftStrategy(sibling,root);
}

/*Sibling and its child situation. rightLeft means Sibling is right child, and siblings child is left child*/
static void rightRight_leftLeftStrategy (Node_t* siblingsChild, Node_t** root){
	fixNodeToFitRBTRules(siblingsChild,root);
}

static void siblingIsBlackAndChildrenAreBlackToo (Node_t* node, Node_t* sibling, Node_t** root){
	sibling->color = RED;
	if (RED == node->parent->color){
		node->parent->color = BLACK;
	}else{
		DoubleBlackDeleteStrategy(node->parent, root);
	}
}

static void siblingIsBlackAndMinOneChildIsRed (Node_t* node, Node_t* sibling, Node_t** root){
	SiblingBlackAndChildrenRedCases_t strategy = checkAfterDeletonStrategyForBlackSiblingAndOneRedChild(sibling);

	switch (strategy){
		case LEFT_LEFT:{
			rightRight_leftLeftStrategy(sibling->leftChild, root);
			break;
		}
		case RIGHT_LEFT:{
			rightLeft_leftRightStrategy(sibling, sibling->leftChild, root);
			break;
		}
		case RIGHT_RIGHT:{
			rightRight_leftLeftStrategy(sibling->rightChild, root);
			break;
		}
		case LEFT_RIGHT:{
			rightLeft_leftRightStrategy(sibling, sibling->rightChild, root);
			break;
		}
	}
}

static SiblingBlackAndChildrenRedCases_t checkAfterDeletonStrategyForBlackSiblingAndOneRedChild (Node_t* sibling){
	if (sibling->parent->leftChild == sibling){
		//sibling is left child
		if (sibling->leftChild != NULL && RED == sibling->leftChild->color){
			//left or both are red
			return LEFT_LEFT;
		}else{
			return LEFT_RIGHT;
		}

	}else{
		//sibling is right child
		if (sibling->rightChild != NULL && RED == sibling->rightChild->color){
			//right or both are red
			return RIGHT_RIGHT;
		}else{
			return RIGHT_LEFT;
		}
	}
}
