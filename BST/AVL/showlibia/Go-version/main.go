package main

import (
	"flag"
)

func main() {
	// 定义命令行参数
	runTest := flag.Bool("test", false, "Run the test function")
	runCorrect := flag.Bool("correct", false, "Run the correct function")

	// 解析命令行参数
	flag.Parse()

	// 根据命令行参数执行对应的函数
	if *runTest {
		test()
	}

	if *runCorrect {
		correct()
	}

	// 如果没有提供任何参数，默认执行两个函数
	if !*runTest && !*runCorrect {
		test()
		correct()
	}
}
