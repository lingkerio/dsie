package bst;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

class Operation {
    String operation;
    int value;

    Operation(String operation, int value) {
        this.operation = operation;
        this.value = value;
    }
}

public class Main {

    public static void main(String[] args) {
        String filename = "../../../benchmark/benchmark_operations.csv";

        List<Operation> operations = new ArrayList<>();
        int count = loadOperations(filename, operations);
        if (count < 0) {
            System.exit(1);
        }

        BST bst = new BST();  // Instantiate your BST
        double elapsedTime = timeExecution(bst, operations);
        System.out.printf("Total time to execute all BST operations (excluding I/O): %.6f seconds%n", elapsedTime);
    }

    public static int loadOperations(String filename, List<Operation> operations) {
        try (DataInputStream br = new DataInputStream(new FileInputStream(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length == 2) {
                    try {
                        operations.add(new Operation(parts[0], Integer.parseInt(parts[1])));
                    } catch (NumberFormatException e) {
                        System.err.printf("Warning: Malformed line: %s%n", line);
                    }
                } else {
                    System.err.printf("Warning: Malformed line: %s%n", line);
                }
            }
        } catch (IOException e) {
            System.err.printf("Error opening file: %s%n", filename);
            return -1;
        }
        return operations.size();
    }

    public static double timeExecution(BST bst, List<Operation> operations) {
        long startTime = System.nanoTime();

        for (Operation operation : operations) {
            processOperation(bst, operation.operation, operation.value);
        }

        long endTime = System.nanoTime();
        return (endTime - startTime) / 1_000_000_000.0;
    }

    public static void processOperation(BST bst, String operation, int value) {
        switch (operation) {
            case "insert":
                bst.insert(value);
                break;
            case "search":
                boolean found = bst.contains(value);
                // You can print the result or handle it accordingly
                // System.out.printf("Search %d: %s%n", value, found ? "Found" : "Not Found");
                break;
            case "delete":
                bst.remove(value);
                break;
            case "findmin":
                bst.findMin();
                break;
            case "findmax":
                bst.findMax();
                break;
            default:
                System.err.printf("Unknown operation: %s%n", operation);
        }
    }
}
