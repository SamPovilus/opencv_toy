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
    Mat m1 = Mat(image.size[0],image.size[1], CV_8UC3, Scalar(255,255,0));

    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    int targetSize = 5;
    cv::Mat gaussX = cv::getGaussianKernel(targetSize, -1, CV_32F);
    cv::Mat gaussY = cv::getGaussianKernel(targetSize, -1, CV_32F);
    cv::Mat gauss2d = gaussX * gaussY.t();
    gauss2d *= 200;

    cout << "gauss2d = "<< endl << " "  << gauss2d << endl << endl;
    
    // get the circle's bounding rect
    Rect boundingRect(c.center.x-c.radius, c.center.y-c.radius, c.radius*2+1,c.radius*2+1);

    int xTargetLoc = c.center.x;
    int yTargetLoc = c.center.y;

    Mat target = image.colRange(xTargetLoc,xTargetLoc+targetSize).rowRange(yTargetLoc,yTargetLoc+targetSize);

    cout << "image 1= " << endl << image.colRange(xTargetLoc,xTargetLoc+targetSize).rowRange(yTargetLoc,yTargetLoc+targetSize) << endl << endl;

    cout << "image corner = " << endl << image.colRange(0,3).rowRange(0,3) << endl << endl;

    // obtain the image ROI:
    Mat circleROI(image, boundingRect);

    cout << "image 2= " << endl << image.colRange(xTargetLoc,xTargetLoc+targetSize).rowRange(yTargetLoc,yTargetLoc+targetSize) << endl << endl;

    //draw the circle
    circle(circleROI, Point(c.radius, c.radius), c.radius, Scalar::all(1), -1);

    cout << "image 4= " << endl << image.colRange(xTargetLoc,xTargetLoc+targetSize).rowRange(yTargetLoc,yTargetLoc+targetSize) << endl << endl;


    gauss2d.copyTo(target);

    cout << "image 5= " << endl << image.colRange(xTargetLoc,xTargetLoc+targetSize).rowRange(yTargetLoc,yTargetLoc+targetSize) << endl << endl;


    cvtColor(image,image,COLOR_BGR2GRAY);
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}
