#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

bool mouse_pressing = false;
int start_x = 1, start_y = -1;
Mat img_color;

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
	Mat img_result = img_color.clone();

	if (event == EVENT_LBUTTONDOWN)
	{
		mouse_pressing = true;
		start_x = x;
		start_y = y;

		circle(img_result, Point(x, y), 10, Scalar(0, 255, 0), -1);
		imshow("img_color", img_result);
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (mouse_pressing) {
			rectangle(img_result, Point(start_x, start_y), Point(x, y), Scalar(0, 255, 0), 3);
			imshow("img_color", img_result);
		}
	}
	else if (event == EVENT_LBUTTONUP) {
		mouse_pressing = false;

		Mat img_Lenna(img_color, Rect(start_x, start_y, x - start_x, y - start_y));
		cvtColor(img_Lenna, img_Lenna, COLOR_BGR2GRAY);
		cvtColor(img_Lenna, img_Lenna, COLOR_GRAY2BGR);

		img_Lenna.copyTo(img_result(Rect(start_x, start_y, x - start_x, y - start_y)));
		imshow("img_color", img_result);

		/*imshow("img_Lenna", img_Lenna);
		imshow("img_color", img_result);*/
	}
}

Mat rotate(Mat src, double angle)
{
	Mat dst;
	Point2f pt(src.cols / 2.0, src.rows / 2.0);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, Size(src.cols, src.rows));
	return dst;
}

int main()
{
	img_color = imread("Lenna.png", IMREAD_COLOR);
	
	imshow("img_color", img_color);
	setMouseCallback("img_color", mouse_callback);
	
	
		
    waitKey(0);
	destroyAllWindows();
}