# 1. Обязательные настройки
cmake_minimum_required(VERSION 3.10)
project(TerminalCamProject VERSION 1.0.0)

# 2. Поиск OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 3. Создание БИБЛИОТЕКИ
# Это создает цель (target) с именем TerminalCam
add_library(TerminalCam STATIC 
    TerminalCam.cpp 
    TerminalCam.h
)

# 4. Создание демо-приложения
add_executable(CamDemo main.cpp)
target_link_libraries(CamDemo PRIVATE TerminalCam ${OpenCV_LIBS})

# 5. ИНСТРУКЦИИ ДЛЯ ЭКСПОРТА (то, что мы добавляли)

# Куда ставить файлы
install(TARGETS TerminalCam
    EXPORT TerminalCamTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES TerminalCam.h DESTINATION include)

# Генерируем конфиг для других проектов
install(EXPORT TerminalCamTargets
    FILE TerminalCamTargets.cmake
    NAMESPACE TerminalCam::
    DESTINATION lib/cmake/TerminalCam
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "TerminalCamConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/TerminalCamConfigVersion.cmake"
    DESTINATION lib/cmake/TerminalCam
)