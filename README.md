#  TerminalCam Library

Библиотека на C++ для захвата видео с веб-камеры и его отрисовки в терминале в реальном времени. Использует ANSI-цвета и символы полублока для достижения "честного" цветного изображения в консоли.

##  Особенности
* **Full Color**: Использует 24-битные ANSI последовательности для передачи цвета.
* **Double Pixel**: Техника упаковки двух пикселей в один знакоместо (символ `▀`).
* **OpenCV Backend**: Надежный захват видео через OpenCV 4.x.
* **Header-only (почти)**: Легко интегрируется в ваши проекты как библиотека.

##  Требования
* C++ 11 или выше
* OpenCV 4.13.0 (или совместимая версия)
* Терминал с поддержкой UTF-8 и ANSI цветов (Windows Terminal, VS Code Terminal, iTerm2).

##  Быстрый старт (Сборка)

```bash
# Клонирование
git clone [https://github.com/ryduxbsbdmc-eng/TerminalCam.git](https://github.com/ryduxbsbdmc-eng/TerminalCam.git)
cd TerminalCam

# Сборка
mkdir build
cd build
cmake ..
cmake --build . --config Release
