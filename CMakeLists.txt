# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(SimulatedUniverse-count)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加源文件并生成共享库
add_library(SimulatedUniverse-count SHARED src/simulated_universe.cpp)

# 链接必要的库
target_link_libraries(SimulatedUniverse-count user32)