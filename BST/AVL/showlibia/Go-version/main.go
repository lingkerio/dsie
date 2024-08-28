package main

import (
	"flag"
)

func main() {
	runTest := flag.Bool("test", false, "Run the test function")
	runCorrect := flag.Bool("correct", false, "Run the correct function")

	flag.Parse()

	if *runTest {
		test()
	}

	if *runCorrect {
		correct()
	}

	if !*runTest && !*runCorrect {
		test()
		correct()
	}
}
