cmake_minimum_required(VERSION 3.20)
project(Smokers)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(Smokers main.cpp Smoker.h Mediator.h Semaphore.h Mediator.cpp Smoker.cpp Semaphore.cpp MyUtility.h Process.h Process.cpp)
