#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "AVL.h"  // Assuming you put the AVL implementation in avl.h

#define MAX_LINE_LENGTH 100

// Structure to hold an operation and its value
typedef struct {
    char operation[MAX_LINE_LENGTH];
    int value;
} Operation;

// Function to read operations from a CSV file into an array
int load_operations(const char* filename, Operation** operations) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int capacity = 100;  // Initial capacity for the operations array
    int count = 0;
    *operations = (Operation*)malloc(capacity * sizeof(Operation));

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (count >= capacity) {
            capacity *= 2;
            *operations = (Operation*)realloc(*operations, capacity * sizeof(Operation));
        }
        if (sscanf(line, "%[^,],%d", (*operations)[count].operation, &(*operations)[count].value) == 2) {
            count++;
        } else {
            fprintf(stderr, "Warning: Malformed line: %s", line);
        }
    }

    fclose(file);
    return count;
}

// Function to process a single operation
AVLNode* process_operation(AVLNode* root, const char* operation, int value) {
    if (strcmp(operation, "insert") == 0) {
        return insert(root, value);
    } else if (strcmp(operation, "search") == 0) {
        bool found = search(root, value);
        // You can print the result or handle it accordingly
        // printf("Search %d: %s\n", value, found ? "Found" : "Not Found");
    } else if (strcmp(operation, "delete") == 0) {
        return delete(root, value);
    }
    return root;
}

// Function to time the execution of the AVL operations (excluding I/O time)
double time_execution(Operation* operations, int count) {
    clock_t start = clock();

    AVLNode* root = NULL;
    for (int i = 0; i < count; i++) {
        root = process_operation(root, operations[i].operation, operations[i].value);
    }
    printf("%d\n", count);

    clock_t end = clock();
    free_avl(root);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    const char* filename = "../../../benchmark/benchmark_operations.csv";

    Operation* operations;
    int count = load_operations(filename, &operations);
    if (count < 0) {
        return 1;
    }

    double elapsed_time = time_execution(operations, count);
    printf("Total time to execute all AVL operations (excluding I/O): %.6f seconds\n", elapsed_time);

    free(operations);
    return 0;
}
