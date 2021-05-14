#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;
Mat rotate(Mat src, double angle);
Mat createOne(vector<Mat>& images, int cols, int min_gap_size);
Mat a[550][550];
Mat b;

int main()
{
	int a2 = 0;
	int a4 = 1;
	int n = 32;
	int rot = 180;
	Mat img = imread("Lenna.png");

	int p = (512 / n) * n;
	Mat output = img(Rect(0, 0, img.cols, img.rows)).clone();
	Mat outputROI;
	Mat SplitImage;
	Mat e;
	Rect r(Point(p, p), Point(img.rows, img.cols));



	for (int i = 0; i < img.cols / n; i++)
	{
		for (int j = 0; j < img.rows / n; j++)
		{	
			Rect z(Point(j * n, i * n), Point((j + 1) * n, (i + 1) * n));
			Rect x(Point((j+0) * n, (i+0) * n), Point(n * (j + 1), n * (i + 1)));
			//Rect c(Point((j + 0) * output.cols, (i + 0) * output.rows), Point(output.cols * (j + 1), output.rows * (i + 1)));

			SplitImage = rotate(img(x), rot);
			outputROI = output(x);
			SplitImage.copyTo(outputROI);
			outputROI.release();
		}			
	}		
	if (img.rows % n > 0)
	{
		for (int i = 0; i < (p / n); i++)
		{
			Rect a(Point(p, a2), Point(img.rows, a4*n));
			Rect b(Point(a2, p), Point(a4*n, img.cols));
			rotate(output(a), rot).copyTo(output(Rect(a)));
			rotate(output(b), rot).copyTo(output(Rect(b)));
			rotate(output(r), rot).copyTo(output(Rect(r)));
			a2 += n;
			a4 += 1;
		}
	}
	imshow("회전 레나", output);	
	waitKey(0);
}

Mat rotate(Mat src, double angle) //회전
{
	Mat dst;
	Point2f pt(src.cols / 2.0, src.rows / 2.0);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, Size(src.cols, src.rows));
	return dst;
}

Mat createOne(vector<Mat>& images, int cols, int min_gap_size)
{
	int max_width = 0;
	int max_height = 0;
	for (int i = 0; i < images.size(); i++)
	{
		if (i > 0 && images[i].type() != images[i - 1].type()) {
			cerr << "WARNING: creteOne failed, different types of images";
			return Mat();
		}
		max_height = max(max_height, images[i].rows);
		max_width = max(max_width, images[i].cols);
	}
	int rows = ceil(images.size() / cols);

	Mat result = Mat::zeros(rows * max_height + (rows - 1) * min_gap_size,
		cols * max_width + (cols - 1) * min_gap_size, images[0].type());

	size_t i = 0;
	int current_height = 0;
	int current_width = 0;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (i >= images.size())
				return result;

			Mat to(result,
				Range(current_height, current_height + images[i].rows),
				Range(current_width, current_width + images[i].rows));
				
			images[i++].copyTo(to);
			current_width += max_width + min_gap_size;
		}
		current_width = 0;
		current_height += max_height + min_gap_size;
	}
	return result;
}