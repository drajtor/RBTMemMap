#include <stdio.h>
#include "types.h"
#include "redBlackTree.h"
#include "map.h"

#define DISPLAY_OFFSETT 18
#define LINE_LEN 8

void printHorizontal_Recursive(Node_t* node, int offset);

void printTree(Node_t* root){
	printHorizontal_Recursive(root,0);
}

void printHorizontal_Recursive(Node_t* node, int offset)
{
	int currOffset;// = offset;
	if (node == NULL){
		return;
	}

    offset += DISPLAY_OFFSETT;
    currOffset = offset;
    printHorizontal_Recursive(node->rightChild, offset);
    printf("\n");

    for (int i = DISPLAY_OFFSETT; i < currOffset; i++)
        printf(" ");

    if (NULL == node->parent){
    	printf("-");
    }
    else if (node->parent->leftChild == node){
    	printf("/\\");
    }else{
    	printf("\\/");
    }

    for (int i = 0; i < LINE_LEN; i++)
		printf("-");

	if (node->color == RED){
		printf("%s", KRED);
	}
	MapNode_t* mapNode = (MapNode_t*)node->treeObject;
    printf("%x(%d)\n", (int)node->value, mapNode->size);
    printf("%s", KWHT);

    printHorizontal_Recursive(node->leftChild, offset);
}
