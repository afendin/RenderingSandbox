cmake_minimum_required(VERSION 3.16)

project(RenderingSandbox VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appRenderingSandbox
    main.cpp
    src/appmanager.h src/appmanager.cpp
    src/drawmanager.h src/drawmanager.cpp
    src/triangle.h    src/triangle.cpp
    src/trianglestruct.h src/trianglestruct.cpp
    3rdparty/tinyrenderer/geometry.h
    3rdparty/tinyrenderer/model.h
    3rdparty/tinyrenderer/model.cpp
    3rdparty/lib-qt-qml-tricks/src/qqmlobjectlistmodel.h
    3rdparty/lib-qt-qml-tricks/src/qqmlobjectlistmodel.cpp
)

qt_add_qml_module(appRenderingSandbox
    URI RenderingSandbox
    VERSION 1.0
    QML_FILES main.qml

)

add_custom_command(TARGET appRenderingSandbox
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/obj "${CMAKE_CURRENT_BINARY_DIR}/obj"
)

target_include_directories(appRenderingSandbox PRIVATE
                            src
                            3rdparty/lib-qt-qml-tricks/include
                            3rdparty/tinyrenderer
                            )

set_target_properties(appRenderingSandbox PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appRenderingSandbox
    PRIVATE Qt6::Quick)

install(TARGETS appRenderingSandbox
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
