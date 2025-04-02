#include<stdio.h>
#define BUFFER_SIZE 5
void wait(int *mutex)
{
    (*mutex)--;
}

void signal(int *mutex)
{
    (*mutex)++;
}

void producer(int *x,int *mutex,int *full,int *empty)
{
    if(*empty>0)
    {
        wait(&mutex);
        (*full)++;
        (*empty)--;
        (*x)++;
        printf("Producer produced the product %d\n",*x);
        signal(&mutex);
    }
    else{
        printf("Buffer is Full! Can't Produce\n");
    }
}

void consumer(int *x,int *mutex,int *full,int *empty)
{
    if(*full>0){
        wait(&mutex);
        (*full)--;
        (*empty)++;
        printf("Consumer consumed the product %d\n",*x);
        (*x)--;
    }
    else{
        printf("Buffer is empty!\n");
    }
}

void main()
{
    int empty=BUFFER_SIZE;
    int full=0,mutex=1,choice;
    int x=0, loop=1;
    printf("Producer-Consumer Problem using Semaphore\n");
    while(loop){
        printf("\n---MENU--- \n1.Producer\n2.Consumer\n3.Exit\nEnter your choice\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            producer(&x,&mutex,&full,&empty);
            break;
        case 2:
            consumer(&x,&mutex,&full,&empty);
            break;
        case 3:
            printf("Exiting...");
            loop=0;
        default :
            printf("Enter Valid choice\n");
        }
    }
}
