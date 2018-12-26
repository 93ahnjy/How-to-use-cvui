/*
3개창에서 각각 다른 창에서의 마우스 위치를 보여준다.
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW1_NAME "Windows 1"
#define WINDOW2_NAME "Windows 2"
#define WINDOW3_NAME "Windows 3"

int main(int argc, const char *argv[])
{
    // We have one cv::Mat for each window.
    cv::Mat frame1 = cv::Mat(200, 500, CV_8UC3);
    cv::Mat frame2 = cv::Mat(200, 500, CV_8UC3);
    cv::Mat frame3 = cv::Mat(200, 500, CV_8UC3);


    // Init cvui, instructing it to create 3 OpenCV windows.
    const cv::String windows[] = { WINDOW1_NAME, WINDOW2_NAME, WINDOW3_NAME };
    cvui::init(windows, 3);

    while (true) {
        // clear all frames
        frame1 = cv::Scalar(49, 52, 49);
        frame2 = cv::Scalar(49, 52, 49);
        frame3 = cv::Scalar(49, 52, 49);

        // window1 gui
        // cvui::mouse(WINDOW1_NAME) 같이 특정 window에서의 마우스 좌표를 뽑아올 수 있다.
        cvui::context(WINDOW1_NAME);
        cvui::printf(frame1, 10, 10, "In window1, mouse is at: %d,%d (obtained from window name)", cvui::mouse(WINDOW1_NAME).x, cvui::mouse(WINDOW1_NAME).y);
        if (cvui::mouse(WINDOW1_NAME, cvui::LEFT_BUTTON, cvui::IS_DOWN)) {
            cvui::printf(frame1, 10, 30, "In window1, mouse LEFT_BUTTON is DOWN");
        }
        cvui::imshow(WINDOW1_NAME, frame1);




        // window2 gui
        cvui::context(WINDOW2_NAME);
        cvui::printf(frame2, 10, 10, "In window2, mouse is at: %d,%d (obtained from context)", cvui::mouse().x, cvui::mouse().y);
        if (cvui::mouse(cvui::LEFT_BUTTON, cvui::IS_DOWN)) {
            cvui::printf(frame2, 10, 30, "In window2, mouse LEFT_BUTTON is DOWN");
        }
        cvui::imshow(WINDOW2_NAME, frame2);







        // window3 gui
        // cvui::mouse(WINDOW1_NAME) 같이 특정 window에서의 마우스 좌표를 뽑아올 수 있다.
        cvui::context(WINDOW3_NAME);
        cvui::printf(frame3, 10, 10, "In window1, mouse is at: %d,%d", cvui::mouse(WINDOW1_NAME).x, cvui::mouse(WINDOW1_NAME).y);
        cvui::printf(frame3, 10, 30, "In window2, mouse is at: %d,%d", cvui::mouse(WINDOW2_NAME).x, cvui::mouse(WINDOW2_NAME).y);
        cvui::printf(frame3, 10, 50, "In window3, mouse is at: %d,%d", cvui::mouse(WINDOW3_NAME).x, cvui::mouse(WINDOW3_NAME).y);
        if (cvui::mouse(WINDOW1_NAME, cvui::LEFT_BUTTON, cvui::IS_DOWN)) {
            cvui::printf(frame3, 10, 90, "window1: LEFT_BUTTON is DOWN");
        }
        if (cvui::mouse(WINDOW2_NAME, cvui::LEFT_BUTTON, cvui::IS_DOWN)) {
            cvui::printf(frame3, 10, 110, "window2: LEFT_BUTTON is DOWN");
        }
        if (cvui::mouse(WINDOW3_NAME, cvui::LEFT_BUTTON, cvui::IS_DOWN)) {
            cvui::printf(frame3, 10, 130, "window3: LEFT_BUTTON is DOWN");
        }
        cvui::imshow(WINDOW3_NAME, frame3);

        // Check if ESC key was pressed
        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
