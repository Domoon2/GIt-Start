#include <iostream>
#include <opencv2/opencv.hpp>	
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/ml.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;
using namespace cv::ml;

int threshold_value = 128;
int threshold_type = 0;
const int max_value = 255;
const int max_binary_value = 255;
Mat src, src_gray, dst;
static void MyThreshold(int, void*)
{
	threshold(src, dst, threshold_value, max_binary_value, threshold_type);
	imshow("result", dst);
}

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
void shuffleDFT(Mat& src)
{
	int cX = src.cols / 2;
	int cY = src.rows / 2;

	Mat q1(src, Rect(0, 0, cX, cY));
	Mat q2(src, Rect(cX, 0, cX, cY));
	Mat q3(src, Rect(0, cY, cX, cY));
	Mat q4(src, Rect(cX, cY, cX, cY));

	Mat tmp;
	q1.copyTo(tmp);
	q4.copyTo(q1);
	tmp.copyTo(q4);
	q2.copyTo(tmp);
	q3.copyTo(q2);
	tmp.copyTo(q3);
}
Mat getFilter(Size size)
{
	Mat filter = Mat::ones(size, CV_32FC2);
	circle(filter, size / 2, 10, Vec2f(0, 0), -1);
	return filter;
}
int main()
{
	Mat train_features(5, 2, CV_32FC1);
	Mat labels(5, 1, CV_32FC1);

	train_features.at<float>(0, 0) = 10, train_features.at<float>(0, 1) = 10;
	train_features.at<float>(1, 0) = 10, train_features.at<float>(1, 1) = 20;
	train_features.at<float>(2, 0) = 10, train_features.at<float>(2, 1) = 10;
	train_features.at<float>(3, 0) = 10, train_features.at<float>(3, 1) = 30;
	train_features.at<float>(4, 0) = 10, train_features.at<float>(4, 1) = 30;
	
	labels.at<float>(0, 0) = 1;
	labels.at<float>(1, 0) = 1;
	labels.at<float>(2, 0) = 1;
	labels.at<float>(3, 0) = 2;
	labels.at<float>(4, 0) = 2;

	Ptr<ml::KNearest> knn = ml::KNearest::create();
	Ptr<ml::TrainData> trainData = ml::TrainData::create(train_features, ROW_SAMPLE, labels);

	knn->train(trainData);

	Mat sample(1, 2, CV_32FC1);
	Mat predictedLabels;

	sample.at<float>(0, 0) = 28, sample.at<float>(0, 1) = 28;

	knn->findNearest(sample, 2, predictedLabels);

	float prediction = predictedLabels.at<float>(0, 0);
	cout << "�׽�Ʈ ������ �� = " << prediction << endl;
	return 0;
}