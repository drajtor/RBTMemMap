#ifndef MAP_H_
#define MAP_H_

#include "redBlackTree.h"

typedef  Node_t* map_t;

typedef struct{
	//TODO remove if not needed
//	void* obejct;
	int size;
}MapNode_t;

int mymap_init (map_t* map);
void* mymap_mmap (map_t* map, void* vaddr, unsigned int size, unsigned int flags, void* o);
void mymap_munmap(map_t *map, void* vaddr);
int mymap_dump(map_t* map);

#endif /* MAP_H_ */
