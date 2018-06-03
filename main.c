#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "redBlackTree.h"
#include "map.h"
#include "rulesCheckers.h"
#include "test.h"

#define MEM_SPACE_LEN 512

char memSpace[MEM_SPACE_LEN];

void* AllocateObject(map_t* map, void* addr, char* objectToAlloc, int len);
void printMemory();

int main (void){

	printf(CLEAR_SCREEN);

	int testRes = runTests();

	printf("\n");
	printf ("****************************************\n");
	if (testRes == TRUE){
		printf("%s", KGRN);
		printf("Self Tests PASSED\n");
		printf("%s", KWHT);
	}else{
		printf("%s", KRED);
		printf("Self Tests FAILED\n");
		printf("%s", KWHT);
		return 0;
	}
	printf ("****************************************\n");
	printf("\n");
	map_t* map = calloc(1,sizeof(map_t*));
	mymap_init(map);

	printf("Map first objects:\n\n");
	void* ObjA = AllocateObject(map, &memSpace[0], "#AAAAAA" ,sizeof( "#AAAAAA" ));
	void* ObjB = AllocateObject(map, &memSpace[0], "#BBBBBB" ,sizeof( "#BBBBBB" ));
	void* ObjC = AllocateObject(map, &memSpace[0], "#CC" ,sizeof( "#CC" ));
	void* ObjD = AllocateObject(map, &memSpace[0], "#DDDDDDDDDDDDDD" ,sizeof( "#DDDDDDDDDDDDDD" ));
	void* ObjE = AllocateObject(map, &memSpace[0], "#E" ,sizeof( "#E" ));
	void* ObjF = AllocateObject(map, &memSpace[0], "#FFFFFFFF" ,sizeof( "#FFFFFFFF" ));
	void* ObjG = AllocateObject(map, &memSpace[0], "#GGGG" ,sizeof( "#GGGG" ));
	void* ObjH = AllocateObject(map, &memSpace[0], "#HHHHHHHHHHHHHHHHHHHHHH" ,sizeof( "#HHHHHHHHHHHHHHHHHHHHHH" ));
	void* ObjI = AllocateObject(map, &memSpace[0], "#III" ,sizeof( "#III" ));
	void* ObjJ = AllocateObject(map, &memSpace[0], "#JJJJJJ" ,sizeof( "#JJJJJJ" ));
	void* ObjK = AllocateObject(map, &memSpace[0], "#KKKKKKKKKK" ,sizeof( "#KKKKKKKKKK" ));
	void* ObjL = AllocateObject(map, &memSpace[0], "#LLLLL" ,sizeof( "#LLLLL" ));
	void* ObjM = AllocateObject(map, &memSpace[0], "#MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" ,sizeof( "#MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM"));
	void* ObjN = AllocateObject(map, &memSpace[0], "#NNNNNNNNNN" ,sizeof( "#NNNNNNNNNN" ));
	void* ObjO = AllocateObject(map, &memSpace[0], "#OOO" ,sizeof( "#OOO" ));
	void* ObjP = AllocateObject(map, &memSpace[0], "#PPPPPPPPPPPPPPPPP" ,sizeof( "#PPPPPPPPPPPPPPPPP"));

	void* ObjR = AllocateObject(map, ((char*)ObjP) + 30, "#R" ,sizeof( "#R" ));
	void* ObjS = AllocateObject(map, ((char*)ObjP) + 30, "#SSSSSSSSSSSSS" ,sizeof( "#SSSSSSSSSSSSS" ));
	void* ObjT = AllocateObject(map, ((char*)ObjP) + 30, "#TTTT" ,sizeof( "#TTTT" ));
	void* ObjU = AllocateObject(map, ((char*)ObjP) + 30, "#UUUUUUU" ,sizeof( "#UUUUUUU" ));
	void* ObjW = AllocateObject(map, ((char*)ObjP) + 30, "#WWWWWWWWW" ,sizeof( "#WWWWWWWWW" ));
	printf("\n");
	printf("Memory map:\n");
	printMemory();
	printf("\n");
	printf("\n");
	printf("Memory tree:\n");
	mymap_dump(map);
	printf("\n");
	printf("\n");

	printf("Unmap some of objects:\n\n");
	mymap_munmap(map, ObjL);
	mymap_munmap(map, ObjG);
	mymap_munmap(map, ObjC);
	mymap_munmap(map, ObjO);
	mymap_munmap(map, ObjU);
	mymap_munmap(map, ObjA);
	mymap_munmap(map, ObjE);
	mymap_munmap(map, ObjM);

	printf("\n");
	printf("Memory map:\n");
	printMemory();
	printf("\n");
	printf("\n");
	printf("Memory tree:\n");
	mymap_dump(map);
	printf("\n");
	printf("\n");

	printf("Map new obects in free space:\n\n");
	AllocateObject(map, &memSpace[0], "#1" ,sizeof( "#1" ));
	AllocateObject(map, &memSpace[0], "#22" ,sizeof( "#22" ));
	AllocateObject(map, &memSpace[0], "#333" ,sizeof( "#333" ));
	AllocateObject(map, &memSpace[0], "#4444" ,sizeof( "#4444" ));
	AllocateObject(map, &memSpace[0], "#55555" ,sizeof( "#55555" ));
	AllocateObject(map, &memSpace[0], "#666666" ,sizeof( "#666666" ));
	AllocateObject(map, &memSpace[0], "#7777777" ,sizeof( "#7777777" ));
	AllocateObject(map, &memSpace[0], "#88888888" ,sizeof( "#88888888" ));
	AllocateObject(map, &memSpace[0], "#999999999" ,sizeof( "#999999999" ));

	printf("\n");
	printf("Memory map:\n");
	printMemory();
	printf("\n");
	printf("\n");
	printf("Memory tree:\n");
	mymap_dump(map);
	printf("\n");
	printf("\n");

	printf("Unmap all Letter objects:\n\n");
	mymap_munmap(map, ObjB);
	mymap_munmap(map, ObjD);
	mymap_munmap(map, ObjF);
	mymap_munmap(map, ObjT);
	mymap_munmap(map, ObjW);
	mymap_munmap(map, ObjS);
	mymap_munmap(map, ObjR);
	mymap_munmap(map, ObjN);
	mymap_munmap(map, ObjK);
	mymap_munmap(map, ObjJ);
	mymap_munmap(map, ObjH);
	mymap_munmap(map, ObjI);
	mymap_munmap(map, ObjP);

	printf("\n");
	printf("Memory map:\n");
	printMemory();
	printf("\n");
	printf("\n");
	printf("Memory tree:\n");
	mymap_dump(map);
	printf("\n");
	printf("\n");

	printf("Unmap rest of objects starting with root...\n");
	while(*map != NULL){
		mymap_munmap(map, (void*)(*map)->value);
	}

	free(map);
	printf("end\n");
	return 0;
}


void* AllocateObject(map_t* map, void* addr, char* objectToAlloc, int len){
	void* objectPtr;

	printf("Mapping Object %s ",objectToAlloc);
	/*cut out \0*/
	len -= 1;
	objectPtr = mymap_mmap(map, addr, len ,0 ,objectToAlloc);

	if (NULL == objectPtr){
		return NULL;
	}
	printf(" mapped to 0x%x \n",(int)objectPtr );

	return objectPtr;
}

void printMemory(){
	for (int i = 0 ; i < MEM_SPACE_LEN ; i++){
		if (0 == i%32){
			printf("\n");
		}
		if (memSpace[i] != 0){
			printf("%c",memSpace[i]);
		}else{
			printf("-");
		}
	}
}

