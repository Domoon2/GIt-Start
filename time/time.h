#include <iostream>
//타임 클래스 인터페이스 파일
using namespace std;

#ifndef TIME_H
#define TIME_H

	class Time
{
private:
	int hours;
	int minutes;
	int seconds;
public:
	Time(int hours, int minutes, int seconds);
	Time();
	~Time();
	void print() const;
	void tick();
private:
	void normalize();
};
#endif // 

