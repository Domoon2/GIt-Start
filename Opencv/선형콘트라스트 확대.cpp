#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;
int drawing = false;
int red, green, blue;
void on_trackbar(int, void*) {}
Mat img = imread("Lenna.png",IMREAD_GRAYSCALE);

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

void brighten(Mat& img, int value)
{
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; ++c)
			img.at<uchar>(r, c) = saturate_cast<uchar>(img.at<uchar>(r, c) + value);
	}
}

int contrastEnh(int input, int x1, int y1, int x2, int y2)
{
	double output;
	if (0 <= input && input <= x1)
	{
		output = y1 / x1 * input;
	}
	else if (x1 < input && input <= x2)
	{
		output = ((y2 - y1) / (x2 - x1)) * (input - x1) + y1;
	}
	else if (x2 < input && input <= 255)
	{
		output = ((255 - 62) / (255 - x2)) * (input - x2) + y2;
	}
	return (int)output;
}

int main()
{
	Mat img = imread("Lenna.png");
	Mat oimg = img.clone();

	int x1, x2, y1, y2;
	cout << "x1 값 입력 : "; cin >> x1;
	cout << "x2 값 입력 : "; cin >> x2;
	cout << "y1 값 입력 : "; cin >> y1;
	cout << "y2 값 입력 : "; cin >> y2;

	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			for (int ch = 0; ch < 3; ch++)
			{
				int output = contrastEnh(img.at<Vec3b>(r, c)[ch], x1, y1, x2, y2);
				oimg.at<Vec3b>(r, c)[ch] = saturate_cast<uchar>(output);
			}
		}
	}
	imshow("Original img", img);
	imshow("New img", oimg);
	waitKey(0);
	return 0;
}