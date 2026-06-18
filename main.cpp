#include "TerminalCam.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    // 1. Настройка кодировки UTF-8 для Windows, чтобы корректно отображать символ полублока ▀
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

    // 2. Инициализация камеры через нашу библиотеку
    // Индекс 0 - стандартная вебкамера
    TerminalCam cam(0);

    if (!cam.isOpened()) {
        std::cerr << " ОШИБКА: Камера не найдена или занята другим приложением!" << std::endl;
        return -1;
    }

    // 3. Скрываем курсор, чтобы он не мерцал при отрисовке
    std::cout << "\033[?25l";

    std::cout << "Приложение запущено. Нажмите ESC в окне OpenCV или Ctrl+C здесь для выхода." << std::endl;

    try {
        while (true) {
            // 4. Получаем цветной кадр из библиотеки
            // 120 - ширина (символы), 60 - высота (пиксели, упакованные по два в символ)
            std::string frame = cam.getFrameAsColor(120, 60);

            if (frame.empty()) {
                std::cerr << "Ошибка получения кадра!" << std::endl;
                break;
            }

            // 5. Вывод кадра в терминал
            std::cout << frame << std::flush;

            // 6. Опрос клавиатуры (необходим для работы OpenCV и выхода)
            // 27 - код клавиши ESC
            if (cv::waitKey(1) == 27) {
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    }

    // 7. Возвращаем терминал в нормальное состояние:
    // \033[?25h - показать курсор
    // \033[0m   - сбросить все цвета
    std::cout << "\033[?25h\033[0m" << std::endl;

    return 0;
}