#ifndef FRACTIONAL_H_
#define FRACTIONAL_H_
//分数类：用分数代替小数进行计算，有着小数点后18位的精度
//分数类的精度仅仅比double多了两位，但是内存大小却翻了倍，而且无法像double一样存储大数
//那么我编写分数类的意义何在？
//我编写分数类的最重要的一点是为了能够得到如下的数字：
//我想要看到的是10.0而不是9.999999999999999999
//我也不想看到运算中一个0.0000000000000001因为与一个大数相乘得到了0.1这样的影响数值分析的数
#include "mathop.h"
#include<iostream>
using namespace std;

#define FRACTIONAL_PERCISION_LIMIT (1E18)
typedef long long Ftype;

class Fraction {
private:
	Ftype numer_ = 0;//分子
	Ftype denomin_ = 1;//分母
	void __fraction_simplify(void);//分数约分

public:
	Fraction() {}
	~Fraction() {}
	template<class T>
	Fraction(T num) { numer_ = num; }//对于int或者char，直接赋值给分子
	template<> Fraction(float num);//对于float
	template<> Fraction(double num);//	double时，进行运算后转化为分数
	Fraction(Ftype numer, Ftype denomin);//分数的正规构建函数

	void SetNumerator(const Ftype);//设置分子
	void SetDenominator(const Ftype);//设置分母
	Ftype Denominator(void)const;//返回分母
	Ftype Numerator(void)const;//返回分子
	Ftype Int64(void)const;//返回int化的分数
	double Double(void)const;//返回double化的分数
	
	void operator=(const Fraction&);
	template<class T>
	void operator=(const T num) { *this = Fraction(num); }

	Fraction operator+(const Fraction&)const;
	Fraction operator-(const Fraction&)const;
	Fraction operator*(const Fraction&)const;
	Fraction operator/(const Fraction&)const;

	template<class T>
	Fraction operator+(const T num)const { return *this + Fraction(num); }
	template<class T>
	Fraction operator-(const T num)const { return *this - Fraction(num); }
	template<class T>
	Fraction operator*(const T num)const { return *this * Fraction(num); }
	template<class T>
	Fraction operator/(const T num)const { return *this / Fraction(num); }
	
	template<class T>
	friend Fraction operator+(const T num,const Fraction& frac){ return Fraction(num) + frac; }
	template<class T>
	friend Fraction operator-(const T num, const Fraction& frac) { return Fraction(num) - frac; }
	template<class T>
	friend Fraction operator*(const T num, const Fraction& frac) { return Fraction(num) * frac; }
	template<class T>
	friend Fraction operator/(const T num, const Fraction& frac) { return Fraction(num) / frac; }

	friend ostream& operator<<(ostream&, const Fraction&);
};

#endif