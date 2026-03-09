#include "TerminalCam.h"

TerminalCam::TerminalCam(int deviceID) {
    // Пробуем разные API для Windows
    std::vector<int> backends = {cv::CAP_DSHOW, cv::CAP_MSMF, cv::CAP_ANY};
    for (int api : backends) {
        cap.open(deviceID, api);
        if (cap.isOpened()) break;
    }
}

TerminalCam::~TerminalCam() {
    if (cap.isOpened()) cap.release();
}

bool TerminalCam::isOpened() const {
    return cap.isOpened();
}

std::string TerminalCam::getFrameAsColor(int targetWidth, int targetHeight) {
    cv::Mat frame, smallFrame;
    if (!cap.read(frame)) return "";

    // Ресайз под размер терминала (высота должна быть четной)
    cv::resize(frame, smallFrame, cv::Size(targetWidth, targetHeight));

    std::string buffer = "\033[H"; // Возврат курсора в начало

    for (int i = 0; i < smallFrame.rows; i += 2) {
        for (int j = 0; j < smallFrame.cols; j++) {
            cv::Vec3b topP = smallFrame.at<cv::Vec3b>(i, j);
            cv::Vec3b botP = smallFrame.at<cv::Vec3b>(i + 1, j);

            // \033[38;2;R;G;Bm - цвет текста
            // \033[48;2;R;G;Bm - цвет фона
            buffer += "\033[38;2;" + std::to_string(topP[2]) + ";" + std::to_string(topP[1]) + ";" + std::to_string(topP[0]) + "m";
            buffer += "\033[48;2;" + std::to_string(botP[2]) + ";" + std::to_string(botP[1]) + ";" + std::to_string(botP[0]) + "m";
            
            buffer += "\u2580"; // Символ верхнего полублока
        }
        buffer += "\033[0m\n"; // Сброс цвета в конце строки
    }
    return buffer;
}