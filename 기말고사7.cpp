#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

//void camerashooter(char*);
//void camerafaces(char *);
//void camerapedestrians(char *);
void bgsub(char*);

int main(int argc, char* argv[]) {
	// camershooter(“정상”);
	// camerafaces(“얼굴들”);
	// camerapedestrians(“사람들”);
	bgsub("bgs - 사람들");
	return(0);
}

void bgsub(char *wcam) {

	Mat frame, fg, bg, dfg;
	bool stop(false), detectShadow = true;
	int history = 500, keyboard;
	vector<vector<Point>> contours;
	//- video cap & bg-model …
	namedWindow(wcam, WINDOW_AUTOSIZE);
	moveWindow(wcam, 100, 100);
	namedWindow("BG");
	namedWindow("FG");
	namedWindow("dFG");
	VideoCapture cap("pedestrian-efpl-campus4-c0.avi");
	if (!cap.isOpened()) return;
	//- create a background subtractor … !?
	int wide = (int)cap.get(CAP_PROP_FRAME_WIDTH);
	int high = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
	Ptr<BackgroundSubtractor> pMOG2;
	pMOG2 = createBackgroundSubtractorMOG2(history, 16, detectShadow = true);
	//- video cap & bg-model …
	moveWindow("FG", 100 + (wide + 16), 100);
	moveWindow("BG", 100 + (wide + 16) * 2, 100);
	moveWindow("dFG", 100 + (wide + 16) * 3, 100);
	while (!stop) {
		if (!cap.read(frame)) {
			cerr << "frame read err" << endl;
			exit(EXIT_FAILURE);
		}
		pMOG2->apply(frame, fg);
		erode(fg, fg, Mat());
		dilate(fg, fg, Mat());
		findContours(fg, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		drawContours(frame, contours, -1, Scalar(0, 0, 255), 2);
		imshow(wcam, frame);
		imshow("FG", fg);
		pMOG2->getBackgroundImage(bg);
		imshow("BG", bg);
		absdiff(frame, bg, dfg);
		imshow("dFG", dfg);
		if (waitKey(1000 / 30) >= 0) stop = true;
	}
	cap.release();
}