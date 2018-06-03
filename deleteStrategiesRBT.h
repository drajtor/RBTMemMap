#ifndef DELETESTRATEGIESRBT_H_
#define DELETESTRATEGIESRBT_H_

#include "redBlackTree.h"

void nodeHasOneChildDeleteStrategy(Node_t* node, Node_t* child);
void DoubleBlackDeleteStrategy(Node_t* node, Node_t** root);

#endif /* DELETESTRATEGIESRBT_H_ */
