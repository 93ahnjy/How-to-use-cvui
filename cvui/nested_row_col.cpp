/*
만일 beginRow안에 beginColumn이 있다면?
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Nested rows and columns"


int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(600, 800, CV_8UC3);
    std::vector<double> values;
    bool checked = false;
    double value = 1.0;

    // Fill the vector with a few random values
    for (std::vector<double>::size_type i = 0; i < 20; i++) {
        values.push_back(rand() + 0.);
    }

    // Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
    cvui::init(WINDOW_NAME);

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);


        cvui::beginRow(frame, 10, 50, 100, 150);
            cvui::text("Row starts");
            cvui::button("here");


            // beginRow도중에 beginColumn이 생겨도 원래 다른 gui가 올 공간에 'gui 열'이 오는것 뿐이다.
            // 참고로 다시 Row가 시작되면 beginColumn의 크기만큼 알아서 건너뛰기 때문에 걱정 ㄴㄴ
            cvui::beginColumn(100, 150);
                cvui::text("Column 1");
                cvui::button("button1");
                cvui::button("button2");
                cvui::button("button3");
                cvui::text("End of column 1");
            cvui::endColumn();


            // Add two pieces of text
            cvui::text("Hi again,");
            cvui::text("its me!");



            // Start a new column
            cvui::beginColumn(100, 50);
                cvui::text("Column 2");
                cvui::button("button1");
                cvui::button("button2");
                cvui::button("button3");
                cvui::space();
                cvui::text("Another text");
                cvui::space(40);
                cvui::text("End of column 2");
            cvui::endColumn();



            // Add more text
            cvui::text("this is the ");
            cvui::text("end of the row!");
        cvui::endRow();



        // Here is another nested row/column
        cvui::beginRow(frame, 50, 300, 100, 150);

            // 구지 beginColumn의 위치, 크기를 지정하지 않아도, '알아서' 적절한 위치를 선정해주니 걱정 ㄴㄴ
            cvui::beginColumn();
                cvui::text("Column 1");
                cvui::button("button with very large label");
                cvui::text("End of column 1");
            cvui::endColumn();

            // Add two pieces of text
            cvui::text("Hi again,");
            cvui::text("its me!");

            // Start a new column
            cvui::beginColumn();
                cvui::text("Column 2");

                cvui::button("btn");
                cvui::space();
                cvui::text("text");
                cvui::button("btn2");
                cvui::text("text2");
                if (cvui::button("&Quit")) {
                    break;
                }
            cvui::endColumn();

            // Add more text
            cvui::text("this is the ");
            cvui::text("end of the row!");
        cvui::endRow();



        cvui::update();

        cv::imshow(WINDOW_NAME, frame);

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
