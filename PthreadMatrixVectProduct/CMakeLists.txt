cmake_minimum_required(VERSION 3.18)
project(PthreadMatrixVectProduct)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(PthreadMatrixVectProduct main.cpp)

target_link_libraries(PthreadMatrixVectProduct PRIVATE Threads::Threads)











