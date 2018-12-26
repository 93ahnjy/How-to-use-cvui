/*
This is an extremely simple demo application to showcase the
basic structure, features and use of cvui.

Code licensed under the MIT license, check LICENSE file.
*/

#include <opencv2/opencv.hpp>

// One (and only one) of your C++ files must define CVUI_IMPLEMENTATION
// before the inclusion of cvui.h to ensure its implementaiton is compiled.
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "CVUI Hello World!"

int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(200, 500, CV_8UC3);
    int count = 0;

    // cvui를 수행할 때 어느 window에서 시작할지를 정한다.
    // 오직 이 window내에 있는 gui만 수행된다.
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);

        // 클릭이 발생하면 True를 내놓는다. 그때마다 카운트 증가
        if (cvui::button(frame, 110, 80, "Hello, world!")) {
            // The button was clicked, so let's increment our counter.
            count++;
        }


        // cvui::printf를 이용하면 gui의 frame내부에 글이나 숫자 쓰기가 가능하다.
        cvui::printf(frame, 250, 90, 0.4, 0xff0000, "Button click count: %d", count);

        // GUI 보여주기
        cvui::imshow(WINDOW_NAME, frame);

        // Check if ESC key was pressed
        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
