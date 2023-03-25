#ifndef FRACTIONAL_H_
#define FRACTIONAL_H_
//�����ࣺ�÷�������С�����м��㣬����С�����18λ�ľ���
//������ľ��Ƚ�����double������λ�������ڴ��Сȴ���˱��������޷���doubleһ���洢����
//��ô�ұ�д�������������ڣ�
//�ұ�д�����������Ҫ��һ����Ϊ���ܹ��õ����µ����֣�
//����Ҫ��������10.0������9.9999999999999999999999999999999
//��Ҳ���뿴��������һ��0.0000000000000000001��Ϊ��һ��������˵õ���0.1������Ӱ����ֵ��������

#include<iostream>
using namespace std;

#define FRACTIONAL_PERCISION_LIMIT (1E18)
typedef long long Ftype;

class Fraction {
private:
	Ftype numer_ = 0;//����
	Ftype denomin_ = 1;//��ĸ
	void __fraction_simplify(void);//����Լ��
	Ftype __least_common_multiple(const Ftype,const Ftype);//��С������

public:
	Fraction() {}
	~Fraction() {}
	Fraction(Ftype num);//int����ֵת��Ϊ����
	Fraction(double num);//double����ֵת��Ϊ����
	Fraction(Ftype numer, Ftype denomin);//���������湹������

	void SetNumerator(const Ftype);//���÷���
	void SetDenominator(const Ftype);//���÷�ĸ
	Ftype Denominator(void)const;//���ط�ĸ
	Ftype Numerator(void)const;//���ط���
	Ftype Int64(void)const;//����int���ķ���
	double Double(void)const;//����double���ķ���
	
	void operator=(const Fraction&);
	void operator=(const Ftype);
	void operator=(const double);
	Fraction operator+(const Fraction&)const;
	Fraction operator+(const Ftype)const;
	Fraction operator+(const double)const;
	Fraction operator-(const Fraction&)const;
	Fraction operator-(const Ftype)const;
	Fraction operator-(const double)const;
	Fraction operator*(const Fraction&)const;
	Fraction operator*(const Ftype)const;
	Fraction operator*(const double)const;
	Fraction operator/(const Fraction&)const;
	Fraction operator/(const Ftype)const;
	Fraction operator/(const double)const;
	
	friend Fraction operator+(const Ftype,const Fraction&);
	friend Fraction operator+(const double, const Fraction&);
	friend Fraction operator-(const Ftype, const Fraction&);
	friend Fraction operator-(const double, const Fraction&);
	friend Fraction operator*(const Ftype, const Fraction&);
	friend Fraction operator*(const double, const Fraction&);
	friend Fraction operator/(const Ftype, const Fraction&);
	friend Fraction operator/(const double, const Fraction&);

	friend ostream& operator<<(ostream&, const Fraction&);
};

#endif