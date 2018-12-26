/*
데이터 파일을 읽어다가 그래프 그리기 좋은 함수
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME	"Sparkline"

std::vector<double> load(std::string thePath) {
    std::vector<double> data;
    double time, value;
    std::ifstream file(thePath.c_str());

    if (!file)	{
        throw std::runtime_error("Unable to open file");
    }

    while (file >> time >> value) {
        data.push_back(value);
    }

    return data;
}

int main(int argc, const char *argv[])
{
    cv::Mat frame = cv::Mat(600, 800, CV_8UC3);

    cvui::init(WINDOW_NAME);

    std::vector<double> points = load("/home/nvidia/cvui-2.7.0/example/data/sparkline.csv");



    // few_points에는 30개 데이터만, no_points에는 아예 데이터 없이
    std::vector<double> few_points;
    std::vector<double> no_points;


    for (std::vector<double>::size_type i = 0; i < 30; i++) {
        few_points.push_back(rand() + 0.);
    }

    while (true) {
        // Fill the frame with a nice color
        frame = cv::Scalar(49, 52, 49);

        // cvui::sparkline의 4개의 숫자는 rect처럼 표현되는 그래프 영역크기 및 위치 표현
        cvui::sparkline(frame, points, 0, 0, 800, 200);
        cvui::sparkline(frame, points, 0, 200, 800, 100, 0xff0000);
        cvui::sparkline(frame, points, 0, 300, 400, 100, 0x0000ff);


        // Add a sparkline with few points
        cvui::sparkline(frame, few_points, 10, 400, 790, 80, 0xff00ff);

        // 데이터 아예 없어도 동작은 한다. 다만 data없다고 경고함
        cvui::sparkline(frame, no_points, 10, 500, 750, 100, 0x0000ff);






        cvui::update();

        cv::imshow(WINDOW_NAME, frame);

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}

