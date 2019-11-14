#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

typedef struct {
    double radius;
    Point center;
} Circle;


int main( int argc, char** argv )
{
    Circle c;
    c.radius = 100.0;
    c.center.x = 100;
    c.center.y = 150;
    String imageName( "HappyFish.jpg" ); // by default
    if( argc > 1)
    {
        imageName = argv[1];
    }
    Mat image;
    image = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Read the file
    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    // get the circle's bounding rect
    Rect boundingRect(c.center.x-c.radius, c.center.y-c.radius, c.radius*2+1,c.radius*2+1);

    // obtain the image ROI:
    Mat circleROI(image, boundingRect);

    //draw the circle
    circle(circleROI, Point(c.radius, c.radius), c.radius, Scalar::all(1), -1);


    cvtColor(image,image,COLOR_BGR2GRAY);
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}
