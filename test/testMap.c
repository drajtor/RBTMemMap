#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "testMap.h"
#include "types.h"
#include "map.h"
#include "printTree.h"

testResult_t mapTest_addAndDeleteRoot();
testResult_t mapTest_addAndDeleteRootAndChildren();
testResult_t mapTest_customTest();

char memSpaceTest[2048];

testResult_t mapTest(){
	testResult_t res = TEST_PASS;

	if (TEST_FAIL == mapTest_addAndDeleteRoot()){
		printf("mapTest_addAndDeleteRoot FAILED\n");
		res = TEST_FAIL;
	}else{
#ifdef MAP_TEST_DEBUG
		printf("mapTest_addAndDeleteRoot PASSED\n");
#endif
	}
	if (TEST_FAIL == mapTest_addAndDeleteRootAndChildren()){
		printf("mapTest_addAndDeleteRootChildren FAILED\n");
		res = TEST_FAIL;
	}else{
#ifdef MAP_TEST_DEBUG
		printf("mapTest_addAndDeleteRootChildren PASSED\n");
#endif
	}
	if (TEST_FAIL == mapTest_customTest()){
		printf("mapTest_addAndDeleteRootChildren FAILED\n");
		res = TEST_FAIL;
	}else{
#ifdef MAP_TEST_DEBUG
		printf("mapTest_addAndDeleteRootChildren PASSED\n");
#endif
	}

	return res;
}

testResult_t mapTest_addAndDeleteRoot(){
	int res = TRUE;

	map_t* map = calloc(1,sizeof(map_t));
//	map_t* map;
	mymap_init(map);

	char stringA [6] = "AAAAA";
	char stringCleared [6] = "\0\0\0\0\0";

	char* ptrA = mymap_mmap(map, &memSpaceTest[0], sizeof(stringA),0,stringA);
	if (strcmp(stringA,memSpaceTest) != 0){
		res = FALSE;
	}
	if (ptrA != &memSpaceTest[0]){
		res = FALSE;
	}
	mymap_munmap(map, ptrA );
	if (strcmp(stringCleared,memSpaceTest) != 0){
		res = FALSE;
	}

	return res;
}

testResult_t mapTest_addAndDeleteRootAndChildren(){
	int res = TRUE;

	map_t* map = calloc(1,sizeof(map_t));
	mymap_init(map);

	char stringA [6] = "AAAAA";
	char stringB [6] = "BBBBB";
	char stringC [6] = "CCCCC";

	char* ptrA = mymap_mmap(map, &memSpaceTest[0], sizeof(stringA),0,stringA);
	char* ptrB = mymap_mmap(map, &memSpaceTest[0], sizeof(stringB),0,stringB);
	char* ptrC = mymap_mmap(map, &memSpaceTest[0], sizeof(stringC),0,stringC);

//	printTree(*map);
//	printf("\n");

	mymap_munmap(map, ptrB );
	mymap_munmap(map, ptrC );
	mymap_munmap(map, ptrA );

	for (int i = 0 ; i < 3*sizeof(stringA) ; i++){
		if (memSpaceTest[i] != 0){
			res = FALSE;
			break;
		}
	}

	return res;
}

testResult_t mapTest_customTest(){
	int res = TRUE;

	map_t* map = calloc(1,sizeof(map_t));
	mymap_init(map);

	char stringA [6] = "AAAAAA";
	char stringB [6] = "BBBBBB";
	char stringC [6] = "CCCCCC";
	char stringD [6] = "DDDDDD";
	char stringE [6] = "EEEEEE";
	char stringF [6] = "FFFFFF";

	char stringG [3] = "GGG";

	char stringH [1] = "H";
	char stringI [2] = "II";
	char stringJ [5] = "JJJJJ";

	char* ptrA = mymap_mmap(map, &memSpaceTest[0], sizeof(stringA),0,stringA);
	char* ptrB = mymap_mmap(map, &memSpaceTest[0], sizeof(stringB),0,stringB);
	char* ptrC = mymap_mmap(map, &memSpaceTest[0], sizeof(stringC),0,stringC);
	char* ptrD = mymap_mmap(map, &memSpaceTest[0], sizeof(stringD),0,stringD);
	char* ptrE = mymap_mmap(map, &memSpaceTest[0], sizeof(stringE),0,stringE);
	char* ptrF = mymap_mmap(map, &memSpaceTest[0], sizeof(stringF),0,stringF);

	mymap_munmap(map, ptrC );
	char* ptrG = mymap_mmap(map, &memSpaceTest[0], sizeof(stringG),0,stringG);
	ptrC = mymap_mmap(map, &memSpaceTest[0], sizeof(stringC),0,stringC);

	mymap_munmap(map, ptrB );
	mymap_munmap(map, ptrG );
	ptrG = mymap_mmap(map, &memSpaceTest[0], sizeof(stringG),0,stringG);
	ptrB = mymap_mmap(map, &memSpaceTest[0], sizeof(stringB),0,stringB);

	mymap_munmap(map, ptrA );
	mymap_munmap(map, ptrC );
	mymap_munmap(map, ptrF );


	char* ptrH = mymap_mmap(map, &memSpaceTest[0], sizeof(stringH),0,stringH);
	ptrC = mymap_mmap(map, &memSpaceTest[0], sizeof(stringC),0,stringC);


	char* ptrI = mymap_mmap(map, &memSpaceTest[0], sizeof(stringI),0,stringI);
	char* ptrJ = mymap_mmap(map, &memSpaceTest[0], sizeof(stringJ),0,stringJ);

	if (strcmp("HII",&memSpaceTest[0]) != 0){
		res = FALSE;
	}
	if (strcmp("GGGBBBBBB",&memSpaceTest[6]) != 0){
		res = FALSE;
	}
	if (strcmp("DDDDDDEEEEEECCCCCCJJJJJ",&memSpaceTest[18]) != 0){
		res = FALSE;
	}


	mymap_munmap(map, ptrD );
	mymap_munmap(map, ptrE );
	mymap_munmap(map, ptrI );
	mymap_munmap(map, ptrJ );
	mymap_munmap(map, ptrH );

	return res;
}



