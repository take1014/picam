#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#include <time.h>

void getTime(char *file_name);

void getTime(char *file_name)
{
	time_t t = time(NULL);
	struct tm *local = localtime(&t);
    sprintf(file_name, "%04d%02d%02d%02d%02d%02d", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
}

int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat road_img;
    cv::VideoCapture cap;
    cap.open(0);
    cap.set(cv::CAP_PROP_FPS, 60);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    int w = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int h = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps = (int)cap.get(cv::CAP_PROP_FPS);
    int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    fourcc = -1;
    printf("width:%d, height:%d, fps:%d\n", w, h, fps);
    cv::VideoWriter out;
    /* capture1.open(2); */

    if (!cap.open(0))
    {
        cout << "cap is not opened" << endl;
        return 0;
    }
    cout << "Capture is opened" << endl;

    int frame_count = 0;
    char file_name[15];
    for(;;)
    {
        if (frame_count == 0)
        {
            printf("create VideoWriter\n");
            getTime(&file_name[0]);
            printf("Now local time is ....%s\n", file_name);
            std::string str_file_name(file_name, 14);
            out = cv::VideoWriter(str_file_name, fourcc, fps, cv::Size(w, h), 0);
            printf("create VideoWriter\n");
        }
        cap >> road_img;
        cv::rotate(road_img, road_img, cv::ROTATE_180);
        // printf("RoadImage->width:%d, height:%d\n", road_img.cols, road_img.rows);
        if(road_img.empty())
            break;
        cv::putText(road_img, "road_facing_cam", Point(20, 50),
                    FONT_HERSHEY_COMPLEX, 1, // font face and scale
                    Scalar(255, 255, 255), // white
                    1, LINE_AA); // line thickness and type

        cv::namedWindow("road_facing", cv::WINDOW_AUTOSIZE);
        // cv::setWindowProperty("road_facing", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
        cv::imshow("road_facing", road_img);
        cv::moveWindow("road_facing", 30, 40);
        out.write(road_img);
        frame_count ++;
        if (frame_count > 9000)
        {
            frame_count = 0;
        }

        if(waitKey(10) >= 0)
            break;
    }

    cap.release();
    out.release();
    return 0;
}
