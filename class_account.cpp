#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cassert>

using namespace std;

class Account
{
private:
	long accNumber;
	double balance;
	static int base;  //정적 데이터 멤버
public:
	Account(double bal); //생성자
	~Account(); //소멸자
	void checkBalance() const; //접근자
	void deposit(double amount); //설정자
	void withdraw(double amount); //설정자
};

int Account::base = 0; //정적 데이터 멤버 초기화


//매개변수 있는 생성자
Account::Account(double bal)
:balance(bal)
{
	if (bal < 0.0)
	{
		cout<<"잔액은 음수 안 된다 빚이면 가능 ㅋ";
		assert(false);
	}
	base++;
	accNumber = 10000 + base;

	cout << "계좌 " << accNumber << "만들어졌습니다." << endl;
	cout << "잔액 " << balance << "만들어졌습니다." << endl << endl;
}
Account::~Account()
{
	cout << "계좌" << accNumber << "가 닫혔습니다" << endl;
	cout << "$" << balance << "를 고객에게 보냈습니다" << endl << endl;
}
void Account::checkBalance() const
{
	cout << "계좌" << accNumber << endl;
	cout << "트랙잭션 - 잔액 확인" << endl;
	cout << "잔액 : " << balance << endl << endl;
}

void Account::deposit(double amount)
{
	if (amount > 0.0)
	{
		balance += amount;
		cout << "계좌" << accNumber << endl;
		cout << "트랜잭션 : deposit of " << amount << endl;
		cout << "변경된 잔액" << balance << endl << endl;
	}
	else
	{
		cout << "트랜잭션 중단" << endl;
	}
}
void Account::withdraw(double amount)
{
	if (amount > balance)
	{
		amount = balance;
	}

	balance -= amount;
	cout << "계좌" << accNumber << endl;
	cout << "트랜잭션  - 인출: deposit of " << amount << endl;
	cout << "변경된 잔액" << balance << endl << endl;
}

int main()
{
	//계좌 3개 생성
	Account acc1(2000);
	Account acc2(5000);
	Account acc3(1000);

	//트랜잭션
	acc1.deposit(150);
	acc2.checkBalance();
	acc1.checkBalance();
	acc3.withdraw(800);
	acc1.withdraw(1000);
	acc2.deposit(120);
	return 0;
}