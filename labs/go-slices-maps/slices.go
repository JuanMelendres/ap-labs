package main

import "golang.org/x/tour/pic"

func Pic(dx, dy int) [][]uint8 {
  data := make([][]uint8, dy)
  for i := range data {
      data[i] = make([]uint8, dx)
  }
  for x := range data {
      for y := range data[x] {
          data[x][y] = uint8(x*y)
      }
  }
  return data
}

func main() {
  pic.Show(Pic)
}
