/*#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void edgedetectors(char *);
// void CannyThresh(int, void*);
int lowThr; // T1 for Canny
Mat gim, cadge;
char *wemap = "모서리맵";


void CannyThresh(int, void*) {
	int ratio = 3, kernelsz = 3;
	//edge 처리 , 결과 = cadge :
	Canny(gim, cadge, lowThr, ratio*lowThr, 3, kernelsz);
	// 3 = aperture size(~diameter)
	imshow(wemap, cadge);

}



int main(int argc, char* argv[]) {
	edgedetectors("정상");
	return 0;
}


void edgedetectors(char* w0) {
	Mat img = imread("worldleaders_atUN.jpg",
		IMREAD_COLOR);
	if (img.empty()) { cout << "사진 없다." << endl; return; }
	namedWindow(w0, WINDOW_AUTOSIZE);
	imshow(w0, img);
	moveWindow(w0, 100, 100);
	waitKey(0);
	//- (1) make it gray & smooth it - 
	cvtColor(img, gim, COLOR_RGB2GRAY);
	char *w1 = "모서리";
	imshow(w1, gim);
	waitKey(0);
	GaussianBlur(gim, gim, Size(3, 3), 0, 0, BORDER_DEFAULT);
	imshow(w1, gim); waitKey(0);
	//- (2) edge detection : Sobel, Laplacian, Canny -
	Mat gradX, gradY, ddgim; // gradients, & Laplacian images
	Mat absGradX, absGradY, gradim; // edges of magnitude
	Mat edge; // thresholded edge image
	int scale = 1, delta = 0, ddepth = CV_16S;
	int ftype = 2;
	//- Sobel -
	if (ftype == 1) {
		Sobel(gim, gradX, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT); //~x
		convertScaleAbs(gradX, absGradX);
		imshow(w1, absGradX); waitKey(0);
		Sobel(gim, gradY, ddepth, 0, 1, 3, BORDER_DEFAULT); //~y
		convertScaleAbs(gradY, absGradY);
		imshow(w1, absGradY); waitKey(0);
		addWeighted(absGradX, 0.5, absGradY, 0.5, delta, gradim);
		imshow(w1, gradim); waitKey(0);
		threshold(gradim, edge, 128, 255, THRESH_BINARY);
		imshow(wemap, edge); waitKey(0);
	}
	else if (ftype == 2) {
		//- Laplacian - 
		Laplacian(gim, ddgim, ddepth, 3, scale, 0, BORDER_DEFAULT);
		convertScaleAbs(ddgim, gradim); // 3 = k_sz, 0=delta
		imshow(w1, gradim); waitKey(0);
	}

	else {
		//- Canny -
		namedWindow(wemap, WINDOW_AUTOSIZE);
		createTrackbar("minThr", wemap, &lowThr, 100,
			CannyThresh); // 100 = max_lowThr //- callback function 등록 -
		CannyThresh(0, 0); // 초기화
		waitKey(0);

	}
}
*/