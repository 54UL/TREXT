cmake_minimum_required(VERSION 3.16)

project(SnipingTester VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_PREFIX_PATH "/path/to/Qt6")
set(CMAKE_PREFIX_PATH "/usr/local/lib;/usr/lib;/usr/local/lib64;/usr/lib64" ${CMAKE_PREFIX_PATH})

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup()

#fixme!!!
# set(Tesseract_DIR "C:/repos/mingw-w64-x86_64-static-tesseract/build")

# Find OpenCV
# set(OpenCV_DIR "C:/repos/OpenCV-MinGW-Build")
 find_package(OpenCV REQUIRED)
 include_directories(${OpenCV_INCLUDE_DIRS})

# Find Tesseract
#find_package(Tesseract REQUIRED)
#include_directories(${Tesseract_INCLUDE_DIRS})
#end fixme

#find resources and code files

file(GLOB_RECURSE APP_SRC "*app/*.cpp")
file(GLOB_RECURSE APP_HEADERS "app/*.hpp")
qt_add_resources(resources app/resources.qrc)


qt_add_executable(appSnipingTester
    ${APP_SRC}
    ${APP_HEADERS}
    qrc_resources.cpp
)

qt_add_qml_module(appSnipingTester
    URI SnipingTester
    VERSION 1.0
    QML_FILES app/Main.qml
)

set_target_properties(appSnipingTester PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.xul.trext
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSnipingTester
    PRIVATE Qt6::Quick Qt6::Widgets ${OpenCV_LIBS} tesseract
)

target_compile_options(appSnipingTester PRIVATE ${OpenCV_CFLAGS_OTHER} ${Tesseract_CFLAGS})

install(TARGETS appSnipingTester
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
