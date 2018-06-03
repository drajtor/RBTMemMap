#ifndef INSERTIONSTRATEGIESRBT_H_
#define INSERTIONSTRATEGIESRBT_H_

//#define DEBUG_STRATEGIES
#include "redBlackTree.h"

typedef enum{
STRAT_CASE_ROOT ,
STRAT_CASE_UNCLE_RED,
STRAT_CASE_UNCLE_BLACK_TRIANGLE,
STRAT_CASE_UNCLE_BLACK_LINE,

STRAT_PARENT_IS_ROOT,
STRAT_ERROR

}Strategy_t;

void fixNodeToFitRBTRules(Node_t* node, Node_t** root_);

#endif /* INSERTIONSTRATEGIESRBT_H_ */
