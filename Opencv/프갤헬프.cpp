#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
using namespace cv;
using namespace std;

void rotate(Mat src, double angle,Mat* output) //회전
{
    Mat dst;
    Point2f pt(src.cols / 2.0, src.rows / 2.0);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    dst.copyTo(*output);
}

int main()
{
    int n = 50; //분할 픽셀 사이즈
    int rot = 90; //회전할 각도
    Mat outputROI;
    Mat* SplitImage;
    std::vector<Mat*>vPtList;
    std::vector<Mat*>::iterator 
        vPtList_iter;    
    Mat img = imread("Lenna.png");

    Mat* o ;
    Rect r(0, 0, 512, 512);

    if (512 % n > 0)
    {        
        o = new Mat(img.cols + n - (img.cols % n), img.cols + n - (img.cols % n), CV_8UC3);
    }
    else
    {        
        o =new Mat(512, 512, CV_8UC3);
    }
    img.copyTo((*o)(r));
       
    for (int i = 0; i < o->cols / n; i++)
    {
        for (int j = 0; j < o->rows / n; j++)
        {
            Rect z(Point(j * n, i * n), Point((j + 1) * n, (i + 1) * n));
            SplitImage = new Mat[z,CV_8UC3];
            vPtList.push_back(SplitImage);
            rotate((*o)(z), rot, SplitImage);
            outputROI = (*o)(z);
            (*SplitImage).copyTo(outputROI);
        }
    }

   
    imshow("33", *o);    
    imwrite("check.png", *o);    
 
    waitKey(0);            
    delete o;
    for (vPtList_iter = vPtList.begin(); vPtList_iter != vPtList.end(); vPtList_iter++)
    {
        Mat* temp = *vPtList_iter;
        delete temp;
    }
    return 0;
 
}
    