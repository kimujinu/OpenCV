/*#include <opencv2/opencv.hpp>
#include <windows.h>


using namespace cv;
using namespace std;
void spacefilter(Mat img, char*);
void binarizeImage(Mat img);
void filter_lin(Mat img, Mat resimg, int fter);
void generateNoise(Mat img, double rate);
void medianFilter(Mat img, Mat res);

int main(int argc, char* argv[]) {
	Mat img = imread("LenaRGB.bmp", IMREAD_GRAYSCALE);
	spacefilter(img, "�������͸�");
	return 0;

}

void spacefilter(Mat img, char* w) {
	Mat img2 = Mat::zeros(Size(img.cols, img.rows), CV_8U);
	namedWindow(w, WINDOW_AUTOSIZE);
	imshow(w, img);
	moveWindow(w, 100, 100);
	waitKey(0);// �ƹ�Ű�� ������ ����.
	//binarizeImage(img); imshow(w, img); waitKey(0);

	if (0) {
		filter_lin(img, img2, 1); filter_lin(img2, img2, 2);
		imshow("����", img2); waitKey(0);
		filter_lin(img, img2, 3); // 3
		imshow("����", img2); waitKey(0);
	}
	else {
		generateNoise(img, 0.1); imshow("����", img); waitKey(0);
		medianFilter(img, img2); imshow("����", img2); waitKey(0);
	}

	destroyWindow(w);

}

void binarizeImage(Mat img)
{
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			if (img.at<uchar>(i, j) < 128)
				img.at<uchar>(i, j) = 0;
			else
				img.at<uchar>(i, j) = 255;
}

void filter_lin(Mat img, Mat resimg, int fter) {
	float wbook[4][3][3] = { { { 1. / 20, 2. / 20, 1. / 20 },{ 2. / 20, 8. / 20, 2. / 20 },
	{ 1. / 20, 2. / 20, 1. / 20 } },
	{ { 1. / 9, 1. / 9, 1. / 9 },{ 1. / 9, 1. / 9, 1. / 9 },{ 1. / 9, 1. / 9, 1. / 9 } },
	{ { 0, -1, 0 },{ -1, 4, -1 },{ 0, -1, 0 } },	 //����þ� ���� 
	{ { 0, -2, 0 },{ -2, 8, -2 },{ 0, -2, 0 } } };	// Box/mean filter
	for (int r = 1; r < img.rows - 1; r++) {		// Laplacian 1 
		for (int c = 1; c < img.cols - 1; c++) {	// Laplacian 2
			int result = 0;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					result += wbook[fter][i][j] * img.at<uchar>(r + (i - 1), c + (j - 1));
			if (fter >= 2) result = result / 2 + 128;
			resimg.at<uchar>(r, c) = result;
		}
	}
}

void generateNoise(Mat img, double rate) { // ���� ����
	for (int i = 0; i < img.rows * img.cols * rate; i++) {
		int r = rand() % img.rows;
		int c = rand() % img.cols;
		img.at<uchar>(r, c) = 255 - img.at<uchar>(r, c);
	}
}

void medianFilter(Mat img, Mat res) { //���� ���� ������ �����ִ� ���͸�,salt&papper Noise�� �����ϴµ� ȿ����
	int g[9];
	for (int r = 1; r < img.rows - 1; r++) {
		for (int c = 1; c < img.cols - 1; c++) {
			int result = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					g[i * 3 + j] = img.at<uchar>(r + (i - 1), c + (j - 1)); //9���� 1-D �迭��
				}
			}
			for (int lastIndex = 7; lastIndex >= 0; lastIndex--) {
				for (int k = 0; k <= lastIndex; k++) {
					if (g[k] > g[k + 1]) {
						int t = g[k];
						g[k] = g[k + 1];
						g[k + 1] = t;
					}
				}
			}
			res.at<uchar>(r, c) = g[4];
		}
	}
}

*/