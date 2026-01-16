#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000
#define TEST_VALUE 500

/* ---------------- Data Structures ---------------- */

int array[MAX_SIZE];

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

/* ---------------- Function Prototypes ---------------- */

void generateRandomNumbers(int size);
void populateLinkedList(int size);
void freeLinkedList();

void insertArray(int num, int index);
void deleteArray(int num, int size);
int linearSearchArray(int num, int size);
void bubbleSortArray(int size);

void insertLinkedList(int num);
void deleteLinkedList(int num);
void linearSearchLinkedList(int num);

void measureTime(int size);

/* ---------------- Main ---------------- */

int main() {
    srand(time(NULL));

    int sizes[] = {10, 100, 1000, 10000};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < count; i++) {
        printf("\n--- Testing for N = %d ---\n", sizes[i]);

        generateRandomNumbers(sizes[i]);
        populateLinkedList(sizes[i]);
        measureTime(sizes[i]);
        freeLinkedList();
    }

    return 0;
}

/* ---------------- Utility Functions ---------------- */

void generateRandomNumbers(int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}

void populateLinkedList(int size) {
    for (int i = 0; i < size; i++) {
        insertLinkedList(array[i]);
    }
}

void freeLinkedList() {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* ---------------- Array Operations ---------------- */

void insertArray(int num, int index) {
    array[index] = num;
}

void deleteArray(int num, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == num) {
            for (int j = i; j < size - 1; j++) {
                array[j] = array[j + 1];
            }
            break;
        }
    }
}

int linearSearchArray(int num, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == num) return i;
    }
    return -1;
}

void bubbleSortArray(int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

/* ---------------- Linked List Operations ---------------- */

void insertLinkedList(int num) {
    struct Node* node = malloc(sizeof(struct Node));
    node->data = num;
    node->next = head;
    head = node;
}

void deleteLinkedList(int num) {
    struct Node *temp = head, *prev = NULL;

    while (temp != NULL && temp->data != num) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}

void linearSearchLinkedList(int num) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == num) return;
        temp = temp->next;
    }
}

/* ---------------- Benchmarking ---------------- */

void measureTime(int size) {
    clock_t start, end;

    start = clock();
    insertArray(TEST_VALUE, size - 1);
    end = clock();
    printf("Array insertion: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    deleteArray(TEST_VALUE, size);
    end = clock();
    printf("Array deletion: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    linearSearchArray(TEST_VALUE, size);
    end = clock();
    printf("Array search: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    bubbleSortArray(size);
    end = clock();
    printf("Array sort (bubble): %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    insertLinkedList(TEST_VALUE);
    end = clock();
    printf("Linked list insertion: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    deleteLinkedList(TEST_VALUE);
    end = clock();
    printf("Linked list deletion: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    linearSearchLinkedList(TEST_VALUE);
    end = clock();
    printf("Linked list search: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);
}
