#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat road_img, driver_img;
    VideoCapture cap;
    cap.open(0);
    cap.set(cv::CAP_PROP_FPS, 60);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    int width = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps = (int)cap.get(cv::CAP_PROP_FPS);
    printf("width:%d, height:%d, fps:%d\n", width, height, fps);
    /* capture1.open(2); */

    if (!cap.open(0))
    {
        cout << "cap is not opened" << endl;
        return 0;
    }
    /* if (!capture1.open(2)) */
    /* { */
    /*     cout << "Capture1 is not opened" << endl; */
    /*     return 1; */
    /* } */
    cout << "Capture is opened" << endl;
    for(;;)
    {
        cap >> road_img;

        /* capture1 >> driver_img; */
        cv::rotate(road_img, road_img, cv::ROTATE_180);
        /* cv::rotate(driver_img, driver_img, cv::ROTATE_180); */
        // printf("RoadImage->width:%d, height:%d\n", road_img.cols, road_img.rows);
        /* printf("DriverImage->width:%d, height:%d\n", driver_img.cols, driver_img.rows); */
        if(road_img.empty())
            break;
        /* if(driver_img.empty()) */
        /*     break; */
        cv::putText(road_img, "road_facing_cam", Point(20, 50),
                    FONT_HERSHEY_COMPLEX, 1, // font face and scale
                    Scalar(255, 255, 255), // white
                    1, LINE_AA); // line thickness and type

        cv::namedWindow("road_facing", cv::WINDOW_NORMAL);
        // cv::setWindowProperty("road_facing", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
        cv::imshow("road_facing", road_img);
        cv::moveWindow("road_facing", 30, 40);
        /* imshow("driver_facing", driver_img); */
        if(waitKey(10) >= 0)
            break;
    }
    return 0;
}
