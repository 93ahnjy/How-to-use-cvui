/*
실시간으로 이미지의 RGB, HSV 바꿔버리기
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"CVUI Test"

int main(int argc, const char *argv[])
{
    cv::Mat lena = cv::imread("/home/nvidia/cvui-2.7.0/example/data/lena.jpg");
    cv::Mat frame = lena.clone();
    cv::Mat doubleBuffer = frame.clone();
    int trackbarWidth = 130;

    // 아래처럼 cvui::init에서 waitKey값을 설정해 주면 cvui::update때 여기 안에 있는 waitKey가 그 값에 맞춰 작동한다.
    cvui::init(WINDOW_NAME, 20);

    while (true) {
        doubleBuffer.copyTo(frame);

        // 구석에 Quit버튼을 만든다. &을 붙이면 버튼 이름의 첫 글자를 눌러도 버튼이 눌리는 shortcut이 만들어진다.
        if (cvui::button(frame, frame.cols - 100, frame.rows - 30, "&Quit")) {
            break;
        }

        // RGB HUD
        cvui::window(frame, 20, 50, 180, 240, "RGB adjust");




        // trackbar 배열하기.
        cvui::beginColumn(frame, 35, 80, -1, -1, 10);
            static double rgb[3] {1., 1., 1};
            bool rgbModified = false;


            // trackbar는 값이 바뀌면 true를 return한다.
            // 원문은 They return true upon edition
            // rgb의 픽셀값을 직접 바꾸는게 아니라 '비율'로 조절 (0 ~ 1)
            if (cvui::trackbar(trackbarWidth, &rgb[0], (double)0., (double)2., 2, "%3.02Lf")) {
                rgbModified = true;
            }
            if (cvui::trackbar(trackbarWidth, &rgb[1], (double)0., (double)2., 2, "%3.02Lf")) {
                rgbModified = true;
            }
            if (cvui::trackbar(trackbarWidth, &rgb[2], (double)0., (double)2., 2, "%3.02Lf")) {
                rgbModified = true;
            }

            cvui::space(2);
            cvui::printf(0.35, 0xcccccc, "   RGB: %3.02lf,%3.02lf,%3.02lf", rgb[0], rgb[1], rgb[2]);


            // cv::merge는 각 r,g,b 따로따로 나누어 처리한 이미지를 다시 하나의 color 이미지로 합쳐준다.
            if (rgbModified) {
                std::vector<cv::Mat> channels(3);
                cv::split(lena, channels);
                for (int c = 0; c < 3; c++) {
                    channels[c] = channels[c] * rgb[c];
                }
                cv::merge(channels, doubleBuffer);
            }
        cvui::endColumn();




        // HSV에 대해서도 마찬가지
        cvui::window(frame, lena.cols - 200, 50, 180, 240, "HSV adjust");
        cvui::beginColumn(frame, lena.cols - 180, 80, -1, -1, 10);
            static double hsv[3] {1., 1., 1};
            bool hsvModified = false;

            if (cvui::trackbar(trackbarWidth, &hsv[0], (double)0., (double)2., 2, "%3.02Lf")) {
                hsvModified = true;
            }
            if (cvui::trackbar(trackbarWidth, &hsv[1], (double)0., (double)2., 2, "%3.02Lf")) {
                hsvModified = true;
            }
            if (cvui::trackbar(trackbarWidth, &hsv[2], (double)0., (double)2., 2, "%3.02Lf")) {
                hsvModified = true;
            }

            cvui::space(2);
            cvui::printf(0.35, 0xcccccc, "   HSV: %3.02lf,%3.02lf,%3.02lf", hsv[0], hsv[1], hsv[2]);



            if (hsvModified) {
                cv::Mat hsvMat;
                cv::cvtColor(lena, hsvMat, cv::COLOR_BGR2HSV);
                std::vector<cv::Mat> channels(3);
                cv::split(hsvMat, channels);

                for (int c = 0; c < 3; c++) {
                    channels[c] = channels[c] * hsv[c];
                }

                cv::merge(channels, hsvMat);
                cv::cvtColor(hsvMat, doubleBuffer, cv::COLOR_HSV2BGR);
            }
        cvui::endColumn();





        cvui::printf(frame, frame.cols - 300, frame.rows - 20, 0.4, 0xCECECE, "cvui v.%s", cvui::VERSION);

        cvui::update();

        cv::imshow(WINDOW_NAME, frame);
    }

    return 0;
}
