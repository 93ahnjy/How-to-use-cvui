/*
 이제는 여러 개의 창에다가 각각 gui를 만들 수도 있다.
 그러기 위해서는 cvui::contex(NAME)과 cvui::update(NAME) 사이에 gui를 call해야 한다.
 그래야 cvui가 지금 어느 window에서 gui를 이용중인 지를 알 수가 있다.

예시)

  // Code for window "window1".
  cvui::context("window1");
      cviu::text(frame, ...);
      cviu::button(frame, ...);
  cviu::update("window1");

  // somewhere else, code for "window2"
  cvui::context("window2");
      cviu::printf(frame, ...);
      cviu::printf(frame, ...);
  cviu::update("window2");

  // Show everything in a window
  cv::imshow(frame);





cvui::context(NAME)와 cviu::update(NAME) 사이에 gui가 불러지는 것을 잘 확인해라
cvui::imshow()를 하면 아래처럼 update와 cv::imshow를 동시에 해준다.

E.g.

  // Code for window "window1".
  cvui::context("window1");
      cviu::text(frame, ...);
      cviu::button(frame, ...);
  cviu::imshow("window1");

  // somewhere else, code for "window2"
  cvui::context("window2");
      cviu::printf(frame, ...);
      cviu::printf(frame, ...);
  cviu::imshow("window2");
*/





#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW1_NAME "Window 1"
#define WINDOW2_NAME "Windows 2"
#define WINDOW3_NAME "Windows 3"
#define WINDOW4_NAME "Windows 4"

// Update a window using cvui functions, then show it using cv::imshow().
void window(const cv::String& name) {

    // Create a frame for this window and fill it with a nice color
    cv::Mat frame = cv::Mat(200, 500, CV_8UC3);
    frame = cv::Scalar(49, 52, 49);


    // 특정 window에서 gui 수행할 것임을 cvui에게 알려준다.
    cvui::context(name);


    // window 정보출력
    cvui::printf(frame, 110, 50, "%s - click the button", name.c_str());


    // 버튼출력 출력
    if (cvui::button(frame, 110, 90, "Button")) {
        cvui::printf(frame, 200, 95, "Button clicked!");
        std::cout << "Button clicked on: " << name << std::endl;
    }

    // 여기가 cvui::context(name)의 끝
    cvui::update(name);


    // Show the content of this window on the screen
    cvui::imshow(name, frame);
}



//위 코드에서 cvui::imshow()로 update 과정만 생략
void compact(const cv::String& name) {
    // Create a frame for this window and fill it with a nice color
    cv::Mat frame = cv::Mat(200, 500, CV_8UC3);
    frame = cv::Scalar(49, 52, 49);

    cvui::context(name);

    cvui::printf(frame, 110, 50, "%s - click the button", name.c_str());
    if (cvui::button(frame, 110, 90, "Button")) {
        cvui::printf(frame, 200, 95, "Button clicked!");
        std::cout << "Button clicked on: " << name << std::endl;
    }

    cvui::imshow(name, frame);
}









int main(int argc, const char *argv[])
{
    // cvui에서 init를 4개를 할 것임을 알려준다. 단, 이 때 window 이름 변수 또한 array여야 한다.
    const cv::String windows[] = { WINDOW1_NAME, WINDOW2_NAME, WINDOW3_NAME, WINDOW4_NAME };
    cvui::init(windows, 4);

    while (true) {

        // window 함수 하나당 gui가 call되었다가 update되며 끝난다.
        window(WINDOW1_NAME);
        window(WINDOW2_NAME);
        window(WINDOW3_NAME);

        // 얘는 compact 코드를 사용. 당연히 결과는 똑같다.
        compact(WINDOW4_NAME);

        // Check if ESC key was pressed
        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}
