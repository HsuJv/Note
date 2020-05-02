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

T QueueNew(char *name) {
    T newQ = (T)calloc(1, sizeof(struct T));
    strncpy(newQ->name, name, QName - 1);
    // newQ->lock = SemCreate(newQ->name, TRUE, FALSE, NULL);
    return newQ;
}

X QueuePop(T q) {
    if (queue_unlikely(!q)) return NULL;
    if (queue_unlikely(!q->n)) return NULL;

    // assert QueueProtect(q);
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
        // queue head is NULL already according to the previous update
        // So just set the queue tail to NULL
        q->tail = NULL;
    }

    // update the element
    r->next = NULL;
    r->owner = NULL;

    ASSERT(NULL == r->prev);

    // QueueRelease(q);

    return r;
}

int QueuePush(X v, T q) {
    if (queue_unlikely(!q)) return -1;
    if (queue_unlikely(!v)) return -1;

    ASSERT(NULL == v->next);
    ASSERT(NULL == v->prev);

    // QueueProtect(q);
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

    // QueueRelease(q);
    return 0;
}

X QueueRemove(X v) {
    if (queue_unlikely(!v)) return NULL;
    T q = v->owner;
    if (queue_unlikely(!v->owner)) return NULL;

    ASSERT(q->n);
    ASSERT(v->next || v->prev || 1 == q->n);

    // QueueProtect(q);
    X o;
    X ret = v->next;
    if (NULL != (o = v->prev)) {
        o->next = v->next;
    } else {
        // the first one
        q->head = v->next;
    }

    if (NULL != (o = v->next)) {
        o->prev = v->prev;
    } else {
        // the last one
        q->tail = v->prev;
    }

    q->n--;

    if (queue_unlikely(!q->n)) {
        // queue is empty now
        q->head = q->tail = NULL;
    }

    v->prev = NULL;
    v->next = NULL;
    v->owner = NULL;
    // QueueRelease(q);

    return ret;
}

#ifdef DEBUG
void QueueShow(T q) {
    QueueProtect(q);
    printf("Q name: %s size %lu\n", q->name, q->n);
    printf("Q head: %p, tail %p\n", q->head, q->tail);

    register X this = q->head;
    for (size_t i = 0; i < q->n && this; i++, this = this->next) {
        printf("elem %lu: prev %016lx\tself %016lx\tnext %016lx\n", i,
               (uintptr_t)this->prev, (uintptr_t)this, (uintptr_t)this->next);
    }
    QueueRelease(q);
}
#endif /* DEBUG */

#undef T
#undef X

#undef queue_unlikely
#undef queue_likely