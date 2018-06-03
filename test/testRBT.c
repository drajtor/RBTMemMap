#include <stdio.h>
#include "testRBT.h"
#include "types.h"
#include "redBlackTree.h"
#include "test.h"
#include "rulesCheckers.h"
#include "printTree.h"

testResult_t deletionTest_NodeOrChildIsRed();
testResult_t deletionTest_DoubleBlack_SiblingIsRed();
testResult_t deletionTest_DeleteRoot();
testResult_t deletionTest_DoubleBlack_SiblingAndItsChildrenAreBlack();
testResult_t deletionTest_DoubleBlack_SiblingBlackOneChildRed();

testResult_t deletionTest(){
	testResult_t res = TEST_PASS;

	if (TEST_FAIL == deletionTest_DeleteRoot()){
		printf("deletionTest_DeleteRoot FAILED\n");
		res = TEST_FAIL;
	}else{
#ifdef DELETION_TEST_DEBUG
		printf("deletionTest_DeleteRoot PASSED\n");
#endif
	}

	if (TEST_FAIL == deletionTest_NodeOrChildIsRed()){
		printf("deletionTest_NodeOrChildIsRed FAILED\n");
		res = TEST_FAIL;
	}else{
#ifdef DELETION_TEST_DEBUG
		printf("deletionTest_NodeOrChildIsRed PASSED\n");
#endif
	}

	if (TEST_FAIL == deletionTest_DoubleBlack_SiblingIsRed()){
		printf("deletionTest_DoubleBlack_SiblingIsRed FAILED\n");
		res = TEST_FAIL;
	}else{
#ifdef DELETION_TEST_DEBUG
		printf("deletionTest_DoubleBlack_SiblingIsRed PASSED\n");
#endif
	}

	if (TEST_FAIL == deletionTest_DoubleBlack_SiblingAndItsChildrenAreBlack()){
		printf("deletionTest_DoubleBlack_SiblingAndItsChildrenAreBlack FAILED\n");
		res = TEST_FAIL;
	}else{
#ifdef DELETION_TEST_DEBUG
		printf("deletionTest_DoubleBlack_SiblingAndItsChildrenAreBlack PASSED\n");
#endif
	}

	if (TEST_FAIL == deletionTest_DoubleBlack_SiblingBlackOneChildRed()){
		printf("deletionTest_DoubleBlack_SiblingBlackOneChildRed FAILED\n");
		res = TEST_FAIL;
	}else{
#ifdef DELETION_TEST_DEBUG
		printf("deletionTest_DoubleBlack_SiblingBlackOneChildRed PASSED\n");
#endif
	}

	return res;
}

int verifyTest (Node_t* root){

#ifdef DELETION_TEST_DEBUG
	int res = runChecks(root, RUN_CHECKS__PRINT);
#else
	int res = runChecks(root, RUN_CHECKS__DONT_PRINT);
#endif
	if (res == FALSE){
		printTree(root);
	}
	return res;
}

testResult_t deletionTest_DoubleBlack_SiblingBlackOneChildRed(){
	int res = TRUE;
	Node_t** rootNodeDeletionTest;

	rootNodeDeletionTest = initTreeRoot();

	/*	Left Right Strategy, checking Right Right by the way.*/
	addNode(20,rootNodeDeletionTest);
	addNode(50,rootNodeDeletionTest);
	addNode(10,rootNodeDeletionTest);
	addNode(30,rootNodeDeletionTest);
	addNode(33,rootNodeDeletionTest);
	addNode(60,rootNodeDeletionTest);
	addNode(53,rootNodeDeletionTest);
	addNode(59,rootNodeDeletionTest);
	deleteNode(50,rootNodeDeletionTest);

	if (FALSE == verifyTest(*rootNodeDeletionTest)){
		res = FALSE;
	}

	addNode(59,rootNodeDeletionTest);
	addNode(55,rootNodeDeletionTest);
	deleteNode(60,rootNodeDeletionTest);

	if (FALSE == verifyTest(*rootNodeDeletionTest)){
		res = FALSE;
	}

	return res;
}

testResult_t deletionTest_DoubleBlack_SiblingAndItsChildrenAreBlack(){
	int res = TRUE;
	Node_t** rootNodeDeletionTest;

	rootNodeDeletionTest = initTreeRoot();

	/*	Node is on Right*/
	addNode(20,rootNodeDeletionTest);
	addNode(50,rootNodeDeletionTest);
	addNode(10,rootNodeDeletionTest);
	addNode(30,rootNodeDeletionTest);
	addNode(33,rootNodeDeletionTest);
	addNode(60,rootNodeDeletionTest);
	addNode(53,rootNodeDeletionTest);
	deleteNode(50,rootNodeDeletionTest);
	deleteNode(60,rootNodeDeletionTest);
	deleteNode(53,rootNodeDeletionTest);
	if (FALSE == verifyTest(*rootNodeDeletionTest)){
		res = FALSE;
	}

	/*	Node is on Left*/
	addNode(50,rootNodeDeletionTest);
	addNode(44,rootNodeDeletionTest);
	addNode(26,rootNodeDeletionTest);
	addNode(38,rootNodeDeletionTest);
	addNode(45,rootNodeDeletionTest);
	deleteNode(45,rootNodeDeletionTest);
	deleteNode(38,rootNodeDeletionTest);
	if (FALSE == verifyTest(*rootNodeDeletionTest)){
		res = FALSE;
	}

	return res;
}


