#ifndef QUEUE_INCLUDE
#define QUEUE_INCLUDE

#include <stddef.h>

#define T QueueControl_T
#define X QueueElement_T
typedef struct T* T;
typedef struct X* X;

struct X {
    X prev;
    X next;
    T owner;
};

struct T {
    X head;
    X tail;
    size_t n;
};

extern T
QueueNew();
extern X QueuePop(T);
extern int QueuePush(T, X);
extern int QueueRemove(X);

#ifdef DEBUG
extern void QueueShow(T);
#endif /* DEBUG */

#undef X
#undef T

#endif /* QUEUE_INCLUDE */
