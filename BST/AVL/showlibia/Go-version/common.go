// common.go
package main

import (
	"encoding/csv"
	"fmt"
	"log"
	"os"
	"strconv"
)

type Operation struct {
	Operation string
	Value     int
}

func LoadOperations(filename string) ([]Operation, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, fmt.Errorf("error opening file: %w", err)
	}
	defer file.Close()

	var operations []Operation
	reader := csv.NewReader(file)
	for {
		record, err := reader.Read()
		if err != nil {
			break
		}

		if len(record) < 2 {
			log.Printf("Warning: Malformed line: %v\n", record)
			continue
		}

		value, err := strconv.Atoi(record[1])
		if err != nil {
			log.Printf("Warning: Invalid value: %v\n", record[1])
			continue
		}

		operations = append(operations, Operation{Operation: record[0], Value: value})
	}

	return operations, nil
}
