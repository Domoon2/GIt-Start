#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

class Rect  //�簢�� ���
{
private:
	double width; //������ ���
	double height;
public:
	Rect(double width, double height); //�Ű������� �ִ� ������
	Rect(); //�⺻ ������
	~Rect(); //�Ҹ���
	Rect(const Rect& rect);
	double getWidth() const; //������
	double getHeight() const;
	double getPerimeter() const;
	double getArea() const;
	void setWidth(double value); //������
	void setHeight(double value);
}; 
Rect::Rect(double wid, double hei)
	:width(wid),height(hei)
{
	cout << "�Ű������� �ִ� �����ڰ� ȣ�� ��" << endl;
}
Rect::Rect()
	: width(5.5), height(5)
{
	cout << "�⺻ ������ ȣ��" << endl;
}
Rect::Rect(const Rect& rect)
	: width(rect.width), height(rect.height)
{
	cout << "���� ������ ȣ��" << endl;
}
Rect::~Rect()
{
	cout << "�Ҹ��� ȣ��" << width << height;
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
int main()
{
	Rect rect1;
	rect1.setHeight(5);
	rect1.setWidth(5);
	cout << "���� :" << rect1.getHeight()<<endl;
	cout << "����" << rect1.getWidth() << endl;
	cout << "����" << rect1.getArea() << endl;
	cout << "�ѷ�" << rect1.getPerimeter() << endl;

	Rect rect2(5, 4);
	
		cout << "width" << rect2.getWidth() << endl;
		cout << "height" << rect2.getHeight() << endl;
		cout << "height" << rect2.getArea() << endl;
		cout << "height" << rect2.getPerimeter() << endl;
	
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

	return 0;
}