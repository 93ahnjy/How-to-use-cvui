/*
This is a demo application to showcase keyboard shortcuts.
Author: Pascal Thomet
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Button shortcut"

int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(cv::Size(650, 150), CV_8UC3);

    // Init cvui and tell it to use a value of 20 for cv::waitKey()
    // because we want to enable keyboard shortcut for
    // all components, e.g. button with label "&Quit".
    // If cvui has a value for waitKey, it will call
    // waitKey() automatically for us within cvui::update().
    cvui::init(WINDOW_NAME, 1);

    while (true) {

        // 이 부분은 '배경초기화' 역할하므로 반드시 있어야 한다.  안그러면 이전 상태 gui기 지워지지 않고 계속 덧그려진다.
        frame = cv::Scalar(49, 52, 49);

        cvui::text(frame, 40, 40, "To exit this app click the button below or press Q (shortcut for the button below).");


        // 버튼 이름 앞에 &를 붙이면 버튼 이름 앞글자에 밑줄이 그어진다. 그걸 키보드로 누르면 버튼이 눌러지는 효과!!!
        if (cvui::button(frame, 300, 80, "&Exit")) {
            break;
        }

        // Since cvui::init() received a param regarding waitKey,
        // there is no need to call cv::waitKey() anymore. cvui::update()
        // will do it automatically.
        cvui::update();

        cv::imshow(WINDOW_NAME, frame);
    }

    return 0;
}
