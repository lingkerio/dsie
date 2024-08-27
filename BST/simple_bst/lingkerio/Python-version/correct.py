import sys
import Bst

sys.setrecursionlimit(3000)

def load_operations(filename):
    operations = []
    with open(filename, "r") as file:
        for line in file:
            operation, value_str = line.strip().split(',')
            value = int(value_str)
            operations.append((operation, value))
    return operations

def process_operation(bst, operation, value, output_file):
    if operation == "insert":
        bst.insert(value)
        output_file.write(f"insert,{value}\n")
    elif operation == "search":
        found = bst.search(value)
        output_file.write(f"search,{value},{'true' if found else 'false'}\n")
    elif operation == "delete":
        node_to_delete = bst.search(value)
        bst.delete(value)
        if node_to_delete:
            output_file.write(f"delete,{value}\n")
        else:
            output_file.write(f"delete,{value},null\n")
    elif operation == "findmin":
        min_value = bst.find_min()
        if min_value is not None:
            output_file.write(f"findmin,{min_value}\n")
        else:
            output_file.write(f"findmin,null\n")
    elif operation == "findmax":
        max_value = bst.find_max()
        if max_value is not None:
            output_file.write(f"findmax,{max_value}\n")
        else:
            output_file.write(f"findmax,null\n")
    else:
        output_file.write(f"Invalid operation: {operation}\n")

if __name__ == "__main__":
    filename = "../../../benchmark/benchmark_operations.csv"
    output_filename = "correctness.csv"
    
    operations = load_operations(filename)
    
    bst = Bst.BST()
    with open(output_filename, "w") as output_file:
        for operation, value in operations:
            process_operation(bst, operation, value, output_file)
    
    print("Correctness test completed. Results are saved in correctness.csv.")