# C++11 类型别名

- 类型别名是一个名字，它是某种类型的同义词。使用类型别名可以使复杂的类型名字简单明了、易于理解和使用，有助于程序员清楚的知道使用该类型的真实目的。

- 两种定义类型别名的方法：
    1. typedef
    2. 别名声明 using
```
typedef double mydouble;
using mydouble = double;
```

- 指针、常量和类型别名
```
typedef char *pstring;
const pstring cstr = 0;     //cstr的类型为 char *const 而不是 const char*
const pstring *ps;          //ps的类型为 char *cosnt* 而不是 const char**
```

