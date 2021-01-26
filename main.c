#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ERR_SUCCESS         0x0
#define ERR_FAILURE         0xffffffff
#define ERR_MEM_ALLOC       0xfffffffe
#define ERR_QUEUE_FULL      0xfffffffd
#define ERR_QUEUE_EMPTY     0xfffffffc

typedef struct qNode {
    char *data;
    uint32_t len;
    struct qNode *next;
} qNode_t;

typedef struct queue {
    qNode_t *front;
    qNode_t *rear;
} queue_t;

qNode_t *newNode(char *data, uint32_t len)
{
    qNode_t *tmp = (qNode_t *)malloc(sizeof(qNode_t));

    if (tmp == NULL)
        return (NULL);

    tmp->data = (char *)malloc(len);

    if (tmp->data == NULL) {
        free((void *)tmp);
        return (NULL);
    }

    memset(tmp->data, 0, len);
    memcpy(tmp->data, data, len);
    tmp->len = len;
    tmp->next = NULL;

    return (tmp);
}

int32_t isEmpty(queue_t *q)
{
    if (q->rear == NULL)
        return 1;
    else
        return 0;
}

queue_t *createQueue()
{
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));

    if (q == NULL)
        return (NULL);

    q->front = q->rear = NULL;

    return (q);
}

int32_t enQueue(queue_t *q, char *data, uint32_t len)
{
    qNode_t *tmp;

    if (data == NULL)
        return (ERR_FAILURE);

    tmp = newNode(data, len);

    if (tmp == NULL)
        return (ERR_FAILURE);

    if (isEmpty(q)) {
        q->front = q->rear = tmp;
    }
    else {
        q->rear->next = tmp;
        q->rear = tmp;
    }

    return ERR_SUCCESS;
}

qNode_t *deQueue(queue_t *q)
{
    qNode_t *tmp;

    if (isEmpty(q)) {
        return (NULL);
    }

    tmp = q->front;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    return (tmp);
}

int main()
{
    qNode_t *tmp;
    char buf[128];
    uint32_t i = 0;

    printf("Hello, World!\n\n");

    queue_t *q = createQueue();
    enQueue(q, "1", 1);
    enQueue(q, "20", 2);
    enQueue(q, "300", 3);
    enQueue(q, "50000", 5);

    while ((tmp = deQueue(q))) {
        memset(buf, 0, 128);
        memcpy(buf, tmp->data, tmp->len);
        printf("Free index: %d, data: %s (len: %u)", ++i, buf, tmp->len);
        free(tmp->data);
        free(tmp);
        printf("...done\n");
    }

    return 0;
}
