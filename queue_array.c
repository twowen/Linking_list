#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define QUEUE_LEN_WS_PKT 10

#define ERR_SUCCESS 0
#define ERR_FAILURE (-1)
#define ERR_QUEUE_FULL (-2)
#define ERR_QUEUE_EMPTY (-3)

#define QUEUE_SIZE_INC ((size) = (size) + (1))
#define QUEUE_SIZE_DEC ((size) = (size) - (1))

int queue[QUEUE_LEN_WS_PKT];
uint8_t size = 0;
uint8_t rear = (QUEUE_LEN_WS_PKT - 1);
uint8_t front = 0;

int8_t enqueue(int data);
int8_t dequeue();
int8_t isFull();
int8_t isEmpty();
int8_t getRear();
int8_t getFront();

int8_t enqueue(int data)
{
    if (isFull()) {
        return ERR_QUEUE_FULL;
    }
    
    rear = (rear + 1) % QUEUE_LEN_WS_PKT;
    
    queue[rear] = data;
    
    QUEUE_SIZE_INC;
    
    return ERR_SUCCESS;
}

int8_t dequeue()
{
    int8_t data = INT_MIN;

    if (isEmpty()) {
        return ERR_QUEUE_EMPTY;
    }
    
    data = queue[front];
    
    front = (front + 1) % QUEUE_LEN_WS_PKT;
    
    QUEUE_SIZE_DEC;
    
    return (data);
}

int8_t isFull()
{
    return (size == QUEUE_LEN_WS_PKT);
}

int8_t isEmpty()
{
    return (size == 0);
}

int8_t getRear()
{
    return (isEmpty() ? INT_MIN : queue[rear]);
}

int8_t getFront()
{
    return (isEmpty()?INT_MIN:queue[front]);
}

int main()
{
    int ch, data;


    /* Run indefinitely until user manually terminates */
    while (1)
    {
        /* Queue menu */
        printf("--------------------------------------\n");
        printf("  QUEUE ARRAY IMPLEMENTATION PROGRAM  \n");
        printf("--------------------------------------\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Size\n");
        printf("4. Get Rear\n");
        printf("5. Get Front\n");
        printf("0. Exit\n");
        printf("--------------------------------------\n");
        printf("Select an option: ");

        scanf("%d", &ch);

        
        /* Menu control switch */
        switch (ch)
        {
            case 1:
                printf("\nEnter data to enqueue: ");
                scanf("%d", &data);

                // Enqueue function returns 1 on success
                // otherwise 0
                if (ERR_SUCCESS == enqueue(data))
                    printf("Element added to queue.");
                else
                    printf("Queue is full.");

                break;

            case 2:
                data = dequeue();

                // on success dequeue returns element removed
                // otherwise returns INT_MIN
                if (data == INT_MIN)
                    printf("Queue is empty.");
                else
                    printf("Data => %d", data);

                break;

            case 3: 

                // isEmpty() function returns 1 if queue is emtpy 
                // otherwise returns 0
                if (isEmpty())
                    printf("Queue is empty.");
                else 
                    printf("Queue size => %d", size);

                break;

            case 4: 

                if (isEmpty())
                    printf("Queue is empty.");
                else 
                    printf("Rear => %d", getRear());

                break;

            case 5: 

                if (isEmpty())
                    printf("Queue is empty.");
                else 
                    printf("Front => %d", getFront());

                break;

            case 0:
                printf("Exiting from app.\n");
                exit(0);
        
            default:
                printf("Invalid choice, please input number between (0-5).");
                break;
        }

        printf("\n\n");
    }
}
