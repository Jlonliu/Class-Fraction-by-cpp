#include "fraction.h"
#include<iostream>

using namespace std;

void Fraction::__fraction_simplify(void) {
	Ftype gcd = GreatestCommonDivisor(numer_, denomin_);// 最大公约数变量
	numer_ = numer_/gcd;
	denomin_ = denomin_/gcd;
}

template<> Fraction::Fraction(float num) {
	bool bOverflow = true;//double数值溢出标志
	double denomin = 1.0;//分母
	int i = 0;
	//double型仅能提供16位精准有效数字
	//分数能够提供18位精准有效数字，精度在double之上
	//但是double可以舍弃精度来存储几百次幂的巨大数字，分数要保证精度，只能存储18次幂的最大数字
	//遇到精度低的巨大double数字，分数很可能无法存储，所以要先检测double数值转化为分数是否会溢出
	for (denomin = 1.0; denomin < INT64_MAX; denomin = denomin * 10) {
		if (abs(num * denomin) > INT64_MAX) {//如果double数值在小数消除过程中溢出了
			break;
		}
		if (num * denomin - Ftype(num * denomin) == 0) {//消除double数值的所有小数
			bOverflow = false;//double数值未溢出
			break;
		}
	}

	if (bOverflow) {//double数值超程
		//Marked
		//异常处理
		//暂时先报个警
		cout << "转化为分数的数值超程" << endl;

	}
	else {
		numer_ = Ftype(num * denomin);
		denomin_ = Ftype(denomin);
		__fraction_simplify();//分数约分
	}
}

template<> Fraction::Fraction(double num) {
	bool bOverflow = true;//double数值溢出标志
	double denomin = 1.0;//分母
	int i = 0;
	//double型仅能提供16位精准有效数字
	//分数能够提供18位精准有效数字，精度在double之上
	//但是double可以舍弃精度来存储几百次幂的巨大数字，分数要保证精度，只能存储18次幂的最大数字
	//遇到精度低的巨大double数字，分数很可能无法存储，所以要先检测double数值转化为分数是否会溢出
	for (denomin = 1.0; denomin < INT64_MAX; denomin = denomin * 10) {
		if (abs(num * denomin) > INT64_MAX) {//如果double数值在小数消除过程中溢出了
			break;
		}
		if (num * denomin - Ftype(num * denomin) == 0) {//消除double数值的所有小数
			bOverflow = false;//double数值未溢出
			break;
		}
	}

	if (bOverflow) {//double数值超程
		//Marked
		//异常处理
		//暂时先报个警
		cout << "转化为分数的数值超程" << endl;

	}
	else {
		numer_ = Ftype(num * denomin);
		denomin_ = Ftype(denomin);
		__fraction_simplify();//分数约分
	}
}

Fraction::Fraction(Ftype numer, Ftype denomin) {
	if (denomin == 0) {//如果分母为0
		//Marked
		//异常处理
		//暂时先报个警
		cout << "错误：分母设置为了0" << endl;
	}
	else {
		numer_ = numer;
		denomin_ = denomin;
		__fraction_simplify();//分数约分
	}
}

void Fraction::SetNumerator(const Ftype num) {
	numer_ = num;
}

void Fraction::SetDenominator(const Ftype num) {
	denomin_ = num;
}

Ftype Fraction::Denominator(void)const {
	return denomin_;
}

Ftype Fraction::Numerator(void)const {
	return numer_;
}

Ftype Fraction::Int64(void)const {
	return numer_ / denomin_;
}

double Fraction::Double(void)const {
	return double(double(numer_) / double(denomin_));
}

void Fraction::operator=(const Fraction& frac) {
	numer_ = frac.Numerator();
	denomin_ = frac.Denominator();
}

Fraction Fraction::operator+(const Fraction& frac)const {
	Fraction fracThis = *this;
	Ftype lcm = LeastCommonMultiple(fracThis.Denominator(), frac.Denominator());//获取分母最大公约数
	Ftype fracThisMultiple = lcm / fracThis.Denominator();//分子乘子：最小公倍数除以分母
	Ftype fracMultiple = lcm / frac.Denominator();//分子乘子：最小公倍数除以分母
	fracThis.SetNumerator(fracThis.Numerator() * fracThisMultiple
		+ frac.Numerator() * fracMultiple);//分子乘乘子后相加
	//fracThis.SetDenominator(fracThis.Denominator() * frac.Denominator());//分母相乘
	fracThis.SetDenominator(lcm);//获取分母
	return fracThis;
}

Fraction Fraction::operator-(const Fraction& frac)const {
	Fraction fracThis = *this;
	Ftype lcm = LeastCommonMultiple(fracThis.Denominator(), frac.Denominator());//获取分母最大公约数
	Ftype fracThisMultiple = lcm / fracThis.Denominator();//分子乘子：最小公倍数除以分母
	Ftype fracMultiple = lcm / frac.Denominator();//分子乘子：最小公倍数除以分母
	fracThis.SetNumerator(fracThis.Numerator() * fracThisMultiple
		- frac.Numerator() * fracMultiple);//分子乘乘子后相减
	//fracThis.SetDenominator(fracThis.Denominator() * frac.Denominator());//分母相乘
	fracThis.SetDenominator(lcm);//获取分母
	return fracThis;
}

Fraction Fraction::operator*(const Fraction& frac)const {
	Fraction fracThis = *this;
	fracThis.SetNumerator(fracThis.Numerator() * frac.Numerator());//分子相乘
	fracThis.SetDenominator(fracThis.Denominator() * frac.Denominator());//分母相乘
	return fracThis;
}

Fraction Fraction::operator/(const Fraction& frac)const {
	Fraction fracThis = *this;
	fracThis.SetNumerator(fracThis.Numerator() * frac.Denominator());//分子乘分母
	fracThis.SetDenominator(fracThis.Denominator() * frac.Numerator());//分母乘分子
	return fracThis;
}

ostream& operator<<(ostream& os, const Fraction& frac) {
	if (frac.Denominator() == 1) {//如果分母为1
		cout << frac.numer_;//直接输出分子
	}
	else {
		cout << frac.numer_ << "/" << frac.denomin_;
	}
	
	return os;
}
