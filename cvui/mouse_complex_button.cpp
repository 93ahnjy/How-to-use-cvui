/*
This is application uses the fine details of the mouse API to dynamically
create ROIs for image visualization based on different mouse buttons.

This demo is very similiar to "mouse-complex", except that it handles 3 ROIs,
one for each mouse button.

Copyright (c) 2017 Fernando Bevilacqua <dovyski@gmail.com>
Licensed under the MIT license.
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>




#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Mouse complex buttons- ROI interaction"


//마우스 버튼 별로 서로 다른 rect 및 ROI 출력


int main(int argc, const char *argv[])
{
    cv::Mat lena = cv::imread("/home/nvidia/cvui-2.7.0/example/data/lena.jpg");
    cv::Mat frame = lena.clone();
    cv::Point anchors[3]; // one anchor for each mouse button
    cv::Rect rois[3]; // one ROI for each mouse button
    unsigned int colors[] = { 0xff0000, 0x00ff00, 0x0000ff };

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    while (true) {

        lena.copyTo(frame);

        cvui::text(frame, 10, 10, "Click (any) mouse button then drag the pointer around to select a ROI.");
        cvui::text(frame, 10, 25, "Use different mouse buttons (right, middle and left) to select different ROIs.");



        // Iterate all mouse buttons (left, middle  and right button).
        for (int button = cvui::LEFT_BUTTON; button <= cvui::RIGHT_BUTTON; button++) {
            // Get the anchor, ROI and color associated with the mouse button
            cv::Point& anchor = anchors[button];
            cv::Rect& roi = rois[button];
            unsigned int color = colors[button];




            // Did the mouse button go down?
            if (cvui::mouse(button, cvui::DOWN)) {
                // Position the anchor at the mouse pointer.
                anchor.x = cvui::mouse().x;
                anchor.y = cvui::mouse().y;
            }


            // Is any mouse button down (pressed)?
            if (cvui::mouse(button, cvui::IS_DOWN)) {
                // Adjust roi dimensions according to mouse pointer
                int width = cvui::mouse().x - anchor.x;
                int height = cvui::mouse().y - anchor.y;

                roi.x = width < 0 ? anchor.x + width : anchor.x;
                roi.y = height < 0 ? anchor.y + height : anchor.y;
                roi.width = std::abs(width);
                roi.height = std::abs(height);

                // Show the roi coordinates and size
                cvui::printf(frame, roi.x + 5, roi.y + 5, 0.3, color, "(%d,%d)", roi.x, roi.y);
                cvui::printf(frame, cvui::mouse().x + 5, cvui::mouse().y + 5, 0.3, color, "w:%d, h:%d", roi.width, roi.height);
            }


            // ROI가 frame 경계 넘어가지 않게
            roi.x = roi.x < 0 ? 0 : roi.x;
            roi.y = roi.y < 0 ? 0 : roi.y;
            roi.width = roi.x + roi.width > lena.cols ? roi.width + lena.cols - (roi.x + roi.width) : roi.width;
            roi.height = roi.y + roi.height > lena.rows ? roi.height + lena.rows - (roi.y + roi.height) : roi.height;




            // 각 버튼에 대하여 해당하는 ROI가 존재하면 lena에서 그부분만 따오기.
            if (roi.area() > 0) {
                cvui::rect(frame, roi.x, roi.y, roi.width, roi.height, color);
                cvui::printf(frame, roi.x + 5, roi.y - 10, 0.3, color, "ROI %d", button);

                cv::imshow("ROI button" + std::to_string(button), lena(roi));
            }
        }






        cvui::update();


        cv::imshow(WINDOW_NAME, frame);



        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
