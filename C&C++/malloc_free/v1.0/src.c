#include <stddef.h>
#include<stdio.h>
#include<errno.h>

#define HEAP_SIZE 1048576

typedef struct block{
    size_t size;
    int free;
    struct block *next;
} block_t;




static char heap[HEAP_SIZE];
static block_t *head = (block_t *)heap;
static long freeSize;

void init_heap();
void *my_malloc(int size);
void my_free(void* ptr);
void loger(block_t *blc);
block_t *findFree(int);


int main()
{
    init_heap();

    int *iptr;
    iptr = my_malloc(sizeof(int));
    *iptr=2;
    printf("%d\n",*iptr);
    my_free(iptr);
    //printf("%d\n",*iptr); //Segmentation fault


    return 0;
}
void init_heap() {
    freeSize = HEAP_SIZE - sizeof(block_t);
    head->size = HEAP_SIZE - sizeof(block_t);
    head->free = 1;
    head->next = NULL;
}

void loger(block_t *blc)
{
    printf("%zu\t%d\t%p\n",blc->size,blc->free,blc->next);
}

void *my_malloc(int size)
{
    block_t *t;

    if(head->next==NULL)
    {
        head->size=size;
        head->free=0;
        head->next=(block_t *)heap+sizeof(block_t)+size+1;

        freeSize-=(sizeof(block_t)+size);
        head->next->size=freeSize;

        return head+sizeof(block_t)+1;
    }
    else
    {

        t=findFree(size);
        if(t == NULL)
        {
            errno=ENOMEM;
            perror("ERROR");
            return NULL;
        }
        t->size=size;
        t->free=0;
        t->next=(block_t *)t+size+sizeof(block_t)+1;

        freeSize-=(sizeof(block_t)+size);
        head->next->size=freeSize;

        return t+sizeof(block_t)+1;
    }

}
block_t *findFree(int size)
{
    block_t *temp=head;
    while(temp->next!=NULL)
    {

        if(temp->free)
            if(temp->size>=size)
                return temp;

        temp=temp->next;
    }

    return NULL;
}

void my_free(void* ptr)
{
    block_t* temp;
    ptr -= sizeof(block_t);
    temp=(block_t*)ptr;
    temp->free=1;

    freeSize+=temp->size;

    while(temp->free)
    {
        if(temp->next->free)
        {
            temp->size+=temp->next->size;
            temp = temp->next;
        }
        else
            break;
    }

}
