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
double findmultipler(double rate, double term); //승수 계산
double getinput(string message); //입력 함수
void input(double& value, double& rate, double& term); //투자 금액, 이율 , 년수 입력
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
	cout << "추첨 숫자";
	for (int i = 0; i < number; i++)
	{
		cout << "  "<<save[i];
	}
		
}

bool isEven(int y)
{
	return((y % 2) == 0);
}

void pattern(int size)  //사각형 패턴 함수
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

int getdat() // 양의 정수 입력 함수
{
	int data;

	do
	{
		cout << "양의 정수를 입력하세요 :";
		cin >> data;
	} while (data < 0);
	return data;
}

int larger(int a, int b) // 큰 수 찾기 함수
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

int input() //윤년 입력 함수
{
	int year;
	do
	{
		cout << "1582년 이후로 입력 :";
		cin >> year;
	} while (year <= 1582);
	return year;
}

bool process(int year) //윤년 판별 함수
{
	bool criterial1 = (year % 4 == 0);
	bool criterial2 = (year % 100 != 0) || (year % 400 == 0);
	return (criterial1) && (criterial2);
}

void output(int year, bool result) //윤년 출력 함수
{
	if (result)
	{
		cout << year << "년은 윤년입니다";
	}
	else
	{
		cout << year << "년은 윤년이 아닙니다.";
	}
}

void fun(int &y)
{
	y++;
	cout << "fun 함수 내부의 y= " << y << endl;
	return;

}
void swap(int& first, int& second)
{
	int temp = first;
	first = second;
	second = temp;
	return;
}


double calEarning(double rate, double hours) //임금 계산 함수
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
	static int count = 0; //정적 지역 변수 선언 프로그램 끝나야 초기화
	num++;
	count++;
	cout << "num =  " << num << "count =  " << count << endl;
}

void input(double& value, double& rate, double& term) //투자 금액, 이율 , 년수 입력
{
	value = getinput("투자 금액 입력");
	rate = getinput("이율 입력");
	term = getinput("시간 입력");
} 

double getinput(string message) //입력 함수
{
	double input;
	do
	{
		cout << message;
		cin >> input;
	} while (input < 0.0);
	return input;
}   

void process(double value, double rate, double term, //미래가치 계산
	double& multiplier, double& futureValue)
{
	multiplier = findmultipler(rate, term);
	futureValue = multiplier * value;
}

double findmultipler(double rate, double term) //승수 계산
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
	cout << endl << "투자 정보" << endl;
	cout << "투자 금액 : " << fixed << setprecision(2) << value << endl;
	cout << "이율 : " << fixed << setprecision(2) << rate << endl;
	cout << "% 연마다 " << endl;
	cout << "투자 기간 : " << term << "년" << endl << endl;
}

void printResult(double multiplier, double futureValue)
{
	cout << "투자의 승수" << fixed << setprecision(3);
	cout << multiplier << endl;
	cout << "미래 가치" << fixed << setprecision(3);
	cout << futureValue << endl;
}

	/*int zero_counter = 0; //동전던지기
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
	cout << "0은" << zero_counter << "  1은" << one_counter;
	return 0;  */

//srand(time(NULL));
//for (int i = 1; i <= 10; i++) //랜덤 소수 뽑기
//{
//	cout << rand() % 10 / 10.0 << endl;
//}

	/*int count = 0; //로또
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
	cout << "추첨 숫자";
	for (int i = 0; i < number; i++)
	{
		cout << "  " << save[i];
	}*/

