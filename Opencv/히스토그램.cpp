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
Mat src, src_gray, dst;
int threshold_value = 0;
int threshold_type = 0;

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


void Threshold_Demo(int, void*)
{
	threshold(src_gray, dst, threshold_value, 255, threshold_type);
	imshow("???? ????", dst);
}
void reduceColorAt(Mat& input, uchar table[])
{
	for (int i = 0; i < input.rows; ++i)
	{
		for (int j = 0; j < input.cols; ++j)
		{
			input.at<uchar>(i, j) = table[input.at<uchar>(i, j)];
		}
	}
}

void drawHist(int histogram[])
{
	int hist_w = 512; //???????׷? ??
	int hist_h =400; // ???????׷? ????
	int bin_w = cvRound((double)hist_w / 256); //???? ??

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	int max = histogram[0];
	for (int i = 1; i < 256; i++)
	{
		if (max < histogram[i])
		{
			max = histogram[i];
		}
	}
	for (int i = 0; i < 255; i++)
	{
		histogram[i] = floor(((double)histogram[i] / max) * histImage.rows);
	}
	for (int i = 0; i < 255; i++)
	{
		line(histImage, Point(bin_w * (i), hist_h),
			Point(bin_w * (i), hist_h - histogram[i]),
			Scalar(0, 0, 255));
	}
	imshow("Histogram", histImage);
}

int main()
{
	Mat src = imread("Lenna.png",IMREAD_GRAYSCALE);
	imshow("input img", src);

	int histogram[256] = { 0 };

	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			histogram[(int)src.at<uchar>(y, x)]++;
		}
	}
	drawHist(histogram);
	waitKey(0);

	return 0;
} 