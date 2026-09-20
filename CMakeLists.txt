cmake_minimum_required(VERSION 3.5)

project(GrabText VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TESSERACT REQUIRED tesseract)

set(PROJECT_SOURCES
            src/main.cpp
            src/mainwindow.cpp
            src/mainwindow.h
            src/mainwindow.ui
            src/screenshotoverlay.h
            src/screenshotoverlay.cpp
            src/language.h
            src/language.cpp
            src/downloadwindow.h
            src/downloadwindow.cpp
            src/downloadwindow.ui
            src/networkmanager.h
            src/networkmanager.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GrabText
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GrabText APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GrabText SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GrabText
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(GrabText PRIVATE
    ${TESSERACT_INCLUDE_DIRS}
)

target_link_directories(GrabText PRIVATE
    ${TESSERACT_LIBRARY_DIRS}
)

target_link_libraries(GrabText PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    ${TESSERACT_LIBRARIES}
)

set_target_properties(GrabText PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS GrabText
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GrabText)
endif()

if(APPLE)
    add_custom_command(TARGET GrabText POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_BUNDLE_DIR:GrabText>/Contents/Resources/languages"

        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/languages"
            "$<TARGET_BUNDLE_DIR:GrabText>/Contents/Resources/languages"
    )
else()
    add_custom_command(TARGET GrabText POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:GrabText>/languages"

        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/languages"
            "$<TARGET_FILE_DIR:GrabText>/languages"
    )
endif()
