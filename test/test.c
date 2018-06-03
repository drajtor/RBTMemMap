#include <stdio.h>

#include "types.h"
#include "redBlackTree.h"
#include "rulesCheckers.h"
#include "test.h"

#include "../insertionStrategiesRBT.h"
#include "testRBT.h"
#include "testMap.h"

#ifdef RBT_INSERTION_DEBUG
void generateInsertionStrategiesTestTree(Node_t* root){
		addNodeColor (6,BLACK,root);
		addNodeColor (7,RED,root);
		addNodeColor (8,BLACK,root);
		addNodeColor (3,BLACK,root);
		addNodeColor (4,RED,root);
		addNodeColor (11,BLACK,root);
		addNodeColor (17,RED,root);
		addNodeColor (16,BLACK,root);
		addNodeColor (12,RED,root);
		addNodeColor (9,RED,root);
}

testResult_t testStrategiesCheck(Node_t* root){
	if (STRAT_CASE_ROOT != checkStrategies(root)){
		printf("STRAT_CASE_ROOT FAILED\n");
		return TEST_FAIL;
	}

	if (STRAT_PARENT_IS_ROOT != checkStrategies(root->rightChild)){
		printf("STRAT_NO_UNCLE 1 FAILED\n");
		return TEST_FAIL;
	}
	if (STRAT_PARENT_IS_ROOT != checkStrategies(root->leftChild)){
		printf("STRAT_NO_UNCLE 2 FAILED\n");
		return TEST_FAIL;
	}

	if (STRAT_CASE_UNCLE_BLACK_LINE != checkStrategies(root->leftChild->leftChild)){
		printf("STRAT_CASE_UNCLE_BLACK_LINE FAILED\n");
		return TEST_FAIL;
	}

	if (STRAT_CASE_UNCLE_BLACK_TRIANGLE != checkStrategies(root->leftChild->rightChild)){
		printf("STRAT_CASE_UNCLE_BLACK_TRIANGLE FAILED\n");
		return TEST_FAIL;
	}
	if (STRAT_ERROR != checkStrategies(root->rightChild->leftChild->leftChild)){
		printf("STRAT_ERROR FAILED\n");
		return TEST_FAIL;
	}

	if (STRAT_CASE_UNCLE_RED != checkStrategies(root->leftChild->leftChild->rightChild)){
		printf("STRAT_CASE_UNCLE_RED FAILED\n");
		return TEST_FAIL;
	}

	return TEST_PASS;
}

testResult_t testStrategies(Node_t** root){
	Node_t* node;

	node = (*root)->rightChild->leftChild;
	fixNodeToFitRBTRules(node, root);
	if (*root != node && (*root)->color != BLACK){
		printf("Black uncle triangle right strategy fix FAILED");
		return TEST_FAIL;
	}
	return TEST_PASS;
}

testResult_t testNodeDuplicates(Node_t* node, value_t value){
	if (NULL == node){
		return TEST_PASS;
	}

	if (value < node->value){
		return testNodeDuplicates(node->leftChild, node->value);
	}else if (value > node->value){
		return testNodeDuplicates(node->rightChild, node->value);
	}else{
		return TEST_FAIL;
	}
	return TEST_PASS;
}
#endif

int runTests(){
#ifdef RBT_INSERTION_DEBUG
	Node_t** root = calloc (1, sizeof(Node_t*));
	*root = addNode(8,root);

	generateInsertionStrategiesTestTree(*root);

	printf("\n");
	printf ("****************************************\n");

	if (TEST_FAIL == testStrategiesCheck(*root)){
		printf("testStrategiesCheck FAILED\n");
		return FALSE;
	}else{
		printf("testStrategiesCheck PASSED\n");
	}

	if (TEST_FAIL == testNodeDuplicates(*root,16) && TEST_PASS == testNodeDuplicates(*root,20)){
		printf("testNodeDuplicates FAILED\n");
		return FALSE;
	}else{
		printf("testNodeDuplicates PASSED\n");
	}


	if (TEST_FAIL == testStrategies(root)){
		printf("testStrategies FAILED\n");
		return FALSE;
	}else{
		printf("testStrategies PASSED\n");
	}
//	printList(*root);
//	deleteInsertionStrategiesTestTree(root);

#endif

	if (TEST_FAIL == deletionTest()){
		printf("DeletionTest FAILED\n");
		return FALSE;
	}else{
		printf("DeletionTest PASSED\n");
	}

	if (TEST_FAIL == mapTest()){
		printf("MapTest FAILED\n");
		return FALSE;
	}else{
		printf("MapTest PASSED\n");
	}

	return TRUE;
}


