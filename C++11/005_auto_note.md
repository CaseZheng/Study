# C++11 auto

- auto类型说明符，让编译器分析表达式所属的类型。auto让编译器通过初始值类推算变量的类型。auto定义的变量必须有初始值。

- 使用引用其实是使用引用的对象，此时编译器以引用对象的类型做为auto的类型。
- auto一般会忽略顶层const, 底层const则会保留下来。如果需要推断出的auto类型是一个顶层const，需要明确指出。

```
	int i = 0, &r = i;
	auto a = r;			// int a

	const int ci = i, &cr = ci;
	auto b = ci;		// int b = ci;
	auto c = cr;		// int c = cr;
	auto d = &i;		// int *d = &i;
	auto e = &ci;		// const int *e = &ci;

	const auto f = ci;	// const int f = ci;

	auto &g = ci;		// const int &g = ci;
	//auto &h = 42;  错误，不能为非常量引用绑定字面值
	const auto &j = 42;	// const int &j = 42;

	auto k = ci, &l = i;		// int k = ci, &l = i;
	auto &m = ci, *p = &ci;		// const int &m	= ci, *p = &ci;
	//auto &n = i, *p2 = &ci; 错误，i的类型是int，而&ci的类型为const int
```
