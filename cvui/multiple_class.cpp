/*
This is application demonstrates how you can use cvui when your project has
multiple files that use cvui.

Code licensed under the MIT license, check LICENSE file.
*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>





#define CVUI_IMPLEMENTATION
#include "cvui.h"

// 해당 헤더랑 cpp 파일 반드시 추가
#include "/home/nvidia/cvui/multiple_files/Class1.h"
#include "/home/nvidia/cvui/multiple_files/Class2.h"

#define WINDOW_NAME "CVUI Multiple files"



// GUI 자체를 class 처럼 만들어 사용하기


int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(300, 500, CV_8UC3);

    Class1 c1;
    Class2 c2;

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);

        c1.renderInfo(frame);
        c2.renderMessage(frame);




        cvui::update();

        cv::imshow(WINDOW_NAME, frame);

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
