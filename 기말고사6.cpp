/*#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>

#define min(a,b) (((a) < (b)) ? (a) : (b))

using namespace cv;
using namespace std;

void camerafaces(char *wcam);
void facedetector(char *wcam, Mat frame);


String faceCasName = "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
String eyesCasName = "C:/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

CascadeClassifier facecas;
CascadeClassifier eyescas;

int main(int argc, char* argv[]) {

	//camerashooter(“방송중”);
	// edgedetectors(“정상”);
	camerafaces("얼굴들");
	return(0);
}


void camerafaces(char *wcam) {

	Mat frame;
	bool stop(false);
	int fps = 30;
	if (!facecas.load(faceCasName)) {
		cerr << "Face load X" << endl; return;
	}
	if (!eyescas.load(eyesCasName)) {
		cerr << "Eyes load X" << endl; return;
	}
	VideoCapture cap(0);
	if (!cap.isOpened()) return;
	namedWindow(wcam, WINDOW_AUTOSIZE);
	moveWindow(wcam, 100, 100);
	// while(!stop) . . .
	while (!stop) {
		cap >> frame;
		imshow(wcam, frame);
		facedetector(wcam, frame);
		if (waitKey(1000 / fps) == 27) stop = true;
	}
	cap.release();
}



void facedetector(char *wcam, Mat frame)
{
	Mat framegray;
	vector<Rect> faceRex;// 검출결과
	cvtColor(frame, framegray, COLOR_BGR2GRAY);
	equalizeHist(framegray, framegray);
	imshow("균명도영상", framegray);
	facecas.detectMultiScale(framegray, faceRex, 1.1, 2, 0, Size(30, 30));
	for (int i = 0; i < faceRex.size(); i++)
	{
		Rect fr = faceRex[i];
		rectangle(frame, Point(fr.x, fr.y), Point(fr.x + fr.width, fr.y + fr.height), Scalar(255, 255, 0), 3, 8, 0);// 굵기
		//- any further processing – eyes and mouth and ...
		Mat faceROI = framegray(fr);// ROI : Region of interesteing
		vector<Rect> eyesRex; // 검출결과
		eyescas.detectMultiScale(faceROI, eyesRex, 1.1, 2, 0,
			Size(20, 10)); //size: 눈의 최소사이즈
		for (int j = 0; j < min(2, eyesRex.size()); j++)
		{
			Rect er = eyesRex[j];
			Point jungsim(fr.x + er.x + er.width / 2, fr.y + er.y + er.height / 2);
			int radius = cvRound((er.width + er.height) / 4);
			circle(frame, jungsim, radius, Scalar(255, 0, 0), 4, 8, 0);
		}
	}
	imshow(wcam, frame);
}
*/