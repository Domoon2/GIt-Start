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
    int n = 360;
    int rot = 45;
    Mat outputROI;
    Mat SplitImage;

    Mat img = imread("Lenna.png");

    Mat* o = new Mat;
    Mat& img2 = *o;
    Rect r(0, 0, 512, 512);

    if (512 % n > 0)
    {        
        *o = Mat(img.cols + n - (img.cols % n), img.cols + n - (img.cols % n), CV_8UC3);
    }
    else if (512 % n == 0)
    {        
        *o = Mat(512, 512, CV_8UC3);
    }
    img.copyTo(img2(r));
       
    for (int i = 0; i < img2.cols / n; i++)
    {
        for (int j = 0; j < img2.rows / n; j++)
        {
            Rect z(Point(j * n, i * n), Point((j + 1) * n, (i + 1) * n));
            SplitImage = rotate(img2(z), rot);
            outputROI = img2(z);
            SplitImage.copyTo(outputROI);
        }
    }
    imshow("33", *o);    
    waitKey(0);        

    return 0;
    delete[] o;        
}
    