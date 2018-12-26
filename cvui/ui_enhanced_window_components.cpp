/*
This application showcases how the window component of cvui can be
enhanced, i.e. make it movable and minimizable.

Authors:
    ShengYu - https://github.com/shengyu7697
    Amaury Bréhéret - https://github.com/abreheret

Contributions:
    Fernando Bevilacqua <dovyski@gmail.com>

Code licensed under the MIT license.
*/

#include <opencv2/opencv.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

// Include the enhanced cvui window component
#include "EnhancedWindow.h"

#define WINDOW_NAME    "CVUI Enhanced Window Component"

int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(600, 800, CV_8UC3);
    int value = 50;

    EnhancedWindow settings(20, 80, 200, 120, "Settings");
    EnhancedWindow info(250, 80, 330, 60, "Info");

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);


        cvui::text(frame, 20, 20, "The Settings and the Info windows below are movable and minimizable.");
        cvui::text(frame, 20, 40, "Click and drag any window's title bar to move it around.");



        // enhanced window는 반드시 begin()을 통해 시작하고 end()를 통해 끝내야 한다.
        // 해당 enhanced window가 minimize 되지 않았다면 아래 gui들을 실행
        settings.begin(frame);
            if (!settings.isMinimized()) {
                cvui::text("Adjust something");
                cvui::space(10); // add 10px of space between UI components
                cvui::trackbar(settings.width() - 20, &value, 5, 150);
            }
        settings.end();






        // 여기도 마찬가지
        info.begin(frame);
        if (!info.isMinimized()) {
            cvui::text("Moving and minimizable windows are awesome!");
        }
        info.end();






        cvui::imshow(WINDOW_NAME, frame);
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    return 0;
}
