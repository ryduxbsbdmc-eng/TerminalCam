#include "TerminalCam.h"
#include <iostream>

int main() {
    std::cout << "Starting application..." << std::endl;
    TerminalCam cam(0); 

    if (!cam.isOpened()) {
        std::cerr << "CRITICAL ERROR: Camera NOT found! (Index 0)" << std::endl;
        return -1;
    }

    std::cout << "Camera opened successfully. Press Ctrl+C to stop." << std::endl;

    while (true) {
        std::string frame = cam.getFrameAsAscii(100);
        if (frame.empty()) {
            std::cerr << "Error: Empty frame received!" << std::endl;
            break;
        }
        
        system("cls"); 
        std::cout << frame;
        cv::waitKey(30); 
    }

    return 0;
}