#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class RandomInteger
{
private:
	int low;
	int high;
	int value;
public:
	RandomInteger(int low, int high); //»ı¼ºÀÚ
	~RandomInteger(); //¼Ò¸êÀÚ

	RandomInteger(const RandomInteger& random) = delete;
	void print() const;
};

RandomInteger::RandomInteger(int lw, int hh)
:low(lw), high(hh)
{
	srand(time(0));
	int temp = rand();
	value = temp % (high - low + 1) + low;
}
RandomInteger::~RandomInteger()
{

}
void RandomInteger::print() const
{
	cout << value << endl;
}

int main()
{
	RandomInteger r1(150, 300);
	cout << "150~300 ·£´ı ¼ıÀÚ :";
	r1.print();

	RandomInteger r2(150, 3000);
	cout << "0~3000 ·£´ı ¼ıÀÚ";
	r2.print();

	return 0;
}