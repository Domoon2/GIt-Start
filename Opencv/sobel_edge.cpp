#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat rotate(Mat src, double angle) //È¸Àü
{
    Mat dst;
    Point2f pt(src.cols / 2.0, src.rows / 2.0);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;
}
int main()
{

    Mat src;
    Mat grad;
    int scale = 1;
    int delta = 0;

    src = imread("Lenna.png",IMREAD_GRAYSCALE);
    if (src.empty())
    {
        return -1;
    }

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    Sobel(src, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    Sobel(src, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);

    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    imshow("img", src);
    imshow("Sobel", grad);
    waitKey(0);
    return 0;
}