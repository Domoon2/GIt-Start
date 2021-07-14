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
		cout << "좌표 " << " " << x << " " << y << endl;
	}
}
void displayDFT(Mat& src)
{
	Mat image_array[2] = { Mat::zeros(src.size(), CV_32F),
												Mat::zeros(src.size(),CV_32F) };

	split(src, image_array);  // dft 영상을 2개의 영상으로 분리

	Mat mag_image;
	// 푸리에 변환 계수들의 절대값 계산
	magnitude(image_array[0], image_array[1], mag_image);

	//푸리에 변환 계수들은 크기때문에 로그 스케일로 변환 0이 안나오게 1을 더함
	mag_image += Scalar::all(1);
	log(mag_image, mag_image);
	//0에서 255 범위로 정규화함 

	normalize(mag_image, mag_image, 0, 1, NORM_MINMAX);
	imshow("DFT", mag_image);
	waitKey(0);
}
int main() {

	Mat img = imread("Lenna.png", IMREAD_GRAYSCALE);

	Mat img_float;
	Mat dft_image;

	img.convertTo(img_float, CV_32FC1, 1.0 / 255.0);

	dft(img_float, dft_image, DFT_COMPLEX_OUTPUT);
	imshow("float", img_float);
	displayDFT(dft_image);
	return 1;
}
  