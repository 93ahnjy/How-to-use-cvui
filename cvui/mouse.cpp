/*
This is application shows the mouse API of cvui. It shows a rectangle on the
screen everytime the user clicks and drags the mouse cursor around.

Copyright (c) 2017 Fernando Bevilacqua <dovyski@gmail.com>
Licensed under the MIT license.
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>






#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Mouse"






int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(300, 600, CV_8UC3);

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    // Rectangle to be rendered according to mouse interactions.
    cv::Rect rectangle(0, 0, 0, 0);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);


        cvui::text(frame, 10, 30, "Click (any) mouse button and drag the pointer around to select an area.");


        // 마우스 위치 출력
        cvui::printf(frame, 10, 50, "Mouse pointer is at (%d,%d)", cvui::mouse().x, cvui::mouse().y);



        //cvui::mouse(int query)를 이용하면 현 마우스 상태가 query상태가 맞는지를 bool로 출력
        // cvui::DOWN(누르는 중), cvui::UP(뗀 상태), cvui::CLICK(클릭)은 1 프레임만 True를 출력
        // 단, cvui::IS_DOWN는 누르는 중이면 계속 true 출력
        if (cvui::mouse(cvui::DOWN)) {
            // Position the rectangle at the mouse pointer.
            rectangle.x = cvui::mouse().x;
            rectangle.y = cvui::mouse().y;
        }

        // Is any mouse button down (pressed)?
        if (cvui::mouse(cvui::IS_DOWN)) {
            // Adjust rectangle dimensions according to mouse pointer
            rectangle.width = cvui::mouse().x - rectangle.x;
            rectangle.height = cvui::mouse().y - rectangle.y;

            // Show the rectangle coordinates and size
            cvui::printf(frame, rectangle.x + 5, rectangle.y + 5, 0.3, 0xff0000, "(%d,%d)", rectangle.x, rectangle.y);
            cvui::printf(frame, cvui::mouse().x + 5, cvui::mouse().y + 5, 0.3, 0xff0000, "w:%d, h:%d", rectangle.width, rectangle.height);
        }



        // Did any mouse button go up?
        if (cvui::mouse(cvui::UP)) {
            // Hide the rectangle
            rectangle.x = 0;
            rectangle.y = 0;
            rectangle.width = 0;
            rectangle.height = 0;
        }

        // Was the mouse clicked (any button went down then up)?
        if (cvui::mouse(cvui::CLICK)) {
            cvui::text(frame, 10, 70, "Mouse was clicked!");
        }



        // 버튼을 뗀 상태면 rectangular 관련 모든 값이 0이 된다.
        // 누르는 상태라면 값이 전부 정해진 상태
        // cvui::rect를 통해 해당 frame에 직사각형을 그릴 수 있다.
        cvui::rect(frame, rectangle.x, rectangle.y, rectangle.width, rectangle.height, 0xff0000, 0xd00000ff);





        cvui::update();


        cv::imshow(WINDOW_NAME, frame);

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
