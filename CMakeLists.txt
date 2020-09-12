cmake_minimum_required(VERSION 3.16)
project(AimingOffer)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR basic/include)
# set(SRC_DIR basic/src)

include_directories(${INC_DIR})

add_executable(AimingOffer basic/src/DuplicationInArray.cpp)