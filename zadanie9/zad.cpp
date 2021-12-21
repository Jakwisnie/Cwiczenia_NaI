
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;
using namespace cv;
void detectAndDisplay( Mat frame);

CascadeClassifier eyes_cascade;
int c=0;
const int N = 100;

class poz{ 
  int x; 
  int y;
public: 
  void setX(int i) { x = i; } 
  int getX() { return x; } 
  void setY(int i) { y = i; } 
  int getY() { return y; } 
}; 
poz g;
poz a[N];

void contains(poz e)
{
     
   int z =0;
    int l =0;
    for(z;z<=c;z++)
        if(a[z].getX()==e.getX() && a[z].getY()==e.getY()) 
        {
         
        }
    else {
        l++;
    }
    if (l>0){
        a[z].setX(e.getX());
        a[z].setY(e.getY());
      c++;
    }
}
int main( int argc, const char** argv )
{
a[0].setX(0);
a[0].setY(0);
system("pwd");

   
    //-- 1. Load the cascades
   if( !eyes_cascade.load( "haarcascade_eye.xml" ) ) {
        cout << "--(!) No haarcade -- Break!\n";
		return -8;
	};
   
   VideoCapture capture;
    capture.open( 0 );
    if ( ! capture.isOpened() )
    {
        cout << "--(!)Error opening video capture\n";
        return -7;
    }
	Mat frame;
    while ( capture.read( frame ) ) 
    {
        if( frame.empty() )
        {
            cout << "--(!) No captured frame -- Break!\n";
            return -1;  
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay(frame);
       if( (waitKey( 1 )&0x0ff) == 27 ) return 0;
    }
    return 0;
}
void detectAndDisplay( Mat frame)
{
	
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
   
    
        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale( frame_gray, eyes );
       
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( eyes[j].x + eyes[j].width/2, eyes[j].y + eyes[j].height/2 );
            g.setX(eyes[j].x + eyes[j].width/2);
            g.setY(eyes[j].y + eyes[j].height/2);
            
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
            contains(g);
            
            
        }

        
        cout<<c<<endl;
        imshow( "Capture - eye detection", frame );
}
