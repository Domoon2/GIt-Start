#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


using namespace cv;
using namespace std;
Mat rotate(Mat src, double angle);


int main()
{

    Mat image = imread("Lenna.png");
    Mat reduce_img;
    Mat big_img;
    Mat rect_img;


    resize(image, big_img, Size(1000, 1000));


    int x1 = -64;
    int x2 = 0;
    int y1 = -64;
    int y2 = 0;
    int number;
    int plus = 64;
	int rows = image.rows;
	int cols = image.cols;
	Mat dst = image.clone();
	cin >> number;
	
	switch (number)
	{
	case 1: x1 += plus, x2 += plus, y1 += plus, y2 += plus;
		break;
	case 2: x1 += 2 * plus, x2 += 2 * plus, y1 += 2 * plus, y2 += 2 * plus;
		break;
	case 3: x1 += 3 * plus, x2 += 3 * plus, y1 += 3 * plus, y2 += 3 * plus;
		break;
	case 4: x1 += 4 * plus, x2 += 4 * plus, y1 += 4 * plus, y2 += 4 * plus;
		break;
	case 5: x1 += 5 * plus, x2 += 5 * plus, y1 += 5 * plus, y2 += 5 * plus;
		break;
	case 6: x1 += 6 * plus, x2 += 6 * plus, y1 += 6 * plus, y2 += 6 * plus;
		break;
	case 7: x1 += 7 * plus, x2 += 7 * plus, y1 += 7 * plus, y2 += 7 * plus;
		break;
	case 8: x1 += 8 * plus, x2 += 8 * plus, y1 += 8 * plus, y2 += 8 * plus;
		break;
	}

	Mat t1 = image(Range(100, 280), Range(0, 300));
	t1 = 255;
	imshow("궁금", t1);

    rect_img = image(Range(x1,x2),Range(y1,y2));
    Mat rt(rect_img.rows, rect_img.rows, CV_8U);
	Mat r_img = rotate(rect_img,90);

	imshow("회에전 레나", rotate(image, 90));
    imshow("레나", image);
    imshow("바뀐 레나", rect_img);
	imshow("회에1전 레나", rotate(rect_img, 45));

	

     waitKey(0);
}

Mat rotate(Mat src, double angle)
{
	Mat dst;
	Point2f pt(src.cols / 2.0, src.rows / 2.0);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, Size(src.cols, src.rows));
	return dst;
}


