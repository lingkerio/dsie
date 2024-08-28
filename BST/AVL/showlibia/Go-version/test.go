// main.go
package main

import (
	"fmt"
	"log"
	"time"
)

func processOperation(root *AVLNode, operation string, value int) *AVLNode {
	switch operation {
	case "insert":
		return Insert(root, value)
	case "search":
		Search(root, value)
	case "delete":
		return Remove(root, value)
	case "findmin":
		FindMin(root)
	case "findmax":
		FindMax(root)
	}
	return root
}

func timeExecution(operations []Operation) time.Duration {
	start := time.Now()

	var root *AVLNode
	for _, op := range operations {
		root = processOperation(root, op.Operation, op.Value)
	}

	return time.Since(start)
}

func test() {
	filename := "../../../benchmark/benchmark_operations.csv"

	operations, err := LoadOperations(filename)
	if err != nil {
		log.Fatal(err)
	}

	elapsedTime := timeExecution(operations)
	fmt.Printf("Total time to execute all operations: %.6f seconds\n", elapsedTime.Seconds())
}
