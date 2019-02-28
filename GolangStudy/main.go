package main

import "fmt"



func main() {
    var a int = 1
    var b = 1
    c := 1
    d := "ddddddddddddd"
    fmt.Println(a, b, c, d)

    e := &a
    fmt.Println(e, *e)

    *e = 2
    fmt.Println(a, *e)

    f := e
    fmt.Println(f, e, &a, *f, *e, a)

    g, h, i := 1, 2.3, "iiiiiiiiii"
    fmt.Println(g, h, i)

    const J = 10
    fmt.Println(J)

    const (
        I = "IIIIIIIIIII"
        H = len(I)
        K = 0
        L = "hehhe"
        M = iota
    )
    fmt.Println(I, H, K, L, M)

    for n:=0; n<5; n++ {
        fmt.Println(n)
        if n==3 {
            fmt.Println("33333333")
            break;
        }
    }

    for a<5 {
        a++
        fmt.Println(a)
        if a%2==1 {
            fmt.Println("22222")
            continue;
        }
    }

    array := [6]int{1,4,5,6}
    for n,x := range array {
        fmt.Println(n, x)
        if n==3 {
            goto N3
        }
    }
    N3: fmt.Println("N3")
}
