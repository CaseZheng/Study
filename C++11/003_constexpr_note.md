# C++11 constexpr 变量

- 将变量声明为constexpr类型以便由编译器来检验变量的值是否是一个常量表达式。声明为constexpr的变量一定是一个常量，而且必须用常量表达式初始化。
- 常量表达式的值需要在编译时就得到计算，因此对声明constexpr时用到的类型必须有所限制。因为这些类型一般比较简单，值也显而易见、容易得到，这些类型称为"字面值类型"
- 算数类型、引用和指针都属于字面值类型。指针和引用定义为constexpr，它们的初始值受到严格限制。一个constexpr指针的初始值必须是nullptr或者0，或者是存储于某个固定地址中的对象。
- 在constexpr定义了一个指针，限定符constexpr仅对指针有效，与指针所指对象无关。

```
const int *p = nullptr;     //p是一个指向整型常量的指针 *p不可改变 p可以改变
constexpr int *q = nullptr; //q是一个指向整数的常量指针  等同于 int * const q = nullptr; *q可以改变 q不可改变
```
