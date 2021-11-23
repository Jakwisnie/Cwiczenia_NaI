#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/video/tracking.hpp>

using namespace cv;
using namespace std;
struct hsv {
    int lRangeValue = 0;
    int rRangeValue = 0;
    int lRangeHue = 0;
    int rRangeHue = 0;
    int lRangeSaturation = 0;
    int rRangeSaturation = 0;
};

int main( int argc, char** argv ) {
    bool capturing = true;
    VideoCapture cap(0);
    
    //Selecting the resolution
    int width, height;
    if(argc == 3){
        width = atof(argv[1]);
        height = atof(argv[2]);
    }else {
        width = 320;
        height = 200;
    }
    //HSV
    hsv hsvColor;

    //Windows
    namedWindow("HSV", WINDOW_NORMAL);
    namedWindow("HSVRange", WINDOW_KEEPRATIO);

    //Trackballs
    createTrackbar("lHue", "HSVRange", &hsvColor.lRangeHue, 180);
    createTrackbar("rHue", "HSVRange", &hsvColor.rRangeHue, 180);
    createTrackbar("lVal", "HSVRange", &hsvColor.lRangeValue, 255);
    createTrackbar("rVal", "HSVRange", &hsvColor.rRangeValue, 255);
    createTrackbar("lSat", "HSVRange", &hsvColor.lRangeSaturation, 255);
    createTrackbar("rSat", "HSVRange", &hsvColor.rRangeSaturation, 255);

    if (!cap.isOpened() ) {
        cerr << "error opening frames source" << endl;
        return -1;
    }
    do {
        Mat frame, window, hsv, hsvRange;
        Mat dst = frame;
        cap >> frame;
        if (cap.read(frame)) {
            //Resize 'window'
            resize(frame,window,{width,height});
            imshow("Rozmiarowka", window);
            GaussianBlur(window,dst,Size(3,3),0);
            imshow("Gauss",dst);
        } else {
            // stream finished
            capturing = false;
        }
        //Control HSV
        cvtColor(frame, hsvRange, COLOR_BGR2HSV);
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsvRange,Scalar(hsvColor.lRangeHue,hsvColor.lRangeSaturation,hsvColor.lRangeValue),
        Scalar(hsvColor.rRangeHue, hsvColor.rRangeSaturation, hsvColor.rRangeValue), hsvRange);
       
        imshow("HSVRange",hsvRange);
         imshow("HSV", hsv);
        //Wait for 'ESC'
        if((waitKey(1000.0/60.0)&0x0ff) == 27) capturing = false;
       
        //Screenshot for 'x' key
        if((waitKey(1000.0/60.0)&0x0ff) == 120) {
            Rect2d r = selectROI(frame);
            Mat cropFrame = frame(r);
            imshow("Basic", cropFrame);
            imwrite("screenshot.jpg",cropFrame);

        }
    } while(capturing);
    return 0;
}
