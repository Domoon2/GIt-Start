#include "fraction.h"
#include <iostream>
using namespace std;

int main()
{
	Fraction fract1;
	Fraction fract2(14, 21);
	Fraction fract3(11, -8);
	Fraction fract4(fract3);

	cout << "������ �м� 4���� ����մϴ�." << endl;
	cout << "fract1:";
	fract1.print();
	cout << "fract2 :";
	fract2.print();
	cout << "fract3 :";
	fract3.print();
	cout << "fract4 :";
	fract4.print();

	cout << "�м� ���� �� ���" << endl;
	fract1.setNumer(4);
	cout << "fract1 :";
	fract1.print();
	fract2.setDenom(5);
	cout << "fract2 :";
	fract2.print();
	cout << "�����ڷ� ���ڿ� �и� ���� Ȯ��" << endl;
	cout << "fract1�� ���� :" << fract1.getNumer() << endl;
	cout << "fract2�� ���� :" << fract2.getNumer() << endl;
	return 0;
}