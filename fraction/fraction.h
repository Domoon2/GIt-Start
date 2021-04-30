#include <iostream>


using namespace std;

#ifndef  FRACTION_H
#define FRACTION_H

class Fraction
{
private:
	int numer;
	int denom;
public:
	Fraction(int num, int den);
	Fraction();
	Fraction(const Fraction& fract);
	~Fraction();

	//접근자
	int getNumer() const;
	int getDenom() const;
	void print() const;

	//설정자
	void setNumer(int num);
	void setDenom(int den);

private:
	void normalize();
	int gcd(int n, int m);
};

#endif // ! FRACTION_H

