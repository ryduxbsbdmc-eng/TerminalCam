#ifndef TERMINAL_CAM_H
#define TERMINAL_CAM_H

#include <opencv2/opencv.hpp>
#include <string>

class TerminalCam {
public:
    TerminalCam(int deviceID = 0);
    ~TerminalCam();
    bool isOpened() const;

    // Новый метод для цветного вывода
    std::string getFrameAsColor(int targetWidth = 120, int targetHeight = 60);

private:
    cv::VideoCapture cap;
};

#endif