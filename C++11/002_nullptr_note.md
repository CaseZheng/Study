# C++11 nullptr

- 空指针不指向任何对象。

- 生成空指针的方法：
```
int *p = nullptr;
int *p = 0;
//需要包含cstdlib头文件
int *p = NULL;
```

- nullptr是一种特殊类型的字面值，可以被抓化成任意其他的指针类型。
- NULL欲处理变量在cstdlib中定义，实际值就是0，因此用NULL初始化指针和用0初始化是一样的。新标准下最好使用nullptr，同时尽量避免使用NULL。
