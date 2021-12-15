
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void detectAndDisplay( Mat frame );

CascadeClassifier eyes_cascade;
int main( int argc, const char** argv )
{
    


   
    //-- 1. Load the cascades
   if( !eyes_cascade.load( "haarcascade_eye.xml" ) ) {
		return -8;
	};
   
   VideoCapture capture;
	capture.open( -1 );
	if ( ! capture.isOpened() ) {
		return -7;
	}
	Mat frame;
	while ( capture.read( frame ) ) {
		        if( frame.empty() )
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );
        if( waitKey(10) == 27 )
        {
            break; // escape
        }
	}
	return 0;
}
void detectAndDisplay( Mat frame )
{
	int c =0;
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
   
    
        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale( frame_gray, eyes );
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( eyes[j].x + eyes[j].width/2, eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
			c=c+1;
            cout<<c<<endl;
        }
}
