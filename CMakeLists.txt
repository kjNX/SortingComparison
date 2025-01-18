cmake_minimum_required(VERSION 3.28)
project(SortingComparison)

set(CMAKE_CXX_STANDARD 26)

add_executable(SequentialSort main_sequential.cpp
        Sequential.cpp
        Sequential.hpp
        Commons.cpp
        Commons.hpp
)

add_executable(ParallelSort main_parallel.cpp
        Sequential.cpp
        Sequential.hpp
        Parallel.cpp
        Parallel.hpp
        Commons.cpp
        Commons.hpp
)
add_executable(QParallelSort main_qparallel.cpp
        Sequential.cpp
        Sequential.hpp
        Parallel.cpp
        Parallel.hpp
        Commons.cpp
        Commons.hpp
)
