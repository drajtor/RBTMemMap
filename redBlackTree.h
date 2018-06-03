#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#define BLACK	0
#define RED		1

#define LEFT	0
#define RIGHT	1

typedef unsigned long int value_t;

typedef struct Node_s {
	unsigned int color;
	struct Node_s* parent;
	struct Node_s* rightChild;
	struct Node_s* leftChild;
	value_t value;
	void* treeObject;
}Node_t;

void rotate(Node_t*const node, int side, Node_t** root_);

Node_t** initTreeRoot(void);
Node_t* addNode (value_t value, Node_t** root );
void deleteNode(value_t value, Node_t** root);
Node_t* getNode (value_t value, Node_t** root );
Node_t** getNextBinaryBranchNode (Node_t* node, value_t value);


#endif /* REDBLACKTREE_H_ */


