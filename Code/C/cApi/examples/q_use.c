#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct Test {
    struct QueueElement_T elem;
    int val;
} Test;

int main() {
    QueueControl_T q = QueueNew("TEST");
    Test a, b, c;
    memset(&a, 0, sizeof(a));
    memset(&b, 0, sizeof(a));
    memset(&c, 0, sizeof(a));
    a.val = 1;
    b.val = 2;
    c.val = 3;

    QueueShow(q);
    QueuePush(q, (QueueElement_T)&a);
    QueueShow(q);
    QueuePush(q, (QueueElement_T)&b);
    QueueShow(q);
    QueuePush(q, (QueueElement_T)&c);
    QueueShow(q);

    QueueRemove((QueueElement_T)&b);
    QueueShow(q);

    Test *d = (Test *)QueuePop(q);
    printf("=========d: %p, d.val: %d\n", d, d->val);
    QueueShow(q);

    d = (Test *)QueuePop(q);
    printf("=========d: %p, d.val: %d\n", d, d->val);
    QueueShow(q);

    d = (Test *)QueuePop(q);
    printf("---------d :%p\n", d);
    QueueShow(q);
    return 0;
}