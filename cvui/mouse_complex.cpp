/*
This is application uses the mouse API to dynamically create a ROI
for image visualization.

Copyright (c) 2017 Fernando Bevilacqua <dovyski@gmail.com>
Licensed under the MIT license.
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>





#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Mouse - ROI interaction"
#define ROI_WINDOW	"ROI"


// 마우스로 ROI를 잡아 그 부분만 다른 창에서 출력하기


int main(int argc, const char *argv[])
{
    cv::Mat lena = cv::imread("/home/nvidia/cvui-2.7.0/example/data/lena.jpg");
    cv::Mat frame = lena.clone();
    cv::Point anchor;
    cv::Rect roi(0, 0, 0, 0);
    bool working = false;

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with Lena's image
        lena.copyTo(frame);

        // 마우스 위치
        cvui::text(frame, 10, 10, "Click (any) mouse button and drag the pointer around to select a ROI.");



        // 첫 마우스 단추 눌러서 시작 지점 저장
        if (cvui::mouse(cvui::DOWN)) {
            // Position the anchor at the mouse pointer.
            anchor.x = cvui::mouse().x;
            anchor.y = cvui::mouse().y;

            // Inform we are working, so the ROI window is not updated every frame
            working = true;
        }



        // 만일 계속 눌러져 있으면 움직이면서 rectangular 관련 값들을 구하자.
        // 무조건 북서쪽 꼭지점이 x,y가 되어야 한다.

        if (cvui::mouse(cvui::IS_DOWN)) {
            // Adjust roi dimensions according to mouse pointer
            int width = cvui::mouse().x - anchor.x;
            int height = cvui::mouse().y - anchor.y;

            roi.x = width < 0 ? anchor.x + width : anchor.x;
            roi.y = height < 0 ? anchor.y + height : anchor.y;
            roi.width = std::abs(width);
            roi.height = std::abs(height);

            // 그려지는 사각형의 가로/세로 값을 마우스 포인터 위치에 표시
            cvui::printf(frame, roi.x + 5, roi.y + 5, 0.3, 0xff0000, "(%d,%d)", roi.x, roi.y);
            cvui::printf(frame, cvui::mouse().x + 5, cvui::mouse().y + 5, 0.3, 0xff0000, "w:%d, h:%d", roi.width, roi.height);
        }


        // 마우스 떼어야 ROI로 잘라내기 가능. 이와 관련 flag 세우기
        if (cvui::mouse(cvui::UP)) {
            // We are done working with the ROI.
            working = false;
        }


        //ROI가 원본 바깥으로 안나가도록 설정
        roi.x = roi.x < 0 ? 0 : roi.x;
        roi.y = roi.y < 0 ? 0 : roi.y;
        roi.width = roi.x + roi.width > lena.cols ? roi.width + lena.cols - (roi.x + roi.width) : roi.width;
        roi.height = roi.y + roi.height > lena.rows ? roi.height + lena.rows - (roi.y + roi.height) : roi.height;

        //직사각형 그리기
        cvui::rect(frame, roi.x, roi.y, roi.width, roi.height, 0xff0000);



        cvui::update();

        cv::imshow(WINDOW_NAME, frame);


        // lena의 ROI만 보여주기
        if (roi.area() > 0 && !working) {
            cv::imshow(ROI_WINDOW, lena(roi));
        }

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
