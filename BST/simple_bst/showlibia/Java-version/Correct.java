package bst;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;


public class Correct {

    public static void main(String[] args) {
        String inputFilename = "../../../benchmark/benchmark_operations.csv";  
        String outputFilename = "correctness.csv";           

        BST bst = new BST();

        try (BufferedReader br = new BufferedReader(new FileReader(inputFilename));
             BufferedWriter bw = new BufferedWriter(new FileWriter(outputFilename))) {

            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length == 2 || parts.length == 3) {
                    String operation = parts[0];
                    int value = Integer.parseInt(parts[1]);
                    processOperation(bst, operation, value, bw);
                } else {
                    System.err.println("Warning: Malformed line: " + line);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void processOperation(BST bst, String operation, int value, BufferedWriter bw) throws IOException {
        if (operation.equals("insert")) {
            bst.insert(value);
            bw.write("insert," + value + "\n");
        } else if (operation.equals("search")) {
            boolean found = bst.contains(value);
            bw.write("search," + value + "," + (found ? "true" : "false") + "\n");
        } else if (operation.equals("delete")) {
            boolean found = bst.contains(value);
            bst.remove(value);
            bw.write("delete," + value + (found ? "" : ",null") + "\n");
        } else if (operation.equals("findmin")) {
            BSTNode minNode = bst.findMin();
            if (minNode != null) {
                bw.write("findmin," + minNode.data + "\n");
            } else {
                bw.write("findmin,null\n");
            }
        } else if (operation.equals("findmax")) {
            BSTNode maxNode = bst.findMax();
            if (maxNode != null) {
                bw.write("findmax," + maxNode.data + "\n");
            } else {
                bw.write("findmax,null\n");
            }
        } else {
            System.err.println("Warning: Unknown operation: " + operation);
        }
    }
}