testResult_t deletionTest_DoubleBlack_SiblingIsRed(){
	int res = TRUE;
	Node_t** rootNodeDeletionTest;

	rootNodeDeletionTest = initTreeRoot();

	/*	Red is on right*/
	addNode(20,rootNodeDeletionTest);
	addNode(50,rootNodeDeletionTest);
	addNode(10,rootNodeDeletionTest);
	addNode(30,rootNodeDeletionTest);
	addNode(33,rootNodeDeletionTest);
	addNode(60,rootNodeDeletionTest);
	addNode(53,rootNodeDeletionTest);
	deleteNode(10,rootNodeDeletionTest);
	if (FALSE == verifyTest(*rootNodeDeletionTest)){
		res = FALSE;
	}

	/*	Red is on left*/
	addNode(47,rootNodeDeletionTest);
	addNode(53,rootNodeDeletionTest);
	addNode(17,rootNodeDeletionTest);
	addNode(43,rootNodeDeletionTest);
	addNode(35,rootNodeDeletionTest);
	addNode(22,rootNodeDeletionTest);
	deleteNode(35,rootNodeDeletionTest);
	deleteNode(43,rootNodeDeletionTest);

	if (FALSE == verifyTest(*rootNodeDeletionTest)){
		res = FALSE;
	}

	deleteNode(33,rootNodeDeletionTest);
	deleteNode(22,rootNodeDeletionTest);
	deleteNode(50,rootNodeDeletionTest);
	deleteNode(60,rootNodeDeletionTest);
	deleteNode(20,rootNodeDeletionTest);
	deleteNode(53,rootNodeDeletionTest);
	deleteNode(47,rootNodeDeletionTest);
	deleteNode(30,rootNodeDeletionTest);
	deleteNode(17,rootNodeDeletionTest);

	return res;
}


testResult_t deletionTest_NodeOrChildIsRed(){
	int res = TRUE;
	Node_t** rootNodeDeletionTest;

	rootNodeDeletionTest = initTreeRoot();

	/*Node is Red, Child is Black*/
	addNode(20,rootNodeDeletionTest);
	addNode(50,rootNodeDeletionTest);
	addNode(10,rootNodeDeletionTest);
	addNode(30,rootNodeDeletionTest);
	deleteNode(30,rootNodeDeletionTest);

	if (FALSE == verifyTest(*rootNodeDeletionTest)){
		res = FALSE;
	}

	/*Node is Black, Child is Red*/
	addNode(30,rootNodeDeletionTest);
	deleteNode(50,rootNodeDeletionTest);

	if (FALSE == verifyTest(*rootNodeDeletionTest)){
		res = FALSE;
	}

	deleteNode(30,rootNodeDeletionTest);
	deleteNode(10,rootNodeDeletionTest);
	deleteNode(20,rootNodeDeletionTest);

	return res;
}

testResult_t deletionTest_DeleteRoot(){
	int res = TRUE;
	Node_t** rootNodeDeletionTest;

	rootNodeDeletionTest = initTreeRoot();

	/*Delete From Empty Tree*/
	deleteNode(20,rootNodeDeletionTest);

	/*Delete when root is the only node*/
	addNode(20,rootNodeDeletionTest);
	deleteNode(20,rootNodeDeletionTest);

	/*Delete root that has 2 children */
	addNode(20,rootNodeDeletionTest);
	addNode(10,rootNodeDeletionTest);
	addNode(30,rootNodeDeletionTest);
	deleteNode(20,rootNodeDeletionTest);

	/*Delete root that has min 2 children */
	addNode(50,rootNodeDeletionTest);
	addNode(55,rootNodeDeletionTest);
	addNode(32,rootNodeDeletionTest);
	addNode(9,rootNodeDeletionTest);
	addNode(11,rootNodeDeletionTest);
	deleteNode(30,rootNodeDeletionTest);

	if (FALSE == verifyTest(*rootNodeDeletionTest)){
		res = FALSE;
	}
/*Delete all by root to double test*/
	deleteNode(30,rootNodeDeletionTest);
	deleteNode(11,rootNodeDeletionTest);
	deleteNode(10,rootNodeDeletionTest);
	deleteNode(50,rootNodeDeletionTest);
	deleteNode(32,rootNodeDeletionTest);
	deleteNode(55,rootNodeDeletionTest);
	deleteNode(9,rootNodeDeletionTest);

	return res;
}
