#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

#if DEBUG
#include <assert.h>
#define ASSERT(x)    \
    do {             \
        assert((x)); \
    } while (0)
#else
#define ASSERT(x)
#endif /* DEBUG */

#define queue_likely(x) __builtin_expect(!!(x), 1)
#define queue_unlikely(x) __builtin_expect(!!(x), 0)

#define T QueueControl_T
#define X QueueElement_T

T QueueNew() { return (T)calloc(1, sizeof(struct T)); }
X QueuePop(T q) {
    if (queue_unlikely(!q)) return NULL;
    if (queue_unlikely(!q->n)) return NULL;

    // pop the return one
    X r = q->head;

    // update the control
    q->head = r->next;
    q->n--;
    if (queue_likely(q->head)) {
        q->head->prev = NULL;
    }

    // if empty now
    if (queue_unlikely(!q->n)) {
        q->tail = NULL;
    }

    // update the element
    r->next = NULL;
    r->owner = NULL;

    ASSERT(NULL == r->prev);

    return r;
}
int QueuePush(T q, X v) {
    if (!q) return -1;
    if (!v) return -1;

    ASSERT(NULL == v->next);
    ASSERT(NULL == v->prev);

    v->owner = q;
    if (queue_likely(q->n)) {
        // update the element
        v->prev = q->tail;

        // update the control
        q->tail->next = v;
        q->tail = v;
    } else {
        // the queue is empty
        q->tail = q->head = v;
    }
    q->n++;

    return 0;
}

int QueueRemove(X v) {
    if (!v) return -1;
    T q = v->owner;
    if (!v->owner) return -1;

    ASSERT(q->n);
    ASSERT(v->next || v->prev);

    X o;
    if (NULL != (o = v->prev)) {
        o->next = v->next;
    }
    if (NULL != (o = v->next)) {
        o->prev = v->prev;
    }
    q->n--;

    return 0;
}

#ifdef DEBUG
void QueueShow(T q) {
    printf("Q size: %u\n", q->n);
    printf("Q head: %p, tail %p\n", q->head, q->tail);

    register X this = q->head;
    for (size_t i = 0; i < q->n && this; i++, this = this->next) {
        printf("elem %u: prev %016p\tself %016p\tnext %016p\n", i, this->prev, this,
               this->next);
    }
}
#endif /* DEBUG */

#undef T
#undef X

#undef queue_unlikely
#undef queue_likely