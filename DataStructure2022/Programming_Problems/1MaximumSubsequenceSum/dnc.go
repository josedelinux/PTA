/* divide and conquer */

package main

import (
	"fmt"
)

func Max(A, B int) int {
	if A > B {
		return A
	} else {
		return B
	}
}

/* 返回3个整数中的最大值 */
func Max3(A, B, C int) int {
	return Max(A, Max(B, C))
}

/* 分治法求List[left]到List[right]的最大子列和 */
func DivideAndConquer(arr []int, left int, right int) int {
	var MaxLeftSum, MaxRightSum int             /* 存放左右子问题的解 */
	var MaxLeftBorderSum, MaxRightBorderSum int /*存放跨分界线的结果*/

	var LeftBorderSum, RightBorderSum int
	var center, i int

	/* 递归的终止条件，子列只有1个数字 */
	if left == right {
		if arr[left] > 0 {
			return arr[left]
		} else {
			return 0
		}
	}

	/* 下面是"分"的过程 */
	center = (left + right) / 2 /* 找到中分点 */
	/* 递归求得两边子列的最大和 */
	MaxLeftSum = DivideAndConquer(arr, left, center)
	MaxRightSum = DivideAndConquer(arr, center+1, right)

	/* 下面求跨分界线的最大子列和 */
	MaxLeftBorderSum = 0
	LeftBorderSum = 0
	for i = center; i >= left; i-- { /* 从中线向左扫描 */
		LeftBorderSum += arr[i]
		if LeftBorderSum > MaxLeftBorderSum {
			MaxLeftBorderSum = LeftBorderSum
		}
	} /* 左边扫描结束 */

	MaxRightBorderSum = 0
	RightBorderSum = 0
	for i = center + 1; i <= right; i++ { /* 从中线向右扫描 */
		RightBorderSum += arr[i]
		if RightBorderSum > MaxRightBorderSum {
			MaxRightBorderSum = RightBorderSum
		}
	} /* 右边扫描结束 */

	/* 下面返回"治"的结果 */
	return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum+MaxRightBorderSum)

}

var n int

func main() {

	fmt.Scanf("%d", &n)
	a := make([]int, n+1)
	for i := 0; i < n; i++ {
		fmt.Printf("%d", &a[i])
	}
	fmt.Printf("%d\n", DivideAndConquer(a, 0, n))
}
