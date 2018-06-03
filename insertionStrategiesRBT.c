#include "insertionStrategiesRBT.h"

#include "types.h"
#include "redBlackTree.h"
#include "relations.h"

typedef enum {
	SHAPE_LINE		= 0,
	SHAPE_TRIANGLE	= 1
}shape_t;

shape_t getShape(Node_t* node);
void rotateParentUncleBlackTriangle(Node_t* node, Node_t** root);
void rotateParentUncleBlackLine(Node_t* node, Node_t** root);
Strategy_t checkStrategies (Node_t* node);
void RedUncleRecolor (Node_t* node, Node_t** root);

void fixNodeToFitRBTRules(Node_t* node, Node_t** root){
	Strategy_t strategy = checkStrategies (node);

#ifdef DEBUG_STRATEGIES
			printf("Node %d: ",node->value);
#endif

	switch (strategy){
		case STRAT_CASE_ROOT:{
			node->color = BLACK;
#ifdef DEBUG_STRATEGIES
			printf("STRAT_CASE_ROOT \n");
#endif
			break;
		}
		case STRAT_CASE_UNCLE_RED:{
#ifdef DEBUG_STRATEGIES
			printf("STRAT_CASE_UNCLE_RED \n");
#endif
			RedUncleRecolor(node, root);
			break;
		}
		case STRAT_CASE_UNCLE_BLACK_TRIANGLE:{
#ifdef DEBUG_STRATEGIES
			printf("STRAT_CASE_UNCLE_BLACK_TRIANGLE \n");
#endif
			rotateParentUncleBlackTriangle(node, root);
			break;
		}
		case STRAT_CASE_UNCLE_BLACK_LINE:{
#ifdef DEBUG_STRATEGIES
			printf("STRAT_CASE_UNCLE_BLACK_LINE \n");
#endif
			rotateParentUncleBlackLine(node, root);
			break;
		}
		case STRAT_PARENT_IS_ROOT:{
#ifdef DEBUG_STRATEGIES
			printf("STRAT_PARENT_IS_ROOT \n");
#endif
			break;
		}
		default:{
#ifdef DEBUG_STRATEGIES
			printf("GET UNCLE ERROR!!!! \n");
#endif
		}
	}
}

void rotateParentUncleBlackTriangle(Node_t* node, Node_t** root){
	Node_t* grandparent = node->parent->parent;
	Node_t* parent = node->parent;

	if (parent == grandparent->rightChild){
		rotate(parent,RIGHT, root);
		parent = node->parent;
		rotate(parent,LEFT, root);
	}else{
		rotate(parent,LEFT, root);
		parent = node->parent;
		rotate(parent,RIGHT, root);
	}
	node->color = BLACK;
	grandparent->color = RED;
}

void rotateParentUncleBlackLine(Node_t* node, Node_t** root){
	Node_t* grandparent = node->parent->parent;
	Node_t* parent = node->parent;

	if (parent == grandparent->rightChild){
		rotate(grandparent,LEFT, root);
	}else{
		rotate(grandparent,RIGHT, root);
	}
	parent->color = BLACK;
	grandparent->color = RED;
}

Strategy_t checkStrategies (Node_t* node){
	if (NULL == node){
		return STRAT_ERROR;
	}

	if (NULL == node->parent){
		return STRAT_CASE_ROOT;
	}
	Node_t* grandparent = node->parent->parent;
	if (NULL == grandparent){
		return STRAT_PARENT_IS_ROOT;
	}
	Node_t* uncle = getUncle(node);

	if (uncle != NULL && RED == uncle->color){
		return STRAT_CASE_UNCLE_RED;
	}else if (getShape(node) == SHAPE_LINE){
		return STRAT_CASE_UNCLE_BLACK_LINE;
	}else if (getShape(node) == SHAPE_TRIANGLE){
		return STRAT_CASE_UNCLE_BLACK_TRIANGLE;
	}else{
		return STRAT_ERROR;
	}
}

void RedUncleRecolor (Node_t* node, Node_t** root){
	Node_t* grandparent = node->parent->parent;
	Node_t* parent = node->parent;
	Node_t* uncle = getUncle(node);

	parent->color = BLACK;
	uncle->color = BLACK;
	grandparent->color = RED;

	fixNodeToFitRBTRules(grandparent, root);
}

shape_t getShape(Node_t* node){
	Node_t* grandparent = node->parent->parent;
	Node_t* parent = node->parent;

	if (parent == grandparent->leftChild && node == parent->leftChild){
		return SHAPE_LINE;
	}else if (parent == grandparent->rightChild && node == parent->rightChild){
		return SHAPE_LINE;
	}
	return SHAPE_TRIANGLE;
}
