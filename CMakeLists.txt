
cmake_minimum_required(VERSION 3.0.0)
project(boost_timer VERSION 0.1.0)

add_executable(boost_timer main.cpp TimerTrigger.h TimerTrigger.cpp Timer.h Timer.cpp)

find_package(Boost 1.56.0 COMPONENTS system chrono thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(boost_timer ${Boost_LIBRARIES})
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Werror")