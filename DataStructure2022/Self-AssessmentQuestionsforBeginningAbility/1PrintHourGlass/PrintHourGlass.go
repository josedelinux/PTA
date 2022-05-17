package main

import (
	"fmt"
	"math"
)

func printNtime(n int, target string) {
	for i := 0; i < n; i++ {
		fmt.Printf("%s", target)
	}
}

func main() {
	var givenN int
	var symbol string
	var lineNum int

	fmt.Scanf("%d %s", &givenN, &symbol)
	//fmt.Printf("%d %s\n", givenN, symbol)
	lineNum = int(math.Sqrt(float64((givenN-1)/2) + 1))
	actual := 2*(lineNum*lineNum-1) + 1

	for i := lineNum; i > 0; i-- {
		printNtime(lineNum-i, " ")
		printNtime(2*i-1, symbol)
		fmt.Printf("\n")
	}
	for i := 2; i <= lineNum; i++ {
		printNtime(lineNum-i, " ")
		printNtime(2*i-1, symbol)
		fmt.Printf("\n")
	}
	fmt.Println(givenN - actual)
}
