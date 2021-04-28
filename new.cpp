#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp> //remap 함수 사용을 위해 

using namespace cv;
using namespace std;

void wave(const Mat& image, Mat& result); // 물결 효과 함수

Mat rotate(Mat src, double angle);


int main()

{
	int n = 128;
	int rot = 45;
	Mat img = imread("Lenna.png");
	
	Mat img_result;
	Mat img_result2;
	Mat img_result3;
	Mat img_result4;
	Mat img_result5;
	Mat img_result6;
	Mat roi = img.clone();

	Mat rec1 = roi(Rect(Point(0, 0), Point(n, n)));
	Mat rec2 = roi(Rect(Point(n, 0), Point(256, n)));
	Mat rec3 = roi(Rect(Point(2*n, 0), Point(3*n, n)));
	Mat rec4 = roi(Rect(Point(3 * n, 0), Point(4 * n, n)));

	Mat rec5 = roi(Rect(Point(0, n), Point(n, 2*n)));
	Mat rec6 = roi(Rect(Point(n, n), Point(2*n, 2*n)));
	Mat rec7 = roi(Rect(Point(2 * n, n), Point(3 * n, 2*n)));
	Mat rec8 = roi(Rect(Point(3 * n, n), Point(4 * n, 2*n)));

	Mat rec9 = roi(Rect(Point(0, 2*n), Point(n, 3 * n)));
	Mat rec10 = roi(Rect(Point(n, 2*n), Point(2 * n, 3 * n)));
	Mat rec11 = roi(Rect(Point(2 * n,2*n), Point(3 * n, 3 * n)));
	Mat rec12 = roi(Rect(Point(3 * n, 2*n), Point(4 * n, 3 * n)));

	Mat rec13 = roi(Rect(Point(0, 3 * n), Point(n, 4 * n)));
	Mat rec14 = roi(Rect(Point(n, 3 * n), Point(2 * n, 4 * n)));
	Mat rec15 = roi(Rect(Point(2 * n, 3 * n), Point(3 * n, 4 * n)));
	Mat rec16 = roi(Rect(Point(3 * n, 3 * n), Point(4 * n, 4 * n)));
	
	Mat rot1 = rotate(rec1, rot);
	Mat rot2 = rotate(rec2, rot);
	Mat rot3 = rotate(rec3, rot);
	Mat rot4 = rotate(rec4, rot);

	Mat rot5 = rotate(rec5, rot);
	Mat rot6 = rotate(rec6, rot);
	Mat rot7 = rotate(rec7, rot);
	Mat rot8 = rotate(rec8, rot);

	Mat rot9 = rotate(rec9, rot);
	Mat rot10 = rotate(rec10, rot);
	Mat rot11 = rotate(rec11, rot);
	Mat rot12 = rotate(rec12, rot);

	Mat rot13 = rotate(rec13, rot);
	Mat rot14 = rotate(rec14, rot);
	Mat rot15 = rotate(rec15, rot);
	Mat rot16 = rotate(rec16, rot);

	hconcat(rot1, rot2, img_result);
	hconcat(img_result, rot3, img_result);
	hconcat(img_result, rot4, img_result);

	hconcat(rot5, rot6, img_result2);
	hconcat(img_result2, rot7, img_result2);
	hconcat(img_result2, rot8, img_result2);

	hconcat(rot9, rot10, img_result3);
	hconcat(img_result3, rot11, img_result3);
	hconcat(img_result3, rot12, img_result3);

	hconcat(rot13, rot14, img_result4);
	hconcat(img_result4, rot15, img_result4);
	hconcat(img_result4, rot16, img_result4);

	vconcat(img_result, img_result2, img_result5);
	vconcat(img_result3, img_result4, img_result6);
	vconcat(img_result5, img_result6, img_result);

	//vconcat(img_result, img_result2,img_result3);

	imshow("3", img_result);

	waitKey(0);
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
			X.at <float > (i, j) = j;
			Y.at<float>(i, j) = i + 10 *sin(j / 10.0); //곡선에 따라 이동
		}
	}

	// 매핑 적용
	remap(image, result, X, Y, INTER_LINEAR);
}
Mat rotate(Mat src, double angle)
{
	Mat dst;
	Point2f pt(src.cols / 2.0, src.rows / 2.0);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, Size(src.cols, src.rows));
	return dst;
}


