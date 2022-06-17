/*在线处理*/

package main

import "fmt"

const MAXN = 100000 + 7

func rtp(arr []int, N int) int {
	var ThisSum, MaxSum int
	for i := 0; i < N; i++ {
		ThisSum += arr[i] //向右累加
		if ThisSum > MaxSum {
			MaxSum = ThisSum //发现更大和则更新当前结果
		}
		if ThisSum < 0 {
			ThisSum = 0 //如果当前和小于0，则清零
		}
	}
	return MaxSum
}

func main() {
	var n int
	a := make([]int, MAXN)

	fmt.Scanf("%d", &n)
	for i := 0; i < n; i++ {
		fmt.Scanf("%d", &a[i])
	}
	fmt.Println(rtp(a, n))
}
