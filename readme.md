# Class-Fraction-by-cpp

[toc]

a fraction of class to deal with precision number.
like 0.333333333333*3 not is 1,but 1/3*3 is 1.
这是一个分数类（1/3），用来处理精确数值。
比如double类下0.33333333333*3大概率会得到1。
而Fraction计算0.333333333333*3=0.999999999999（惊！几个3几个9...）。
Fraction计算1/3*3才等于1。

## 优势

- 对于18位有效数字以内的数，Fraction比double更加精确。
- 比16位有效数字的double多了两位有效数字（呃...好像无关紧要）

## 缺点

- 作为一个类而非关键字，计算时增加运算时间
- Fraction本质是两个int64的数字，内存空间比double翻倍
- Fraction支持的最大有效数字仅18位，不能像double一样舍弃精度，存储超大数。

---

## 正文

- Fraction支持“+-*/”操作，可以在Fraction、int、double之间进行四则运算，但是运算结果仅能赋值给Fraction。Fraction不能赋值给int或者double。

- 如果要得到int、double类型的Fraction数值，可以使用Int64()与Double()类函数。


### 构造函数
  - Fraction(数值)
  - Fraction(int64_t 分子, int64_t 分母)
  
### Int64()
- 将Fraction值转化为int64_t后返回
- 参数：无
- 返回值：int64_t

### Double()
- 将Fraction值转化为double后返回
- 参数：无
- 返回值：double

### SetNumerator()
- 设置Fraction的分子数值
- 参数:int64_t
- 返回值：void
  
### SetDenominator()
- 设置Fraction的分母数值
- 参数:int64_t
- 返回值：void

### Numerator()
- 获取Fraction的分子
- 参数：无
- 返回值：int64_t

### Denominator()
- 获取Fraction的分母
- 参数：无
- 返回值：int64_t