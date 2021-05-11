#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_LBUTTONDOWN) 
	{
		Mat& img = *(Mat*)(param);
		circle(img, Point(x, y), 200, Scalar(0, 255, 0), 10);
		putText(img, "I found part", Point(x, y + 200), FONT_HERSHEY_COMPLEX, 2.0, 255, 2);
		imshow("src", img);
	}
	else if (event == EVENT_RBUTTONDOWN) {}
	else if (event == EVENT_MBUTTONDOWN) {}
	else if (event == EVENT_MOUSEMOVE) {}
}

int main()
{
	Mat img = imread("Lenna.png");
	if (img.empty())
	{
		cout << "¸ø ÀÐ¾î" << endl;
	}
	imshow("img", img);
	int x = 300;
	int y = 300;
	while (1)
	{
		int key = waitKey(100);
		if (key == 'q')
		{
			break;
		}
		else if (key == 'a')
		{
			x -= 10;
		}
		else if (key == 'd')
		{
			x += 10;
		}
		else if (key == 's')
		{
			y -= 10;
		}
		else if (key == 'w')
		{
			y += 10;
		}
		circle(img, Point(x, y), 200, Scalar(0, 100, 0), 5);
		imshow("img", img);
	}
	return 0;
}
	