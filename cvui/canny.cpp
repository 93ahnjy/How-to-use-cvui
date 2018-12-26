#include <iostream>

#include <stdio.h>
#include <iostream>
#include <sstream>


#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/core.hpp"

#include "opencv2/cudawarping.hpp"
#include "opencv2/cudaimgproc.hpp"
#include "opencv2/cudaarithm.hpp"

#define CVUI_IMPLEMENTATION
#include "cvui.h"
#define WINDOW_NAME	"CVUI Canny Edge"
#define GUI_NAME	"Settings"

using namespace std;
using namespace cv;

int canny(int argc, const char *argv[])
{
    cv::Mat lena = cv::imread("/home/nvidia/cvui-2.7.0/example/data/lena.jpg");
    cv::Mat frame = lena.clone();
    cv::Mat Settings = Mat(lena.rows, lena.cols, CV_8UC3);
    int low_threshold = 50, high_threshold = 150;
    bool use_canny = false;

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(GUI_NAME);

    while (true) {
        // Should we apply Canny edge?
        if (use_canny) {
            // Yes, we should apply it.
            cv::cvtColor(lena, frame, CV_BGR2GRAY);
            cv::Canny(frame, frame, low_threshold, high_threshold, 3);
            cv::cvtColor(frame, frame, CV_GRAY2BGR);
        } else {
            // No, so just copy the original image to the displaying frame.
            lena.copyTo(frame);
        }

        // Render the settings window to house the checkbox
        // and the trackbars below.
        cvui::window(Settings, 10, 50, 180, 180, "Settings");

        // Checkbox to enable/disable the use of Canny edge
        cvui::checkbox(Settings, 15, 80, "Use Canny Edge", &use_canny);

        // Two trackbars to control the low and high threshold values
        // for the Canny edge algorithm.
        cvui::trackbar(Settings, 15, 110, 165, &low_threshold, 5, 150);
        cvui::trackbar(Settings, 15, 180, 165, &high_threshold, 80, 300);

        // This function must be called *AFTER* all UI components. It does
        // all the behind the scenes magic to handle mouse clicks, etc.
        cvui::update();

        // Show everything on the screen
        cv::imshow(WINDOW_NAME, frame);
        cv::imshow(GUI_NAME, Settings);

        // Check if ESC was pressed
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    return 0;
}
