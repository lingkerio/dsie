import time
import sys
import Bst

sys.setrecursionlimit(3000)

def process_operation(bst, operation, value):
    if operation == "insert":
        bst.insert(value)
    elif operation == "search":
        found = bst.search(value)
        # You can print the result or handle it accordingly
        # print(f"Search {value}: {'Found' if found else 'Not Found'}")
    elif operation == "delete":
        bst.delete(value)
    elif operation == "findmin":
        min_value = bst.find_min()
        # You can print the result or handle it accordingly
        # print(f"Minimum value: {min_value}")
    elif operation == "findmax":
        max_value = bst.find_max()
        # You can print the result or handle it accordingly
        # print(f"Maximum value: {max_value}")
    else:
        print(f"Invalid operation: {operation}")

def load_operations(filename):
    operations = []
    with open(filename, "r") as file:
        for line in file:
            operation, value_str = line.strip().split(',')
            value = int(value_str)
            operations.append((operation, value))
    return operations

def time_execution(operations):
    bst = Bst.BST()
    start_time = time.time()

    for operation, value in operations:
        process_operation(bst, operation, value)

    elapsed_time = time.time() - start_time
    return elapsed_time

if __name__ == "__main__":
    filename = "../../../benchmark/benchmark_operations.csv"
    operations = load_operations(filename)
    elapsed_time = time_execution(operations)
    print(f"Total time to execute all operations: {elapsed_time:.6f} seconds")
