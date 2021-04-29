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
	static int base;  //���� ������ ���
public:
	Account(double bal); //������
	~Account(); //�Ҹ���
	void checkBalance() const; //������
	void deposit(double amount); //������
	void withdraw(double amount); //������
};

int Account::base = 0; //���� ������ ��� �ʱ�ȭ


//�Ű����� �ִ� ������
Account::Account(double bal)
:balance(bal)
{
	if (bal < 0.0)
	{
		cout<<"�ܾ��� ���� �� �ȴ� ���̸� ���� ��";
		assert(false);
	}
	base++;
	accNumber = 10000 + base;

	cout << "���� " << accNumber << "����������ϴ�." << endl;
	cout << "�ܾ� " << balance << "����������ϴ�." << endl << endl;
}
Account::~Account()
{
	cout << "����" << accNumber << "�� �������ϴ�" << endl;
	cout << "$" << balance << "�� ������ ���½��ϴ�" << endl << endl;
}
void Account::checkBalance() const
{
	cout << "����" << accNumber << endl;
	cout << "Ʈ����� - �ܾ� Ȯ��" << endl;
	cout << "�ܾ� : " << balance << endl << endl;
}

void Account::deposit(double amount)
{
	if (amount > 0.0)
	{
		balance += amount;
		cout << "����" << accNumber << endl;
		cout << "Ʈ����� : deposit of " << amount << endl;
		cout << "����� �ܾ�" << balance << endl << endl;
	}
	else
	{
		cout << "Ʈ����� �ߴ�" << endl;
	}
}
void Account::withdraw(double amount)
{
	if (amount > balance)
	{
		amount = balance;
	}

	balance -= amount;
	cout << "����" << accNumber << endl;
	cout << "Ʈ�����  - ����: deposit of " << amount << endl;
	cout << "����� �ܾ�" << balance << endl << endl;
}

int main()
{
	//���� 3�� ����
	Account acc1(2000);
	Account acc2(5000);
	Account acc3(1000);

	//Ʈ�����
	acc1.deposit(150);
	acc2.checkBalance();
	acc1.checkBalance();
	acc3.withdraw(800);
	acc1.withdraw(1000);
	acc2.deposit(120);
	return 0;
}