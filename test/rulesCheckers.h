#ifndef RULESCHECKERS_H_
#define RULESCHECKERS_H_

typedef enum {
	RUN_CHECKS__DONT_PRINT,
	RUN_CHECKS__PRINT
}RunChecksPrint_t;

int runChecks (Node_t* root, RunChecksPrint_t print);


#endif /* RULESCHECKERS_H_ */
