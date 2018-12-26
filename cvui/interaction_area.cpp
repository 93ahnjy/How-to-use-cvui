/*
This is a demo application to showcase how you can use an
interaction area (iarea). An iarea can be used to track mouse
interactions over an specific space.

Copyright (c) 2016 Fernando Bevilacqua <dovyski@gmail.com>
Licensed under the MIT license.
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>




// 이 두 가지 설정은 반드시 해줘야 한다!!!!
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Interaction area"



// 마우스의 위치 파악
// 특정 영역안에 마우스 들어왔는지 파악

int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(300, 600, CV_8UC3);

    // GUI 실행시작.
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);

        // 빨간색 직사각형 그리기
        cv::Rect rectangle(50, 50, 100, 100);
        cvui::rect(frame, rectangle.x, rectangle.y, rectangle.width, rectangle.height, 0xff0000);



        // cvui::iarea()에는 사각형의 x,y,w,h 값이 들어간다.
        // 해당 ROI와 마우스와의 상태를 int 값으로 출력
        int status = cvui::iarea(rectangle.x, rectangle.y, rectangle.width, rectangle.height);


        switch (status) {
            case cvui::CLICK:	std::cout << "Rectangle was clicked!" << std::endl; break;
            case cvui::DOWN:	cvui::printf(frame, 240, 70, "Mouse is: DOWN"); break;
            case cvui::OVER:	cvui::printf(frame, 240, 70, "Mouse is: OVER"); break;
            case cvui::OUT:		cvui::printf(frame, 240, 70, "Mouse is: OUT"); break;
        }

        // cvui::mouse()를 사용하면 Point 형태로 값을 마우스 위치를 출력한다.
        cvui::printf(frame, 240, 50, "Mouse pointer is at (%d,%d)", cvui::mouse().x, cvui::mouse().y);




        cvui::update();

        cv::imshow(WINDOW_NAME, frame);

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
