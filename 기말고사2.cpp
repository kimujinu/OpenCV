﻿/*#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

void morphrocessor(char *);
void skin_color_processor(Mat img, Mat face);
bool isskin(Vec3b px3);
bool isskin_Peer(uchar r, uchar g, uchar b);
void drawREBounds(Mat, vector<vector<Point>>,
	vector<Vec4i>, Mat);
Mat locateFaces(Mat mface);

int main(int argc, char* argv[]) {
	morphrocessor("형태처리다");
	return(0);

}



void morphrocessor(char* w0) {

	Mat img = imread("worldleaders_atUN.jpg",
		IMREAD_COLOR);
	Mat face = Mat::zeros(Size(img.cols, img.rows), CV_8U);
	Mat mface = face.clone();
	if (img.empty()) { cout << "사진 없다." << endl; return; }
	namedWindow(w0, WINDOW_AUTOSIZE);
	imshow(w0, img);
	moveWindow(w0, 100, 100);
	waitKey(0);
	//- find skin pixels 
	skin_color_processor(img, face);
	imshow("얼굴", face);
	waitKey(0);
	//- MORPHGY: erode/dilate/open/close -
	if (1) {
		erode(face, mface, Mat(), Point(-1, -1), 1);
		dilate(mface, mface, Mat(), Point(-1, -1), 1);
	}
	else {
		Mat mel(5, 5, CV_8U, Scalar(1));
		morphologyEx(face, mface, MORPH_OPEN, mel);
		morphologyEx(mface, mface, MORPH_CLOSE, mel);
	}
	imshow("얼굴2", mface);
	waitKey(0);
	//- find face contours - 
	Mat fcontr = locateFaces(mface);
	imshow("얼굴윤곽", fcontr);
	waitKey(0);

}


void skin_color_processor(Mat img, Mat face) {

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (isskin(img.at<Vec3b>(i, j))) //3개로 분할 
				face.at<uchar>(i, j) = 255;
		}
	}
}


bool isskin(Vec3b px3) {
	return isskin_Peer(px3[2], px3[1], px3[0]);
}


bool isskin_Peer(uchar r, uchar g, uchar b) {

	if (!(r > 95 && g > 40 && b > 20)) return false;
	else if (!(abs(r - b) > 15 && r > g && r > b)) return false;
	else {
		uchar mx = max(r, g); uchar mn = min(r, b);
		if (max(mx, b) - min(mn, b) <= 15) return false;
		else return true;
	}
}



Mat locateFaces(Mat mface) {

	Mat canny_oput;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	RNG rng(12345);
	int thresh = 100; // for Canny
	Canny(mface, canny_oput, thresh, thresh * 2, 3); //aperture
	findContours(canny_oput, contours, hierarchy,
		RETR_TREE, CHAIN_APPROX_SIMPLE,
		Point(0, 0)); // mode, method, offset
					  //- draw contours -
	Mat drawing = Mat::zeros(canny_oput.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8,
			hierarchy, 0, Point()); //1=thick, 8=line_type
	}
	//- draw Bounds – here …
	drawREBounds(canny_oput, contours, hierarchy, drawing);
	return drawing;
}

void drawREBounds(Mat canny_oput, vector<vector<Point>>
	contours, vector<Vec4i> hierarchy, Mat drawing) {
	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> minEllipse(contours.size());
	RNG rng(12345);
	//- compute Rects and Ellipses -
	for (int i = 0; i < contours.size(); i++) {
		if (contours[i].size() > 100) {
			minRect[i] = minAreaRect(Mat(contours[i]));
			minEllipse[i] = fitEllipse(Mat(contours[i]));
		}
	}
	//- draw Rects and Ellipses -
	for (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		ellipse(drawing, minEllipse[i], color, 1, 8); //1=굵, 8=탶
		Point2f rect_points[4];
		minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			line(drawing, rect_points[j], rect_points[(j + 1) % 4],
				color, 1, 8); //one side of the rotated rectangle
	}
}
*/