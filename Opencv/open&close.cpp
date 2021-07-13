#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

void on_mouse(int event, int x, int y, int flags, void*)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "ÁÂÇ¥ " << " " << x << " " << y << endl;
	}
}
int main() {

	Mat input_img = (Mat_<uchar>(8,8) <<
		0,0,0,0,0,255,0,0,
		0,255,255,255,0,0,0,0,
		0,255,255,255,0,0,255,255,
		0,255,255,255,0,255,255,255,
		255,255,255,0,0,255,255,255,
		0,0,0,0,255,255,255,255,
		0,0,0,0,255,255,255,0,
		0, 0, 0, 0, 0, 0, 0, 0);
	Mat kernel = (Mat_<int>(3, 3) <<
		1, 1, 1,
		1, 1, 1,
		1, 1, 1);
	Mat output_img;

	morphologyEx(input_img, output_img, MORPH_CLOSE, kernel);
	const int rate = 50;
	resize(input_img, input_img, Size(), rate, rate, INTER_NEAREST);
	imshow("Original", input_img);
	resize(output_img, output_img, Size(), rate, rate, INTER_NEAREST);
	imshow("Close", output_img);
	waitKey(0);
	return 0;

}

  