/*
multiple window gui에 버튼 누르면 오류창까지 띄우기
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define GUI_WINDOW1_NAME "Window 1"
#define GUI_WINDOW2_NAME "Window 2"
#define ERROR_WINDOW_NAME "Error window"



// getWindowProperty가 -1을 return했다는 것은 해당 window가 존재하지 않는다는 뜻
int isWindowOpen(const cv::String &name) {
    return cv::getWindowProperty(name, cv::WND_PROP_AUTOSIZE) != -1;
}

// Open a new OpenCV window and watch it using cvui
void openWindow(const cv::String &name) {
    cv::namedWindow(name);
    cvui::watch(name);
}

// Open an OpenCV window
void closeWindow(const cv::String &name) {
    cv::destroyWindow(name);

    // Ensure OpenCV window event queue is processed, otherwise the window
    // will not be closed.
    cv::waitKey(1);
}







int main(int argc, const char *argv[])
{
    // We have one mat for each window.
    cv::Mat frame1 = cv::Mat(150, 600, CV_8UC3);
    cv::Mat frame2 = cv::Mat(150, 600, CV_8UC3);
    cv::Mat error_frame = cv::Mat(100, 300, CV_8UC3);


    // error를 나타낼 때를 판단할 때 사용할 flag.
    bool error = false;


    // Create two OpenCV windows
    cv::namedWindow(GUI_WINDOW1_NAME);
    cv::namedWindow(GUI_WINDOW2_NAME);



    // 자기만의 window에서 gui를 만들고 싶다면 반드시 namedWindow 함수를 통해 미리 만들어놔라.
    cvui::init(GUI_WINDOW1_NAME);

    // 이걸 이용해야 다른 창에서도 마우스 움직임도 파악할수 있게 된다.
    cvui::watch(GUI_WINDOW2_NAME);

    while (true) {

        // gui 여러 군데 돌릴 거임 ㅇㅇ
        cvui::context(GUI_WINDOW1_NAME);


        // Fill the frame with a nice color
        frame1 = cv::Scalar(49, 52, 49);

        cvui::beginColumn(frame1, 50, 20, -1, -1, 10);
            cvui::text("[Win1] Use the buttons below to control the error window");


            // 우선 cvui::button이 조건문에라도 존재라도 한다면 일단 버튼은 생긴다.
            // Close를 누르면 error창이 꺼지고, open을 누르면 error flag와 함께 error창 발생

            if (cvui::button("Close")) {
                closeWindow(ERROR_WINDOW_NAME);
            }

            // openWindow 함수 안에는 error창에 대해서도 cvui::watch가 존재해서 해당 error창도 gui 작동 가능하다.
            if (cvui::button("Open")) {
                error = true;
                openWindow(ERROR_WINDOW_NAME);
            }
        cvui::endColumn();

        cvui::update(GUI_WINDOW1_NAME);
        cv::imshow(GUI_WINDOW1_NAME, frame1);









        // window1과 똑같다.
        cvui::context(GUI_WINDOW2_NAME);
        frame2 = cv::Scalar(49, 52, 49);

        cvui::beginColumn(frame2, 50, 20, -1, -1, 10);
            cvui::text("[Win2] Use the buttons below to control the error window");

            if (cvui::button("Close")) {
                closeWindow(ERROR_WINDOW_NAME);
            }

            if (cvui::button("Open")) {
                openWindow(ERROR_WINDOW_NAME);
                error = true;
            }
        cvui::endColumn();

        cvui::update(GUI_WINDOW2_NAME);
        cv::imshow(GUI_WINDOW2_NAME, frame2);





        // error flag 떴고 에러창도 열려있는 상태이면 여기에 대한 gui도 실행
        if (error && isWindowOpen(ERROR_WINDOW_NAME)) {



            cvui::context(ERROR_WINDOW_NAME);

            // Fill the error window if a vibrant color
            error_frame = cv::Scalar(10, 10, 49);



            cvui::text(error_frame, 70, 20, "This is an error message", 0.4, 0xff0000);


            // close버튼 누르면 flag를 다시 내린다.
            if (cvui::button(error_frame, 110, 40, "Close")) {
                error = false;
            }


            // error flag가 다 끝날때까지는 update하면서 보여주기도 해야한다.
            if (error) {
                cvui::update(ERROR_WINDOW_NAME);
                cv::imshow(ERROR_WINDOW_NAME, error_frame);
            }

            else {
                closeWindow(ERROR_WINDOW_NAME);
            }
        }

        // Check if ESC key was pressed
        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
