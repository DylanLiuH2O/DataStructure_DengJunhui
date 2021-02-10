## 第2章 向量

### 定义

向量（Vector）是线性数组的一种抽象与泛化，亦是由具有线性次序的一组元素构成的集合$$V={v_0,v_1,\cdots,v_{n-1}}$$，其中的元素分别由秩区分。（所谓秩就是通常说的索引、下标，其范围为$$[0,n)$$）

### 接口

| 操作          | 功能                                             | 适用对象 |
| ------------- | ------------------------------------------------ | -------- |
| size()        | 获取元素总数                                     | 向量     |
| get(r)        | 获取索引为r的元素                                | 向量     |
| put(r, e)     | 用e替换索引为r的元素                             | 向量     |
| insert(r, e)  | 在索引为r的元素前插入一个值为e的元素             | 向量     |
| remove(r)     | 删除索引为r的元素，并返回该元素                  | 向量     |
| disordered()  | 判断所有元素是否已按非降序排列                   | 向量     |
| sort()        | 非降序排列元素                                   | 向量     |
| find(e)       | 查找值为e且索引最大的元素                        | 向量     |
| search(e)     | 查找值不大于e（包括等于）且索引最大的元素        | 有序向量 |
| deduplicate() | 删除重复元素                                     | 向量     |
| uniquify()    | 删除重复元素                                     | 有序向量 |
| traverse()    | 遍历向量且对元素进行处理，处理方法由函数对象指定 | 向量     |

### 实现

**注意：这里的实现并不和书上的完全一致，有些地方进行了一些个人的修改。**

#### 数据成员

`myVector`类有三个私有成员，分别是一个`T`类型的指针，一个标识向量元素数量的`size_t`变量，一个标识当前向量容量的整型变量（注意，容量大于元素数量）。

```c++
private:
    T*  _elem;
    int _size;
    int _capacity;
```

#### 从内存中复制元素

`copyElem()`是受保护成员，只在构造函数以及赋值拷贝函数中使用。

```c++
protected:
    //only for init new obj
    void copyElem(const T* elem, int lo, int hi) {
        _capacity = 2 * (hi - lo);
        _elem = new T[_capacity];
        _size = hi - lo;
        for (int i = 0; i < _size; i++) {
            _elem[i] = elem[i];
        }
    }
```



#### 默认构造函数

实现一个类，首先考虑实现构造函数，我设计的带默认参数的默认构造函数如下。

```c++
public:
    myVector(int sz = 0, T val = 0) : _size(sz) {
        _size = sz;
        _capacity = (_size == 0) ? DEFAULT_CAPACITY : 2 * _size;
        _elem = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            _elem[i] = val;
        }
    }
```

这个默认构造函数与邓俊辉老师设计的不同之处在于，首先参数名为了增强可读性，不使用单字母，同时数据成员的初始化使用了`C++11`的初始化列表，其次去掉了默认可由用户设定其容量的设计，因为由用户来设定默认容量时，会导致很多为了防止错误的冗余操作。最后是其他的一些增强可读性的做法，例如不在下标运算符中赋值。

#### 拷贝构造函数

```c++
public:
    myVector(const myVector<T>& V) {
        copyElem(V._elem, 0, V._size);
    }
```

#### 赋值拷贝函数

```c++
public:
    myVector<T>&
    operator=(const myVector<T>& V) {
        delete[] _elem;
        copyElem(V._elem, 0, V._size);

        return *this;
    }
```

#### 获取向量的大小

```c++
public:
    int size() const {
        return _size;
    }
```

#### 重载[]运算符

为了方便获取向量的元素，我们可以对`[]`进行重载，使其返回对应元素的引用。

```c++
public:
    T& operator[](Index i) const {
        return _elem[i];
    }
```

注意，这里的`const`指的是该函数不会改变成员本身，即指针`_elem`的内容，因此可以修改指针指向的内容。

#### 输出向量

我们通过重载`<<`运算符，可以方便地实现向量元素的输出。

```c++
template <typename T>
ostream& operator<<(ostream& os, const myVector<T>& V) {

    cout << "[";
    for (int i = 0; i < V.size(); i++) {
        cout << V[i];
        if (i < V.size()-1)
            cout << ",";
    }
    cout << "]";
    
    return os;
}
```

这是一个非成员函数。

