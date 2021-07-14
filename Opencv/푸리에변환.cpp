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
		cout << "��ǥ " << " " << x << " " << y << endl;
	}
}
void displayDFT(Mat& src)
{
	Mat image_array[2] = { Mat::zeros(src.size(), CV_32F),
												Mat::zeros(src.size(),CV_32F) };

	split(src, image_array);  // dft ������ 2���� �������� �и�

	Mat mag_image;
	// Ǫ���� ��ȯ ������� ���밪 ���
	magnitude(image_array[0], image_array[1], mag_image);

	//Ǫ���� ��ȯ ������� ũ�⶧���� �α� �����Ϸ� ��ȯ 0�� �ȳ����� 1�� ����
	mag_image += Scalar::all(1);
	log(mag_image, mag_image);
	//0���� 255 ������ ����ȭ�� 

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
  