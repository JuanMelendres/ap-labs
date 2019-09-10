package main

import (
  "fmt"
)

func main() {
  var s []byte
  s = make([]byte, 5, 10)

  s = []byte("ssfsfsffsfssffs")
  fmt.Println(s)
  fmt.Println(len(s))
  fmt.Println(cap(s))
}
