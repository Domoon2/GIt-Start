#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp> //remap 함수 사용을 위해 

using namespace cv;
using namespace std;

void wave(const cv::Mat& image, cv::Mat& result); // 물결 효과 함수

void flip(const cv::Mat& image, cv::Mat& result); // 좌우반전 함수


int main()

{
	Mat img = cv::imread("Lenna.png");


	Mat wave_img;

	wave_img.create(img.rows, img.cols, img.type());

	wave(img, wave_img); // 물결 효과

	imshow("물결", wave_img);

	waitKey(0);

	return 0;

}

void wave(const Mat& image, Mat& result) // 물결 효과 함수

{

	// 맵 역할

	Mat X(image.rows, image.cols, CV_32F);

	Mat Y(image.rows, image.cols, CV_32F);

	// 매핑 생성

	for (int i = 0; i < image.rows; i++)

	{
		for (int j = 0; j < image.cols; j++)
		{		
			X.at<float>(i, j) = j; 
			Y.at<float>(i, j) = i + 10 * sin(j / 5.0);  //사인 곡선에 따라 이동
		}
	}

	// 매핑 적용
	remap(image, result, X, Y, INTER_LINEAR);
}



//void flip(const cv::Mat& image, cv::Mat& result) // 좌우 반전 함수
//
//{
//
//	// 맵 역할
//
//	cv::Mat srcX(image.rows, image.cols, CV_32F);
//
//	cv::Mat srcY(image.rows, image.cols, CV_32F);
//
//
//
//	// 매핑 생성
//
//	for (int i = 0; i < image.rows; i++)
//
//	{
//
//		for (int j = 0; j < image.cols; j++)
//
//		{
//
//			// 화소 (i, j)의 새로운 위치
//
//			srcX.at<float>(i, j) = image.cols - j - 1; // 열은 좌우가 바뀜 ex) 1번째 열은 마지막 열로, 2번째 열은 (마지막-1)열로,..., 마지막 열은 1번째 열로.
//
//			srcY.at<float>(i, j) = i; // 행은 그대로 유지
//
//		}
//
//	}
//
//	// 매핑 적용
//
//	remap(image, result, srcX, srcY, cv::INTER_LINEAR);
//
//}