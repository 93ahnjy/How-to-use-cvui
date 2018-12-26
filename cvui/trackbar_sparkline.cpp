/*
trackbar의 위치를 계속 그래프로 그려준다.
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Trackbar and sparkline"

int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(300, 800, CV_8UC3);
    double value = 2.25;
    std::vector<double> values;

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);

        // In a row, all added elements are
        // horizontally placed, one next the other (from left to right)
        //
        // Within the cvui::beginRow() and cvui::endRow(),
        // all elements will be automatically positioned by cvui.
        //
        // Notice that all component calls within the begin/end block
        // DO NOT have (x,y) coordinates.
        //
        // Let's create a row at position (20,80) with automatic width and height, and a padding of 10
        cvui::beginRow(frame, 20, 80, -1, -1, 10);


            // trackbar가 변화한게 확인이 되면 해당값을 데이터 array에 추가
            if (cvui::trackbar(150, &value, 0., 5.)) {
                std::cout << "Trackbar was modified, value : " << value << std::endl;
                values.push_back(value);
            }


            // 점이 5개 이상 저장될 때부터 그래프 여기 그려진다고 알려준다.
            // 그려지는 것도 그때부터
            if (values.size() > 5) {
                cvui::text("Your edits on a sparkline ->");
                cvui::sparkline(values, 240, 60);

                if (cvui::button("Clear sparkline")) {
                    values.clear();
                }
            }

            else {
                cvui::text("<- Move the trackbar");
            }
        cvui::endRow();






        cvui::update();

        cv::imshow(WINDOW_NAME, frame);

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
