#include <iostream>
#include <cmath>
#include "time.h"

using namespace std;

int main()
{
	Time time(4, 5, 27);

	cout << "���� �ð� :";
	time.print();

	for (int i = 0; i < 143500; i++)
	{
		time.tick();
	}
	cout << "�ð��� ������:";
	time.print();
	return 0;
}