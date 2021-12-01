#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	int loRange[3] = {50, 25, 25};
	int hiRange[3] = {70, 255,255};


	VideoCapture camera(0);

	//czekanie na escape
	while (waitKey(1) != 27) {

		int dilation_size = 5;

		auto structElem = getStructuringElement(MORPH_ELLIPSE, // jądro przekształcenia
			Size(2 * dilation_size + 1, 2 * dilation_size + 1), // wieksza biala strefa
			Point(dilation_size, dilation_size));

		Mat frame;
		Mat backgroundScaled;
		Mat frameMask, frameNegMask;
		Mat frameWithMask, backgroundScaledWithMask;
		Mat meinniceplace;

		camera >> frame;
		flip(frame, frame, 1); // odbicie


		cvtColor(frame, frameMask, COLOR_BGR2HSV);
		inRange(frameMask, Scalar(loRange[0], loRange[1], loRange[2]),
			Scalar(hiRange[0], hiRange[1], hiRange[2]), frameNegMask);


		morphologyEx(frameNegMask, frameNegMask, MORPH_CLOSE, structElem);
		morphologyEx(frameNegMask, frameNegMask, MORPH_OPEN, structElem);
		imshow("dilate", frameNegMask);


		vector<vector<Point>> contours;
		findContours(frameNegMask, contours, RETR_LIST, CHAIN_APPROX_NONE);

		// funkcja do sortowania kontur  najwieksze = 0 i liczba rośnie dla malejących obiektów
		sort(contours.begin(), contours.end(),
			[](auto& a, auto& b) {
			return contourArea(a, false) > contourArea(b, false);
		});

		

		Point avg[2] = {};

		for (int i = 0; i < min(2, (int)contours.size()); i++)
		{
			approxPolyDP(contours.at(i), contours.at(i), 10, true);
			drawContours(frame, contours, i, { 0,0,255,255 });
			Rect r = boundingRect(contours.at(i));
			avg[i].x = r.x + r.width / 2;
			avg[i].y = r.y + r.height / 2;
		}

		//Rysowanie od środka jednego obiektu do środka drugiego
		if ((avg[0].y - avg[1].y < 50 && avg[1].y - avg[0].y < 50))
		{
			line(frame, avg[0], avg[1], Scalar(0, 0, 0), 8);
			line(frame, avg[1], avg[0], Scalar(80, 200, 130), 2);
		}
		imshow("contours", frame);

	}
	return 0;
}
