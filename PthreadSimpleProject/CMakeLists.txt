cmake_minimum_required(VERSION 3.18)
project(PthreadSimpleProject)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(PthreadSimpleProject main.cpp)

target_link_libraries(PthreadSimpleProject PRIVATE Threads::Threads)











