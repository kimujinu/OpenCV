/* //
#include <opencv2/opencv.hpp>
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
	Mat img3 = Mat(img.size(), CV_32F, Scalar(0)); // float 
	Mat img4 = Mat(img.size(), CV_32F, Scalar(0));
	Mat img5 = Mat(img.size(), CV_32F, Scalar(0)); Mat edge;

	namedWindow(w, WINDOW_AUTOSIZE);
	imshow(w, img);
	moveWindow(w, 100, 100);
	waitKey(0); // �ƹ�Ű�� ������ ����.
	//binarizeImage(img); imshow(w, img); waitKey(0);

	if (1) {
		filter_lin(img, img2, 1); filter_lin(img2, img2, 2);
		imshow("����", img2); waitKey(0);
		filter_lin(img, img2, 3); // 3
		imshow("����", img2); waitKey(0);
		filter_lin(img, img3, 4);  // 5
		imshow("����1", img3); waitKey(0); img3.convertTo(img3, CV_8U);

		//Sobel ���͸�: ��� ���⿡�� ������ �����ϴ� ����������

		filter_lin(img, img4, 6);  // img4,5 : CV_32F (- ~ +) filter_lin(img, img5, 7);
		Sobel(img, img4, CV_32F, 1, 0, 3);  // - �� - (1=dx,0=dy) 
		magnitude(img4, img5, edge);
		Sobel(img, img5, CV_32F, 0, 1, 3);  // - �� - (3=Ŀ��size)

											// +
		convertScaleAbs(img4, img4);
		convertScaleAbs(img5, img5);
		imshow("�ٿ�1a", img4); imshow("�ٿ�2a", img5); waitKey(0);
		// scaling + ���밪 convertScaleAbs(img5, img5); imshow("�ٿ�1a", img4); imshow("�ٿ�2a", img5); waitKey(0);
		edge.convertTo(edge, CV_8U); imshow("�Һ�", edge); waitKey(0);

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
	{ { 0, -1, 0 },{ -1, 4, -1 },{ 0, -1, 0 } },  //����þ� ���� 
	{ { 0, -2, 0 },{ -2, 8, -2 },{ 0, -2, 0 } } };// Box/mean filter
	for (int r = 1; r < img.rows - 1; r++) {      // Laplacian 1 
		for (int c = 1; c < img.cols - 1; c++) {  // Laplacian 2
			int result = 0;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					result += wbook[fter][i][j] * img.at<uchar>(r + (i - 1), c + (j - 1));

			if (fter == 2 || fter == 3) result = result / 2 + 128;
			if (fter <= 3) 
				resimg.at<uchar>(r, c) = result;
			else 
				resimg.at<float>(r, c) = result;


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
			for (int lastIndex = 7; lastIndex >= 0; lastIndex--) {  //�����Ʈ
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