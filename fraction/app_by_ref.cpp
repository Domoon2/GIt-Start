#include "fraction.h"
#include <iostream>
using namespace std;

Fraction& larger(Fraction&, Fraction&); //프로토타입

int main()
{
	Fraction fract1(3, 13);
	Fraction fract2(5, 17);
	cout << "첫 번째 쌍에서 더 큰 분수 :";
	larger(fract1, fract2).print();

	Fraction fract3(4, 9);
	Fraction fract4(1, 6);
	cout << "두 번째 쌍에서 더 큰 분수 : ";
	larger(fract3, fract4).print();
	return 0;
}

Fraction& larger(Fraction& fract1, Fraction& fract2)
{
	if (fract1.getNumer() * fract2.getDenom() >
		fract2.getNumer() * fract2.getDenom())
	{
		return fract1;
	}
	return fract2;
}
