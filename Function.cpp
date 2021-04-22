#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

int input();
bool process(int year);
void output(int year, bool result);
void pattern(int size);
void fun(int &y);
void swap(int& first, int& second);
bool isEven(int y);
double calEarning(double rate, double hours = 40);
int smaller(int a, int b);
void fun();
void process(double value, double rate, double term,
	double& multipler, double& futureValue);
void printResult(double multiplier, double futureValue);
void printData(double value, double rate, double term);
void output(double value, double rate, double term, double multiplier, double futureVlaue);
double findmultipler(double rate, double term); //�¼� ���
double getinput(string message); //�Է� �Լ�
void input(double& value, double& rate, double& term); //���� �ݾ�, ���� , ��� �Է�
int random(int high, int low);
int max(int num1, int num2, int num3);
int max(int num1, int num2, int num3, int num4);



int main()
{	
	int count = 0;
	int tmp;
	int same = 0;
	const int number = 6;
	int save[number];

	srand(time(NULL));

	while (count < number)
	{
		same = 0;
		tmp = rand() % 45 + 1;
		for (int i = 0; i < count; i++)
		{
			if (tmp == save[i])
			{
				same = 1;
				break;
			}
		}
		if (same == 0)
		{
			save[count] = tmp;
			count++;
		}
	}
	cout << "��÷ ����";
	for (int i = 0; i < number; i++)
	{
		cout << "  "<<save[i];
	}
		
}

bool isEven(int y)
{
	return((y % 2) == 0);
}

void pattern(int size)  //�簢�� ���� �Լ�
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	return;
}

int getdat() // ���� ���� �Է� �Լ�
{
	int data;

	do
	{
		cout << "���� ������ �Է��ϼ��� :";
		cin >> data;
	} while (data < 0);
	return data;
}

int larger(int a, int b) // ū �� ã�� �Լ�
{
	int big;

	if (a > b)
	{
		big = a;
	}
	else
	{
		big = b;
	}
	return big;
}

int smaller(int a, int b)
{
	int small;
	if (a < b)
	{
		small = a;
	}
	else
	{
		small = b;
	}
	return small;
}

int input() //���� �Է� �Լ�
{
	int year;
	do
	{
		cout << "1582�� ���ķ� �Է� :";
		cin >> year;
	} while (year <= 1582);
	return year;
}

bool process(int year) //���� �Ǻ� �Լ�
{
	bool criterial1 = (year % 4 == 0);
	bool criterial2 = (year % 100 != 0) || (year % 400 == 0);
	return (criterial1) && (criterial2);
}

void output(int year, bool result) //���� ��� �Լ�
{
	if (result)
	{
		cout << year << "���� �����Դϴ�";
	}
	else
	{
		cout << year << "���� ������ �ƴմϴ�.";
	}
}

void fun(int &y)
{
	y++;
	cout << "fun �Լ� ������ y= " << y << endl;
	return;

}
void swap(int& first, int& second)
{
	int temp = first;
	first = second;
	second = temp;
	return;
}


double calEarning(double rate, double hours) //�ӱ� ��� �Լ�
{
	double pay;
	pay = hours * rate;
	return pay;
}

int max(int num1, int num2, int num3)
{
	return larger(larger(num1, num2), num3);
}

int max(int num1, int num2, int num3, int num4)
{
	return max(max(4, 8, 2), 3);
}

void fun()
{
	int num = 3;
	static int count = 0; //���� ���� ���� ���� ���α׷� ������ �ʱ�ȭ
	num++;
	count++;
	cout << "num =  " << num << "count =  " << count << endl;
}

void input(double& value, double& rate, double& term) //���� �ݾ�, ���� , ��� �Է�
{
	value = getinput("���� �ݾ� �Է�");
	rate = getinput("���� �Է�");
	term = getinput("�ð� �Է�");
} 

double getinput(string message) //�Է� �Լ�
{
	double input;
	do
	{
		cout << message;
		cin >> input;
	} while (input < 0.0);
	return input;
}   

void process(double value, double rate, double term, //�̷���ġ ���
	double& multiplier, double& futureValue)
{
	multiplier = findmultipler(rate, term);
	futureValue = multiplier * value;
}

double findmultipler(double rate, double term) //�¼� ���
{
	double factor = 1 + rate / 100;
	return pow(factor, term);
}

void output(double value, double rate, double term, double multiplier, double futureVlaue)
{
	printData(value, rate, term);
	printResult(multiplier, futureVlaue);
}

void printData(double value, double rate, double term)
{
	cout << endl << "���� ����" << endl;
	cout << "���� �ݾ� : " << fixed << setprecision(2) << value << endl;
	cout << "���� : " << fixed << setprecision(2) << rate << endl;
	cout << "% ������ " << endl;
	cout << "���� �Ⱓ : " << term << "��" << endl << endl;
}

void printResult(double multiplier, double futureValue)
{
	cout << "������ �¼�" << fixed << setprecision(3);
	cout << multiplier << endl;
	cout << "�̷� ��ġ" << fixed << setprecision(3);
	cout << futureValue << endl;
}

	/*int zero_counter = 0; //����������
	int one_counter = 0;
	srand(time(NULL));
	for (int i = 1; i <= 1000000; i++)
	{
		if (rand() % 2 == 0)
		{
			zero_counter++;
		}
		else
		{
			one_counter++;
		}
	}
	cout << "0��" << zero_counter << "  1��" << one_counter;
	return 0;  */

//srand(time(NULL));
//for (int i = 1; i <= 10; i++) //���� �Ҽ� �̱�
//{
//	cout << rand() % 10 / 10.0 << endl;
//}

	/*int count = 0; //�ζ�
	int tmp;
	int same = 0;
	const int number = 6;
	int save[number];

	srand(time(NULL));

	while (count < number)
	{
		same = 0;
		tmp = rand() % 45 + 1;
		for (int i = 0; i < count; i++)
		{
			if (tmp == save[i])
			{
				same = 1;
				break;
			}
		}
		if (same == 0)
		{
			save[count] = tmp;
			count++;
		}
	}
	cout << "��÷ ����";
	for (int i = 0; i < number; i++)
	{
		cout << "  " << save[i];
	}*/

