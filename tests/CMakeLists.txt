cmake_minimum_required(VERSION 3.27)

project(unit-tests LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

qt_add_executable(unit-tests tst_settings.cpp)
add_test(NAME unit-tests COMMAND unit-tests)

target_link_libraries(unit-tests PRIVATE
        libs::project_warnings
        libs::project_options
        libs::core)

target_link_system_libraries(unit-tests PRIVATE Qt::Core Qt::Gui Qt::Qml Qt::Test)