/*
This is a demo application to showcase the image button component.

Copyright (c) 2016 Fernando Bevilacqua <dovyski@gmail.com>
Licensed under the MIT license.
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Image button"

using namespace cv;


int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(300, 600, CV_8UC3, cv::Scalar(0));
    cv::Mat out = cv::imread("/home/nvidia/cvui-2.7.0/example/data/lena-face.jpg", cv::IMREAD_COLOR);
    cv::Mat down = cv::imread("/home/nvidia/cvui-2.7.0/example/data/lena-face-red.jpg", cv::IMREAD_COLOR);
    cv::Mat over = cv::imread("/home/nvidia/cvui-2.7.0/example/data/lena-face-gray.jpg", cv::IMREAD_COLOR);

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);


        // 저기서 out, over, down은 각각 이미지가 들어가며
        // 각각 마우스 state가 이미지 벗어남/ 마우스가 이미지 위에/ 이미지 누르는 중/  해당하는 이미지가 뜬다.
        // 클릭시 True가 return되는 건 덤
        if (cvui::button(frame, 200, 80, out, over, down)) {
            std::cout << "Image button clicked!" << std::endl;
        }
        cvui::text(frame, 150, 200, "This image behaves as a button");



        // 이건 평범한 버튼 설정.
        if (cvui::button(frame, 360, 80, "Button")) {
            std::cout << "Regular button clicked!" << std::endl;
        }


        // 반드시 UI component 전부 사용한 뒤에 이게 나와줘야 한다.
        // 마우스 클릭 관련된건 이것 덕분에 사용이 가능함.
        cvui::update();

        // Show everything on the screen
        cv::imshow(WINDOW_NAME, frame);

        // Check if ESC key was pressed
        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
