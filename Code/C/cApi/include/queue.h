#ifndef QUEUE_INCLUDE
#define QUEUE_INCLUDE

#include <stddef.h>

#define queue_likely(x) __builtin_expect(!!(x), 1)
#define queue_unlikely(x) __builtin_expect(!!(x), 0)

#define QName 16

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
    char name[QName];
    X head;
    X tail;
    size_t n;
    // Sem_t lock;
};

extern T QueueNew(char*);
extern X QueuePop(T);
extern int QueuePush(X, T);
extern X QueueRemove(X);

/* ---------------------- static start ---------------------- */

static inline X QueueFetch(T q) {
    if (queue_unlikely(!q)) return NULL;

    return q->head;
}

static inline X QueueNext(X v) {
    if (queue_unlikely(!v)) return NULL;

    return v->next;
}

static inline int QueueElemIn(X v, T q) {
    if (queue_unlikely(!q)) return 0;
    if (queue_unlikely(!v)) return 0;

    return (v->owner == q);
}

/* NOTE:
 * This function must be called along with the QeueueRelease
 */
static inline void QueueProtect(T q) {
    if (queue_unlikely(!q)) return;
    // SemTake(q->lock);
}

static inline void QueueRelease(T q) {
    if (queue_unlikely(!q)) return;
    // SemGive(q->lock);
}

/* ---------------------- static end ----------------------- */

#if DEBUG
extern void QueueShow(T);
#endif /* DEBUG */

#undef X
#undef T

#undef queue_unlikely
#undef queue_likely
#endif /* QUEUE_INCLUDE */
