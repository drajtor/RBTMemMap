#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "types.h"
#include "redBlackTree.h"
#include "relations.h"
#include "printTree.h"

Node_t* getNodeWithNearestToDesiredAddress (value_t address, Node_t** root);
value_t getAllocableAddress (value_t address, Node_t** root, unsigned int size);
Node_t* getRightMemoryNeighbour (Node_t* node);
value_t getAddressAvailable (value_t address, Node_t* parent, unsigned int size, Node_t** root);
Node_t* getInorderAncestor(Node_t* node);
int isSpaceAvailable (value_t address, unsigned int size, Node_t* rightNeighbourInMemory);
static inline value_t getNextAddressAfterObjectInNode (Node_t* node);
unsigned int getObjectSizeFromNode (Node_t* node);
unsigned int getObjectSize (void* vaddr, Node_t** root);

int mymap_init (map_t* map){
//	map = initTreeRoot();
	if (NULL == map){
		printf("Out of memory\n");
		return FALSE;
	}
	return TRUE;
}

void* mymap_mmap (map_t* map, void* vaddr, unsigned int size, unsigned int flags, void* o){
	value_t addressToMap;

	//TODO process flags

	addressToMap = getAllocableAddress((value_t)vaddr, map, size);
	if (addressToMap < (value_t)vaddr){
		printf("getAllocableAddress error\n");
		return NULL;
	}
	Node_t* node = addNode(addressToMap, map);
	if (NULL == node){
		printf("Alloc Error\n");
		return NULL;
	}

	MapNode_t* mapNode = calloc(1,sizeof(MapNode_t));
	if (NULL == mapNode){
		printf("Out of Memory\n");
		return NULL;
	}

	mapNode->size = size;
	node->treeObject = mapNode;
	memcpy((void*)addressToMap , o, size);

	return (void*)addressToMap;
}


value_t getAllocableAddress (value_t address, Node_t** root, unsigned int size){
	Node_t* node;

	node = getNodeWithNearestToDesiredAddress (address, root);
	if (NULL == node){
		/* Map is empty */
		return address;
	}
	return getAddressAvailable(address, node, size, root);
}

Node_t* getNodeWithNearestToDesiredAddress (value_t address, Node_t** root){
	Node_t* node = *root;
	Node_t** nextNode = root;

	while (*nextNode != NULL){
		node = *nextNode;
		if (node->value == address){
			break;
		}
		nextNode = getNextBinaryBranchNode (node,address);
	}
	return node;
}

value_t getAddressAvailable (value_t address, Node_t* node, unsigned int size, Node_t** root){
	Node_t* rightNeighbourInMemory = NULL;

	if (address != node->value){
		/*Check if address available*/
		if (address > node->value){
			rightNeighbourInMemory = getRightMemoryNeighbour(node);
			if (NULL != rightNeighbourInMemory){
				node = rightNeighbourInMemory;
			}
			else{
				/*No right nieghbour, allocate at desired address*/
				return address;
			}
		}
		if (TRUE == isSpaceAvailable(address, size, node)){
			return address;
		}
		/*	Align to existing address*/
		address = node->value;
	}

	value_t newAddress = address;

	do{
		newAddress = getNextAddressAfterObjectInNode(node);
		rightNeighbourInMemory = getRightMemoryNeighbour(node);
		if (NULL == rightNeighbourInMemory){
			/*no right neighbour, free to write*/
			break;
		}
		node = rightNeighbourInMemory;
	}while(FALSE == isSpaceAvailable(newAddress, size, rightNeighbourInMemory));

	return newAddress;
}

static inline value_t getNextAddressAfterObjectInNode (Node_t* node){
	return node->value + getObjectSizeFromNode(node);
}

unsigned int getObjectSizeFromNode (Node_t* node){
	MapNode_t* mapNode = (MapNode_t*) node->treeObject;
	return mapNode->size;
}

int isSpaceAvailable (value_t address, unsigned int size, Node_t* rightNeighbourInMemory){
	if ((address + size) <= rightNeighbourInMemory->value){
		return TRUE;
	}
	return FALSE;
}

Node_t* getRightMemoryNeighbour (Node_t* node){
	Node_t* rightNeighbourInMemory;

	rightNeighbourInMemory = getInorderSuccessor(node);

	if (rightNeighbourInMemory != NULL){
		return rightNeighbourInMemory ;
	}
	rightNeighbourInMemory = getInorderAncestor(node);
	return rightNeighbourInMemory;
}


void mymap_munmap(map_t *map, void* vaddr){

	if (NULL == vaddr || NULL == map){
		return;
	}

	Node_t* node = getNode((value_t)vaddr, map);
	if (NULL == node){
		return;
	}

	unsigned int size =  getObjectSize(vaddr, map);
	memset(vaddr,0,size);

	MapNode_t* mapNode = node->treeObject;
	free (mapNode);
	mapNode = NULL;
	deleteNode((value_t)vaddr, map);
}

unsigned int getObjectSize (void* vaddr, Node_t** root){
	Node_t* node;
	node = getNode((value_t)vaddr, root);
	MapNode_t* mapNode = node->treeObject;

	return mapNode->size;
}

int mymap_dump(map_t* map){
	printTree(*map);
	return 0;
}

