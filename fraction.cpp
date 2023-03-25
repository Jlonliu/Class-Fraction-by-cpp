#include "fraction.h"
#include<iostream>
using namespace std;

void Fraction::__fraction_simplify(void) {
	Ftype lcm = __least_common_multiple(numer_,denomin_);
	Ftype numer = numer_;

	numer_ = lcm/denomin_;
	denomin_ = lcm/numer;
}

Ftype Fraction::__least_common_multiple(const Ftype denominL, const Ftype denominR) {
	Ftype m, n, r,lcm;//gcd为最大公约数变量，lcm为最小公倍数变量

	m = denominL;
	n = denominR;
	//算法：辗转相除法求最大公约数
	//最小公倍数是两个正整数的乘积除以最大公约数
	//lcm = m * n;//假定最小公倍数即是两个正整数的乘积，后面再修改

	do {//辗转相除法
		r = m % n;//求余数
		m = n;//本次循环的除数n，赋给m，作为下一次循环作为被除数
		n = r;//本次循环的余数r，赋给n，作为下一次循环作为除数
	} while (r > 0);//余数r为0时的m值，即是最大公约数
	lcm = denominL / m;//m为最大公约数
	lcm = lcm * denominR;//lcm为最小共倍数
	return lcm;//
}

Fraction::Fraction(Ftype num) {
	numer_ = num;
}

Fraction::Fraction(double num) {
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

void Fraction::operator=(const Ftype num) {
	Fraction frac(num);
	*this = frac;
}

void Fraction::operator=(const double num) {
	Fraction frac(num);
	*this = frac;
}

Fraction Fraction::operator+(const Fraction& frac)const {
	Fraction fracThis = *this;
	fracThis.SetNumerator(fracThis.Numerator() * frac.Denominator()
		+ frac.Numerator() * fracThis.Denominator());//分子乘分母后相加
	fracThis.SetDenominator(fracThis.Denominator() * frac.Denominator());//分母相乘
	return fracThis;
}

Fraction Fraction::operator+(const Ftype num)const {
	return *this + Fraction(num);
}

Fraction Fraction::operator+(const double num)const {
	return *this + Fraction(num);
}

Fraction Fraction::operator-(const Fraction& frac)const {
	Fraction fracThis = *this;
	fracThis.SetNumerator(fracThis.Numerator() * frac.Denominator()
		- frac.Numerator() * fracThis.Denominator());//分子乘分母后相加
	fracThis.SetDenominator(fracThis.Denominator() * frac.Denominator());//分母相乘
	return fracThis;
}

Fraction Fraction::operator-(const Ftype num)const {
	return *this - Fraction(num);
}

Fraction Fraction::operator-(const double num)const {
	return *this - Fraction(num);
}

Fraction Fraction::operator*(const Fraction& frac)const {
	Fraction fracThis = *this;
	fracThis.SetNumerator(fracThis.Numerator() * frac.Numerator());//分子相乘
	fracThis.SetDenominator(fracThis.Denominator() * frac.Denominator());//分母相乘
	return fracThis;
}

Fraction Fraction::operator*(const Ftype num)const {
	return *this * Fraction(num);
}

Fraction Fraction::operator*(const double num)const {
	return *this * Fraction(num);
}

Fraction Fraction::operator/(const Fraction& frac)const {
	Fraction fracThis = *this;
	fracThis.SetNumerator(fracThis.Numerator() * frac.Denominator());//分子乘分母
	fracThis.SetDenominator(fracThis.Denominator() * frac.Numerator());//分母乘分子
	return fracThis;
}

Fraction Fraction::operator/(const Ftype num)const {
	return *this / Fraction(num);
}

Fraction Fraction::operator/(const double num)const {
	return *this / Fraction(num);
}

Fraction operator+(const Ftype num,const Fraction& frac) {
	return Fraction(num) + frac;
}

Fraction operator+(const double num, const Fraction& frac) {
	return Fraction(num) + frac;
}

Fraction operator-(const Ftype num, const Fraction& frac) {
	return Fraction(num) - frac;
}

Fraction operator-(const double num, const Fraction& frac) {
	return Fraction(num) - frac;
}

Fraction operator*(const Ftype num, const Fraction& frac) {
	return Fraction(num) * frac;
}

Fraction operator*(const double num, const Fraction& frac) {
	return Fraction(num) * frac;
}

Fraction operator/(const Ftype num, const Fraction& frac) {
	return Fraction(num) / frac;
}

Fraction operator/(const double num, const Fraction& frac) {
	return Fraction(num) / frac;
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

