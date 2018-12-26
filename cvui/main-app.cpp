/*
This is a demo application to showcase the UI components of cvui.

Copyright (c) 2016 Fernando Bevilacqua <dovyski@gmail.com>
Licensed under the MIT license.
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>




// 반드시 미리 설정 해놓기
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"CVUI Test"


// 여러가지 gui 예시 보여주기

int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(300, 600, CV_8UC3);
    bool checked = false;
    bool checked2 = true;
    int count = 0;
    double countFloat = 0.0;
    double trackbarValue = 0.0;

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);


        // 텍스트 보여주기
        cvui::text(frame, 50, 30, "Hey there!");


        // cvui::text에서는 글자 크기 및 색깔까지 바로 바꿀 수 있다!!!
        cvui::text(frame, 200, 30, "Use hex 0xRRGGBB colors easily", 0.4, 0xff0000);


        //cvui::printf로 특정 변수를 printf 할 수도 있다. 색 입히기도 가능!
        cvui::printf(frame, 200, 50, 0.4, 0x00ff00, "Use printf formatting: %d + %.2f = %f", 2, 3.2, 5.2);



        // 평범한 버튼 클릭
        if (cvui::button(frame, 50, 60, "Button")) {
            std::cout << "Button clicked" << std::endl;
        }


        // 만일 버튼 이름이 너무 길다 해도 자동으로 그 크기에 버튼 크기가 맞춰진다.
        cvui::button(frame, 200, 70, "Button with large label");


        // 버튼 크기 조절을 입맛대로 !!
        cvui::button(frame, 410, 70, 15, 15, "x");


        //cvui::window로 head up display 가능
        cvui::window(frame, 50, 120, 120, 100, "Window");


        // cvui::counter를 사용하면 - + 버튼이 생기고 가운데 변수값이 표시된다.
        // 버튼 눌러서 변수값을 늘렸다 줄였다 가능
        cvui::counter(frame, 200, 120, &count);


        // 소수점 단위로 늘릴 수도 있다. 중간에 step size 설정 가능.
        // 출력시 소수점 출력범위도 추가 가능
        cvui::counter(frame, 320, 120, &countFloat, 0.1, "%.1f");



        //cvui::trackbar에서 trackbar 들어갈 이미지/ 이미지의 어느 위치/ trackbar 길이/ &변화시킬 값/ 최소범위/ 최대범위 등을 설정할 수 있다.
        cvui::trackbar(frame, 420, 110, 150, &trackbarValue, 0., 50.);

        // //cvui::checkbox 설정 시 &(변수)의 변수를 미리 true로 해놓으면 미리 체크 된 채로 설정할 수 있다.
        cvui::checkbox(frame, 200, 160, "Checkbox", &checked);
        cvui::checkbox(frame, 200, 190, "A checked checkbox", &checked2);



        // Display the lib version at the bottom of the screen
        cvui::printf(frame, frame.cols - 80, frame.rows - 20, 0.4, 0xCECECE, "cvui v.%s", cvui::VERSION);


        cvui::update();

        cv::imshow(WINDOW_NAME, frame);

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
