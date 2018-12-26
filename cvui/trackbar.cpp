/*
This is a demo application to showcase the trackbar component.
Authors: Pascal Thomet, Fernando Bevilacqua
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Trackbar"

int main(int argc, const char *argv[])
{
    int intValue = 30;
    uchar ucharValue = 30;
    char charValue = 30;
    float floatValue = 12.;
    double doubleValue = 45., doubleValue2 = 15., doubleValue3 = 10.3;
    cv::Mat frame = cv::Mat(770, 350, CV_8UC3);

    // The width of all trackbars used in this example.
    int width = 300;

    // The x position of all trackbars used in this example
    int x = 10;

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);


        // min, max 값 정할 땐 변수의 class 반드시 고려해서
        cvui::text(frame, x, 10, "double, step 1.0 (default)");
        cvui::trackbar(frame, x, 40, width, &doubleValue, (double)0., (double)100.);

        cvui::text(frame, x, 120, "float, step 1.0 (default)");
        cvui::trackbar(frame, x, 150, width, &floatValue, (float)10., (float)15.);




        // trackbar를 일정 구간 나누어 표현하는 것도 가능하다.
        // 나누어진 구간 경계는 항상 long double이다. 출력 표현은 항상 %.2LF 으로 하고, 정수표현은 %.0LF로 해서 소수점 없게
        cvui::text(frame, x, 230, "double, 4 segments, custom label %.2Lf");
        cvui::trackbar(frame, x, 260, width, &doubleValue2, (double)0., (double)20., 4, "%.2Lf");



        // trackbar에서 모든 min, max값은 그냥 전부 cast 시켜버리자.
        cvui::text(frame, x, 340, "uchar, custom label %.0Lf");
        cvui::trackbar(frame, x, 370, width, &ucharValue, (uchar)0, (uchar)255, 0, "%.0Lf");






        //  TRACKBAR_DISCRETE | TRACKBAR_HIDE_LABELS 같은 설정도 추가해서(뒤에 discrete 간격은 알려줘야),
        //  trackbar가 끊어지게 움직이거나 경계값을 숨길 수도 있다.
        cvui::text(frame, x, 450, "double, step 0.1, option TRACKBAR_DISCRETE");
        cvui::trackbar(frame, x, 480, width, &doubleValue3, (double)10., (double)10.5, 1, "%.1Lf", cvui::TRACKBAR_DISCRETE, (double)0.1);


        unsigned int options = cvui::TRACKBAR_DISCRETE | cvui::TRACKBAR_HIDE_SEGMENT_LABELS;
        cvui::text(frame, x, 560, "int, 3 segments, DISCRETE | HIDE_SEGMENT_LABELS");
        cvui::trackbar(frame, x, 590, width, &intValue, (int)10, (int)50, 3, "%.0Lf", options, (int)2);




        // Trackbar using char type.
        cvui::text(frame, x, 670, "char, 2 segments, custom label %.0Lf");
        cvui::trackbar(frame, x, 700, width, &charValue, (char)-128, (char)127, 2, "%.0Lf");




        cvui::update();

        cv::imshow(WINDOW_NAME, frame);

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
