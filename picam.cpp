#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void drawText(Mat & image);

int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat road_img, driver_img;
    VideoCapture capture0, capture1;
    capture0.open(0);
    capture1.open(2);

    if (!capture0.open(0))
    {
        cout << "Capture0 is not opened" << endl;
        return 0;
    }
    if (!capture1.open(2))
    {
        cout << "Capture1 is not opened" << endl;
        return 1;
    }
    cout << "Capture is opened" << endl;
    for(;;)
    {
        capture0 >> road_img;
        capture1 >> driver_img;
        cv::rotate(road_img, road_img, cv::ROTATE_180);
        cv::rotate(driver_img, driver_img, cv::ROTATE_180);
        printf("RoadImage->width:%d, height:%d\n", road_img.cols, road_img.rows);
        printf("DriverImage->width:%d, height:%d\n", driver_img.cols, driver_img.rows);
        if(road_img.empty())
            break;
        if(driver_img.empty())
            break;
        drawText(road_img);
        drawText(driver_img);
        imshow("road_facing", road_img);
        imshow("driver_facing", driver_img);
        if(waitKey(10) >= 0)
            break;
    }
    return 0;
}

void drawText(Mat & image)
{
    putText(image, "Hello OpenCV",
            Point(20, 50),
            FONT_HERSHEY_COMPLEX, 1, // font face and scale
            Scalar(255, 255, 255), // white
            1, LINE_AA); // line thickness and type
}
