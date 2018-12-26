/*
이제는 창이 움직일 수도 있고, 최소화 기능도 생겼다.
*/

#include <opencv2/opencv.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

// Include the class that provides an enhanced cvui window component
#include "EnhancedWindow.h"

#define WINDOW_NAME	"CVUI Ehnanced UI Canny Edge"

int main(int argc, const char *argv[])
{
    cv::Mat fruits = cv::imread("/home/nvidia/cvui-2.7.0/example/data/fruits.jpg");
    cv::Mat frame = fruits.clone();
    int low_threshold = 50, high_threshold = 150;
    bool use_canny = false;




    // 부르기도 쉽다.           x,  y,   w,   h
    EnhancedWindow settings(10, 50, 270, 180, "Settings");
    EnhancedWindow settings2(10, 50, 270, 180, "Settings");


    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);




    while (true) {


        // Should we apply Canny edge?
        if (use_canny) {

            // Yes, we should apply it.
            cv::cvtColor(fruits, frame, CV_BGR2GRAY);
            cv::Canny(frame, frame, low_threshold, high_threshold, 3);
            cv::cvtColor(frame, frame, CV_GRAY2BGR);
        }

        else {
            // No, so just copy the original image to the displaying frame.
            fruits.copyTo(frame);
        }

        // 만일 enhanced window가 minimize 상태가 아니라면 다음 gui들을 만든다.
        // enhanced window는 반드시 begin()을 통해 시작하고 end()를 통해 끝내야 한다.
        settings.begin(frame);
            if (!settings.isMinimized()) {
                cvui::checkbox("Use Canny Edge", &use_canny);
                cvui::trackbar(settings.width() - 20, &low_threshold, 5, 150);
                cvui::trackbar(settings.width() - 20, &high_threshold, 80, 300);
                cvui::space(20); // add 20px of empty space
                cvui::text("Drag and minimize this settings window", 0.4, 0xff0000);
            }
        settings.end();

        /*
        settings2.begin(frame);
            if (!settings2.isMinimized()) {

                cvui::text("Drag and minimize this settings window", 0.4, 0xff0000);
            }
        settings2.end();
        */

        cvui::imshow(WINDOW_NAME, frame);

        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    return 0;
}
