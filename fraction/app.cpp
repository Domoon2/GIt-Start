#include "fraction.h"
#include <iostream>
using namespace std;

int main()
{
	Fraction fract1;
	Fraction fract2(14, 21);
	Fraction fract3(11, -8);
	Fraction fract4(fract3);

	cout << "생성한 분수 4개를 출력합니다." << endl;
	cout << "fract1:";
	fract1.print();
	cout << "fract2 :";
	fract2.print();
	cout << "fract3 :";
	fract3.print();
	cout << "fract4 :";
	fract4.print();

	cout << "분수 변경 후 출력" << endl;
	fract1.setNumer(4);
	cout << "fract1 :";
	fract1.print();
	fract2.setDenom(5);
	cout << "fract2 :";
	fract2.print();
	cout << "접근자로 분자와 분모 따로 확인" << endl;
	cout << "fract1의 분자 :" << fract1.getNumer() << endl;
	cout << "fract2의 분자 :" << fract2.getNumer() << endl;
	return 0;
}