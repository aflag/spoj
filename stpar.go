package main

import (
	"fmt"
)

func Correctable(cars *[]int) bool {
	var side_street = make([]int, len(*cars))
	top := -1
	for i, carnum := range *cars {
		pos := i + 1
		if top >= 0 && side_street[top]-1 == carnum {
			top--
		}
		if carnum > pos {
			if top >= 0 && carnum > side_street[top] {
				return false
			} else {
				top++
				side_street[top] = carnum
			}
		}
	}
	return true
}

func Sort(cars *[]int) {
	for i := range *cars {
		var min int
		index := -1
		for j := i; j < len(*cars); j++ {
			if index == -1 || (*cars)[j] < min {
				min = (*cars)[j]
				index = j
			}
		}
		if index > -1 {
			tmp := (*cars)[i]
			(*cars)[i] = min
			(*cars)[index] = tmp
		}
	}
}

func RemoveGaps(cars *[]int) {
	var sorted = make([]int, len(*cars))
	for i := range *cars {
		sorted[i] = (*cars)[i]
	}
	Sort(&sorted)
	for i, v := range sorted {
		for j := range *cars {
			if v == (*cars)[j] {
				(*cars)[j] = i + 1
				break
			}
		}
	}
}

func main() {
	for {
		var n int
		if _, e := fmt.Scanf("%d", &n); e != nil {
			fmt.Scanf("%d", &n)
		}
		if n == 0 {
			break
		}
		var cars = make([]int, n)
		for i := 0; i < n; i++ {
			fmt.Scanf("%d", &cars[i])
		}
		RemoveGaps(&cars)
		if Correctable(&cars) {
			fmt.Println("yes")
		} else {
			fmt.Println("no")
		}
	}
}
