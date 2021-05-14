#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;
Mat img = imread("Lenna.png");
int drawing = false;
int red, green, blue;
void on_trackbar(int, void*) {}

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
void drawCircle(int event, int x, int y, int, void* param)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		drawing = true;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		if (drawing == true)
		{
			circle(img, Point(x, y), 3, Scalar(blue, green, red), 10);
		}
	}
	else if (event == EVENT_LBUTTONUP)
	{
		drawing = false;
		imshow("img", img);
	}
}
void sub(Mat img)
{
	img = Scalar(0, 0, 0);
}

int main()
{
	Mat img1 = imread("Lenna.png");
	Mat img2 = imread("suhwa512.png");

	imshow("original", img1);

	img1.push_back(img2);

	imshow("rev", img1);

	waitKey(0);
	return 0;
}