#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

typedef struct {
    double x_radius;
    double y_radius;
    Point center;
} Circle;


int main( int argc, char** argv )
{
    int image_x = 400;
    int image_y = 600;
    Circle c;
    c.x_radius = floor(image_x/2);
    c.y_radius = floor(image_y/2);
    c.center.x = floor(image_x/2);
    c.center.y = floor(image_y/2);
    Mat image(400,600,CV_32F);
    Mat zeros = Mat::zeros(image.size(), image.type());
    Mat mask = Mat::zeros(image.size(), image.type());
    randn(image,0.5,0.1);

    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    int targetSize = 10;
    cv::Mat gaussX = cv::getGaussianKernel(targetSize, -1, CV_32F);
    cv::Mat gaussY = cv::getGaussianKernel(targetSize, -1, CV_32F);
    cv::Mat gauss2d = gaussX * gaussY.t();
    gauss2d *= -10.0;

    
    // get the circle's bounding rect
    Rect boundingRect(0,0,image_x,image_y);

    int xTargetLoc = 32;
    int yTargetLoc = 90;

    gauss2d.copyTo(zeros(Rect(xTargetLoc, yTargetLoc, targetSize, targetSize)));
    image += zeros;

    // obtain the image ROI:
    //Mat circleROI(mask, boundingRect);

    //draw the circle
    //circle(circleROI, Point(c.radius, c.radius), c.radius, Scalar::all(1), -1);
    ellipse(mask,Point(c.center.x,c.center.y),Size(c.x_radius,c.y_radius),0,0,0,Scalar::all(1), -1);
    //cout << "circleROI = " << endl << circleROI << endl << endl;
    cout << "mask = " << endl << mask << endl << endl;
    image += mask;
    //cvtColor(image,image,COLOR_BGR2GRAY);
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}
