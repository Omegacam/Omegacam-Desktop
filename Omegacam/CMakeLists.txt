cmake_minimum_required(VERSION 3.5)

project(Omegacam LANGUAGES CXX)

# You only need this for MSVC and not QT Creator
set (CMAKE_PREFIX_PATH "O:\\Qt\\5.15.2\\msvc2019_64")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/output")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.
#
#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/3rd_party/header)
link_directories(${CMAKE_SOURCE_DIR}/3rd_party/lib)

if(ANDROID)
  add_library(Omegacam SHARED
    main.cpp
    home.cpp
    home.h
    home.ui
    cameralistwidget.cpp
    cameralistwidget.h
    common_includes.h
    options.h
    communication.cpp
    communication.h
  )
else()
  add_executable(Omegacam
    "src/main.cpp"
    "src/common_includes.h"
    "src/options.h"
    "src/UI/home.cpp"
    "src/UI/home.h"
    "src/UI/home.ui"
    "src/UI/cameralistwidget.cpp"
    "src/UI/cameralistwidget.h"
    "src/Backend/Network/communication.cpp"
    "src/Backend/Network/communication.h"
     "src/Backend/Network/Sockets/subSocket.cpp" "src/Backend/Network/Sockets/subSocket.h" "src/Backend/backendDelegate.cpp" "src/Backend/backendDelegate.h")
endif()

target_link_libraries(Omegacam PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network libzmq-v142-mt-4_3_5 libzmq-v142-mt-s-4_3_5)
