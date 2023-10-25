cmake_minimum_required(VERSION 3.16)

project(GameOfLife VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_policy(SET QTP0001 NEW) # Suppress warning https://doc.qt.io/qt-6/qt-cmake-policy-qtp0001.html

qt_add_executable(${PROJECT_NAME}
  main.cpp
)

qt_add_qml_module(${PROJECT_NAME}
  URI GameOfLife
  VERSION 1.0
  QML_FILES
    qml/CustomButton.qml
    qml/WelcomeScreen.qml
    qml/GameBoard.qml
    qml/GameCell.qml
    qml/GameOptions.qml
    qml/Main.qml
    qml/WarningPopup.qml
    qml/CustomScrollView.qml
    qml/CustomTextField.qml
  RESOURCES resources.qrc
  SOURCES
    src/gamemanager.hpp       src/gamemanager.cpp
    src/cell.hpp              src/cell.cpp
    src/gameboard.hpp         src/gameboard.cpp
    src/gameoptions.hpp       src/gameoptions.cpp
    src/patterns.hpp          src/patterns.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${PROJECT_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME}
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
