#ifndef RELATIONS_H_
#define RELATIONS_H_

typedef enum{
	NO_CHILDREN,
	ONE_LEFT_CHILD,
	ONE_RIGHT_CHILD,
	TWO_CHILDREN
}ChildrenStatus_t;

Node_t* getUncle(Node_t* node);
Node_t* getSibling(Node_t* node);
Node_t* getInorderSuccessor(Node_t* node);
Node_t* getInorderAncestor(Node_t* node);
ChildrenStatus_t checkChildrenStatus(Node_t* node);

#endif /* RELATIONS_H_ */
