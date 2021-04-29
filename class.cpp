#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cassert>

using namespace std;

class Rect  //사각형 헤더
{
private:
	double width; //데이터 멤버
	double height;
	static int count; //정적 데이터 멤버
public:
	Rect(double width, double height); //매개변수가 있는 생성자
	Rect(); //기본 생성자
	~Rect(); //소멸자
	Rect(const Rect& rect);
	double getWidth() const; //접근자
	double getHeight() const;
	double getPerimeter() const;
	double getArea() const;
	void setWidth(double value); //설정자
	void setHeight(double value);
	static int getCount();
};
int Rect::count = 0;
Rect::Rect(double wid, double hei)
	:width(wid), height(hei)
{
	if ((wid <= 0.0) || (hei <= 0.0))
	{
		cout << "Rect 객체를 생성할수 없다" << endl;
		assert(false);
	}
	count++;
	cout << "매개변수가 있는 생성자가 호출 됨" << endl;
}
Rect::Rect()
	: width(5.5), height(5)
{
	count++;
	cout << "기본 생성자 호출" << endl;
}
Rect::Rect(const Rect& rect)
	: width(rect.width), height(rect.height)
{
	count++;
	cout << "복사 생성자 호출" << endl;
}
Rect::~Rect()
{
	count--;
	cout << "소멸자 호출" << width << height;
	cout << endl;
}

double Rect::getWidth() const
{
	return width;
}
double Rect::getHeight() const
{
	return height;
}
double Rect::getPerimeter() const
{
	return 2 * width + 2 * height;
}
double Rect::getArea() const
{
	return width * height;
}
void Rect::setHeight(double value)
{
	height = value;
}
void Rect::setWidth(double value)
{
	width = value;
}
int Rect::getCount()
{
	return count;
}
int main()
{

	{
		Rect rect1(3.2, 1.2);
		Rect rect2(3.5, 1.5);
		Rect rect3;
		Rect rect4(rect1);
		Rect rect5(rect2);
		cout << "객체의 수" << rect5.getCount() << endl;
	}
	cout << "객체의 수" << Rect::getCount() << endl;
	return 0;
	/*Rect rect1;
	rect1.setHeight(5);
	rect1.setWidth(5);
	cout << "높이 :" << rect1.getHeight() << endl;
	cout << "가로" << rect1.getWidth() << endl;
	cout << "넓이" << rect1.getArea() << endl;
	cout << "둘레" << rect1.getPerimeter() << endl;

	Rect rect2(5, 4);

	cout << "width" << rect2.getWidth() << endl;
	cout << "height" << rect2.getHeight() << endl;
	cout << "height" << rect2.getArea() << endl;
	cout << "height" << rect2.getPerimeter() << endl;
	cout <<"객체의 수"<< rect2.getCount() << endl;

	Rect rect3;
	cout << "width" << rect3.getWidth() << endl;
	cout << "height" << rect3.getHeight() << endl;
	cout << "height" << rect3.getArea() << endl;
	cout << "height" << rect3.getPerimeter() << endl;

	Rect rect4(rect1);
	cout << "width" << rect4.getWidth() << endl;
	cout << "height" << rect4.getHeight() << endl;
	cout << "height" << rect4.getArea() << endl;
	cout << "height" << rect4.getPerimeter() << endl;

	cout << "객체의 수 " << Rect::getCount() << endl;*/

}
