#include <iostream>
#include <cmath>
#include <cassert>>
#include "fraction.h"

using namespace std;

Fraction::Fraction(int num, int den = 1)
	:numer(num), denom(den)
{
	normalize();
}
Fraction::Fraction()
	: numer(0), denom(1)
{
}
Fraction::Fraction(const Fraction& fract)
	: numer(fract.numer), denom(fract.denom)
{

}
Fraction::~Fraction()
{

}
int Fraction::getNumer() const
{
	return numer;
}
int Fraction::getDenom()const
{
	return denom;
}
void Fraction::print() const
{
	cout << numer << "/" << denom << endl;
}
void Fraction::setNumer(int num)
{
	numer = num;
	normalize();
}
void Fraction::setDenom(int den)
{
	denom = den;
	normalize();
}
void Fraction::normalize()
{
	//분모가 0인 경우
	if (denom == 0)
	{
		cout << "잘못된 분모 값입니다. 프로그랩을 중단합니다" << endl;
		assert(false);
	}
	if (denom < 0)
	{
		denom = -denom;
		numer = -numer;
	}
	int divisor = gcd(abs(numer), abs(denom));
	numer = numer / divisor;
	denom = denom / divisor;
}
int Fraction::gcd(int n, int m)
{
	int gcd = 1;
	for (int k = 1; k <= n && k <= m; k++)
	{
		if (n % k == 0 && m % k == 0)
		{
			gcd = k;
		}
	}
	return gcd;
}