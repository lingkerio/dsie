// correct.go
package main

import (
	"fmt"
	"log"
	"os"
)

func processOperationCorrect(root *AVLNode, operation string, value int, outputFile *os.File) *AVLNode {
	switch operation {
	case "insert":
		root = Insert(root, value)
		fmt.Fprintf(outputFile, "insert,%d\n", value)
	case "search":
		found := Search(root, value)
		fmt.Fprintf(outputFile, "search,%d,%t\n", value, found)
	case "delete":
		if Search(root, value) {
			root = Remove(root, value)
			fmt.Fprintf(outputFile, "delete,%d\n", value)
		} else {
			fmt.Fprintf(outputFile, "delete,%d,null\n", value)
		}
	case "findmin":
		minNode := FindMin(root)
		if minNode != nil {
			fmt.Fprintf(outputFile, "findmin,%d\n", minNode.Data)
		} else {
			fmt.Fprintf(outputFile, "findmin,null\n")
		}
	case "findmax":
		maxNode := FindMax(root)
		if maxNode != nil {
			fmt.Fprintf(outputFile, "findmax,%d\n", maxNode.Data)
		} else {
			fmt.Fprintf(outputFile, "findmax,null\n")
		}
	default:
		log.Printf("Warning: Unknown operation: %s\n", operation)
	}
	return root
}

func executeOperations(operations []Operation, outputFilename string) {
	outputFile, err := os.Create(outputFilename)
	if err != nil {
		log.Fatalf("Error opening output file: %v\n", err)
	}
	defer outputFile.Close()

	var root *AVLNode
	for _, op := range operations {
		root = processOperationCorrect(root, op.Operation, op.Value, outputFile)
	}
}

func correct() {
	inputFilename := "../../../benchmark/benchmark_operations.csv"
	outputFilename := "correctness.csv"

	operations, err := LoadOperations(inputFilename)
	if err != nil {
		log.Fatal(err)
	}

	executeOperations(operations, outputFilename)
}
