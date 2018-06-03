#include "types.h"
#include <stdio.h>

#include "redBlackTree.h"
#include "rulesCheckers.h"

int blackNodesToRoot_Max;
int blackNodesToRoot;

int rule4Violations;
int rule5Violations;

#define RULE_1_ROOT_IS_BLACK						1
#define RULE_4_RED_HAS_BLACK_CHILDREN				4
#define RULE_5_NUMBER_OF_BLACK_NODES_TO_LEAF		5

int diveIntoTheTree_Recursive(Node_t* node);
void printOK(int rule);
void printError(int rule, Node_t* node);
int isRootBlack(Node_t* root);
int checkNodeRules(Node_t* node);
int checkNumberOfBlacksToRoot(Node_t* node);
int areRedsChildsBlack(Node_t* redNode);
int isBinaryBranchinchOk(Node_t* node);



int runChecks (Node_t* root, RunChecksPrint_t print){
	int res = TRUE;

	if (NULL == root){
		return TRUE;
	}

	blackNodesToRoot_Max = 0;
	blackNodesToRoot = 0;
	rule4Violations = 0;
	rule5Violations = 0;

	if (FALSE == isRootBlack(root)){
		printError(RULE_1_ROOT_IS_BLACK,root);
		res = FALSE;
	}else if (print == RUN_CHECKS__PRINT){
		printOK(RULE_1_ROOT_IS_BLACK);
	}

	if (FALSE == diveIntoTheTree_Recursive(root)){
		res = FALSE;
	}

	if (rule4Violations == 0 && print == RUN_CHECKS__PRINT){
		printOK(RULE_4_RED_HAS_BLACK_CHILDREN);
	}
	if (rule5Violations == 0 && print == RUN_CHECKS__PRINT){
		printOK(RULE_5_NUMBER_OF_BLACK_NODES_TO_LEAF);
	}

	if(print == RUN_CHECKS__PRINT){
		printf("\n\n");
	}

	return res;
}

int diveIntoTheTree_Recursive(Node_t* node){
	int res = TRUE;
	if (node->color == BLACK){
		blackNodesToRoot++;
	}

	res = checkNodeRules(node);
	if (node->leftChild != NULL && FALSE == diveIntoTheTree_Recursive(node->leftChild)){
		res = FALSE;
	}
	if (node->rightChild != NULL && FALSE == diveIntoTheTree_Recursive(node->rightChild)){
		res = FALSE;
	}

	if (node->color == BLACK){
		blackNodesToRoot--;
	}
	return res;
}

void printOK(int rule){
	printf("%s", KGRN);
	printf("Rule ");
	switch(rule){
		case RULE_1_ROOT_IS_BLACK:{
			printf("ROOT_IS_BLACK");
			break;
		}
		case RULE_4_RED_HAS_BLACK_CHILDREN:{
			printf("RED_HAS_BLACK_CHILDREN");
			break;
		}
		case RULE_5_NUMBER_OF_BLACK_NODES_TO_LEAF:{
			printf("NUMBER_OF_BLACK_NODES_TO_LEAF");
			break;
		}
	}
	printf(" OK\n");

	printf("%s", KWHT);
}

void printError(int rule, Node_t* node){
	printf("%s", KRED);
	printf("Rule ");
	switch(rule){
		case RULE_1_ROOT_IS_BLACK:{
			printf("ROOT_IS_BLACK");
			break;
		}
		case RULE_4_RED_HAS_BLACK_CHILDREN:{
			printf("RED_HAS_BLACK_CHILDREN");
			break;
		}
		case RULE_5_NUMBER_OF_BLACK_NODES_TO_LEAF:{
			printf("NUMBER_OF_BLACK_NODES_TO_LEAF");
			break;
		}
	}
	printf(" FAILED at node: %d\n",(int)node->value);

	printf("%s", KWHT);
}


int isRootBlack(Node_t* root){
	if (root->color == BLACK){
		return TRUE;
	}
	return FALSE;
}

int checkNodeRules(Node_t* node){
	int ret = TRUE;
	if (node->color == RED){
		if (areRedsChildsBlack(node) == FALSE){
			printError(RULE_4_RED_HAS_BLACK_CHILDREN, node);
			ret = FALSE;
		}
	}
	if (FALSE == checkNumberOfBlacksToRoot(node)){
		ret = FALSE;
	}

	return ret;
}

int checkNumberOfBlacksToRoot(Node_t* node){
	int ret = TRUE;
	if (NULL == node->leftChild || NULL == node->rightChild){
		if (blackNodesToRoot_Max == 0){
			blackNodesToRoot_Max = blackNodesToRoot;
		}
		if(blackNodesToRoot != blackNodesToRoot_Max){
			printError(RULE_5_NUMBER_OF_BLACK_NODES_TO_LEAF, node);
			rule5Violations++;
			ret = FALSE;
		}
	}
	return ret;
}

int areRedsChildsBlack(Node_t* redNode){
	if (redNode->leftChild != NULL && RED == redNode->leftChild->color){
		return FALSE;
	}
	if (redNode->rightChild != NULL && RED == redNode->rightChild->color){
		return FALSE;
	}
	return TRUE;
}

int isBinaryBranchinchOk(Node_t* node){
	if (node->leftChild->value < node->value && node->rightChild->value > node->value){
		return TRUE;
	}
	return FALSE;
}

