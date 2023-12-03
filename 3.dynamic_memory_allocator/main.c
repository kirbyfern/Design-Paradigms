#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent an allocation block
struct Block {
    int block_size;         // # of bytes in the data section
    struct Block *next_block; // in C, you have to use "struct Block" as the type
};

// Constants
const size_t OVERHEAD_SIZE = sizeof(struct Block);
const size_t POINTER_SIZE = sizeof(void*);

// Global variables
struct Block *free_head = NULL;

// Function to initialize the heap
void my_initialize_heap(int size) {
    free_head = (struct Block *)malloc(size);
    if (free_head == NULL) {
        fprintf(stderr, "Failed to initialize the heap.\n");
        exit(1);
    }

    free_head->block_size = size - OVERHEAD_SIZE;
    free_head->next_block = NULL;
}

// Function to allocate memory
void *my_alloc(int size) {
    struct Block *current = free_head;
    struct Block *prev = NULL;

    while (current != NULL) {
        if (current->block_size >= size) {
            if (current->block_size - size >= OVERHEAD_SIZE + POINTER_SIZE) {
                struct Block *new_block = (struct Block *)((char *)current + size + OVERHEAD_SIZE);
                new_block->block_size = current->block_size - size - OVERHEAD_SIZE;
                new_block->next_block = current->next_block;
                current->block_size = size;
                current->next_block = new_block;
            }

            if (prev == NULL) {
                free_head = current->next_block;
            } else {
                prev->next_block = current->next_block;
            }

            return (void *)(current + 1);
        }

        prev = current;
        current = current->next_block;
    }

    return NULL;
}

// Function to deallocate memory
void my_free(void *data) {
    if (data == NULL) {
        return;
    }

    struct Block *block = (struct Block *)data - 1;
    block->next_block = free_head;
    free_head = block;
}

// Option 1: Allocate an int and print its address
void menuOptionOne() {
    int *numOne = my_alloc(sizeof(int));
    printf("Address of int A: %p\n", numOne);
    my_free(numOne);
    int *numTwo = my_alloc(sizeof(int));
    printf("Address of int B: %p\n", numTwo);
}

// Option 2: Allocate two ints and print their addresses
void menuOptionTwo() {
    int *numOne = my_alloc(sizeof(int));
    printf("Address of int A: %p\n", numOne);
    int *numTwo = my_alloc(sizeof(int));
    printf("Address of int B: %p\n", numTwo);
    printf("Verifying Results...\n");
    int overheadPlusLarger = OVERHEAD_SIZE + (int)sizeof(int);
    printf("Size of overhead + larger of (the size of an integer; the minimum block size): %d bytes\n", overheadPlusLarger);
    printf("Address B - Address A: %p - %p\n", (void*)numTwo, (void*)numOne);
}

// Option 3: Allocate three ints and print their addresses, then free the second of the three
void menuOptionThree() {
    int *numOne = my_alloc(sizeof(int));
    printf("Address of int A: %p\n", numOne);
    int *numTwo = my_alloc(sizeof(int));
    printf("Address of int B: %p\n", numTwo);
    int *numThree = my_alloc(sizeof(int));
    printf("Address of int C: %p\n", numThree);
    my_free(numTwo);
    printf("After freeing int B...\n");
    double *arr = my_alloc(2 * sizeof(double));
    printf("Address of array of 2 double values: %p\n", arr);
    int *numFour = my_alloc(sizeof(int));
    printf("Address of int D (should be the int B): %p\n", numFour);
}

// Option 4: Allocate one char and one int, and print their addresses
void menuOptionFour() {
    int check = 0;
    char *charOne = my_alloc(sizeof(char));
    printf("Address of char A: %p\n", charOne);
    int *numTwo = my_alloc(sizeof(int));
    printf("Address of int B: %p\n", numTwo);
    int overheadPlusLarger = OVERHEAD_SIZE + (int)sizeof(int);
    printf("Size of overhead + larger of (the size of an integer; the minimum block size): %d\n", overheadPlusLarger);
}

// Option 5: Allocate an 80-element int array, then for one more int value
void menuOptionFive() {
    int *arr = my_alloc(80 * sizeof(int));
    int *numOne = my_alloc(sizeof(int));
    printf("Address of array: %p\n", arr);
    printf("Address of int A: %p\n", numOne);
    printf("Address of int value: %p\n", (char *)arr + 80 * sizeof(int) + OVERHEAD_SIZE);
    printf("Value of int A: %d\n", *numOne);
    printf("Difference between array and int A: %d bytes\n", (int)((char *)numOne - (char *)arr));
    my_free(arr);
    printf("After freeing array...\n");
    printf("Address of int value: %p\n", numOne);
    printf("Value of int A: %d\n", *numOne);
}

int main() {
    int menuChoice = 0;
    int runAgain = 1;
    while (runAgain == 1) {
        printf("\n1. Allocate an int \n2. Allocate two ints \n3. Allocate three ints \n4. Allocate one char \n5. Allocate space for an 80-element int array \n6. Quit \nChoose a menu option: ");
        scanf("%d", &menuChoice);
        printf("\n---Test Case %d---\n", menuChoice);
        my_initialize_heap(1000);
        if (menuChoice == 1) {
            menuOptionOne();
        }
        else if (menuChoice == 2) {
            menuOptionTwo();
        }
        else if (menuChoice == 3) {
            menuOptionThree();
        }
        else if (menuChoice == 4) {
            menuOptionFour();
        }
        else if (menuChoice == 5) {
            menuOptionFive();
        }
        else if (menuChoice == 6) {
            printf("Done!");
            runAgain = 0;
        }
    }
    return 0;
}
