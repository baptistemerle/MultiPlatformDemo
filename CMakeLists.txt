cmake_minimum_required(VERSION 3.16)

project(MultiPlatformDemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Bluetooth QuickControls2)

qt_standard_project_setup(REQUIRES 6.10)

file(GLOB_RECURSE ESP32_UTILS_FILES
    "lib/ESP32Utilities/*.h"
    "lib/ESP32Utilities/*.hpp"
    "lib/ESP32Utilities/*.cpp"
    "lib/ESP32Utilities/*.c"
)

qt_add_executable(appMultiPlatformDemo
  src/main.cpp
  ${ESP32_UTILS_FILES}
)

target_include_directories(appMultiPlatformDemo PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/ESP32Utilities/src
)

qt_add_qml_module(appMultiPlatformDemo
  URI MultiPlatformDemo
  SOURCES
    src/Connectivity/ble_connection.h
    src/Connectivity/ble_connection.cpp
    src/Connectivity/ble_controller.h
    src/Connectivity/ble_controller.cpp
    src/Connectivity/ble_device_model.h
    src/Connectivity/ble_device_model.cpp
    src/Connectivity/ble_scanner.h
    src/Connectivity/ble_scanner.cpp

    src/Core/configuration.h
    src/Core/dashboard_protocol.h
    src/Core/dashboard_protocol.cpp

  QML_FILES
    src/UI/DeviceDetailView.qml
    src/UI/DeviceListView.qml
    src/UI/Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMultiPlatformDemo PROPERTIES
#  MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMultiPlatformDemo
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMultiPlatformDemo
  PRIVATE Qt6::Quick
  PRIVATE Qt6::QuickControls2
  PRIVATE Qt6::Bluetooth
)

install(TARGETS appMultiPlatformDemo
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
