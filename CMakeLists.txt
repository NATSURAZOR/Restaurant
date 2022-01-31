cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)
project(project)

find_package(Threads)

set(SOURCE_FILES
        1_Menu.cpp
        2_Tables.cpp
        3_Reservation.cpp
        4_Restaurant.cpp

        TestMenu.cpp
        TestsTables.cpp
        TestsReservation.cpp
        TestsRestaurant.cpp

        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc const.h)

include_directories(GoogleTest)
add_executable(project ${SOURCE_FILES})
target_link_libraries(project ${CMAKE_LIBS_INIT} ${CMAKE_THREAD_LIBS_INIT})