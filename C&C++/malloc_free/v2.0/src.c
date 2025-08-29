#include <stddef.h>
#include <stdio.h>
#include <errno.h>

#define HEAP_SIZE 1048576

typedef struct block {
    size_t size;
    int free;
    struct block *next;
} block_t;

static char heap[HEAP_SIZE];
static block_t *head = (block_t *)heap;

void init_heap();
void *my_malloc(size_t size);
void my_free(void *ptr);
block_t *find_free_block(size_t size);
void merge_free_blocks();

void init_heap() {
    head->size = HEAP_SIZE - sizeof(block_t);
    head->free = 1;
    head->next = NULL;
}

void *my_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    block_t *block = find_free_block(size);
    if (block == NULL) {
        errno = ENOMEM;
        perror("ERROR");
        return NULL;
    }

    // Check if we can split the block
    if (block->size > size + sizeof(block_t)) {
        // Calculate the address of the new block after splitting
        block_t *new_block = (block_t *)((char *)block + sizeof(block_t) + size);
        new_block->size = block->size - size - sizeof(block_t);
        new_block->free = 1;
        new_block->next = block->next;

        block->size = size;
        block->next = new_block;
    }

    block->free = 0;
    return (void *)((char *)block + sizeof(block_t));
}

block_t *find_free_block(size_t size) {
    block_t *current = head;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void my_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // Get the header from the user pointer
    block_t *block = (block_t *)((char *)ptr - sizeof(block_t));
    block->free = 1;

    // Merge with subsequent free blocks
    merge_free_blocks();
}

void merge_free_blocks() {
    block_t *current = head;
    while (current != NULL && current->next != NULL) {
        if (current->free) {
            block_t *next = current->next;
            // Check if the next block is adjacent in memory
            if ((char *)current + sizeof(block_t) + current->size == (char *)next) {
                if (next->free) {
                    // Merge current and next
                    current->size += sizeof(block_t) + next->size;
                    current->next = next->next;
                    continue; // Check again for further merges
                }
            }
        }
        current = current->next;
    }
}

int main() {
    init_heap();

    int *iptr = my_malloc(sizeof(int));
    if (iptr != NULL) {
        *iptr = 2;
        printf("%d\n", *iptr);
        my_free(iptr);
    }

    // After free, accessing iptr would be undefined behavior, so don't do it.
    // printf("%d\n", *iptr); // This would cause segmentation fault

    return 0;
}
