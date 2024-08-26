#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "bst.h"  // Assuming you put the BST implementation in bst.h

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

// Function to process a single operation and record the result
BSTNode* process_operation(BSTNode* root, const char* operation, int value, FILE* output_file) {
    if (strcmp(operation, "insert") == 0) {
        root = insert(root, value);
        fprintf(output_file, "insert,%d\n", value);
    } else if (strcmp(operation, "search") == 0) {
        bool found = search(root, value);
        fprintf(output_file, "search,%d,%s\n", value, found ? "true" : "false");
    } else if (strcmp(operation, "delete") == 0) {
        BSTNode* node_to_delete = search(root, value) ? root : NULL;
        root = delete(root, value);
        if (node_to_delete) {
            fprintf(output_file, "delete,%d\n", value);
        } else {
            fprintf(output_file, "delete,%d,null\n", value);
        }
    } else if (strcmp(operation, "findmin") == 0) {
        BSTNode* min_node = find_min(root);
        if (min_node) {
            fprintf(output_file, "findmin,%d\n", min_node->value);
        } else {
            fprintf(output_file, "findmin,null\n");
        }
    } else if (strcmp(operation, "findmax") == 0) {
        BSTNode* max_node = find_max(root);
        if (max_node) {
            fprintf(output_file, "findmax,%d\n", max_node->value);
        } else {
            fprintf(output_file, "findmax,null\n");
        }
    } else {
        fprintf(stderr, "Warning: Unknown operation: %s\n", operation);
    }
    return root;
}

// Function to execute the BST operations and record the results
void execute_operations(Operation* operations, int count, const char* output_filename) {
    FILE* output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return;
    }

    BSTNode* root = NULL;
    for (int i = 0; i < count; i++) {
        root = process_operation(root, operations[i].operation, operations[i].value, output_file);
    }

    free_bst(root);
    fclose(output_file);
}

int main() {
    const char* input_filename = "../../../benchmark/benchmark_operations.csv";
    const char* output_filename = "correctness.csv";

    Operation* operations;
    int count = load_operations(input_filename, &operations);
    if (count < 0) {
        return 1;
    }

    execute_operations(operations, count, output_filename);

    free(operations);
    return 0;
}
