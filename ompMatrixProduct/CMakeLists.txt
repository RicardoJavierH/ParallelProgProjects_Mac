cmake_minimum_required(VERSION 3.18)
project(ompMatrixProduct)
if(APPLE)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    if(CMAKE_C_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_C_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY omp)
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY omp)
    endif()
endif()

find_package(OpenMP REQUIRED)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(ompMatrixProduct main.cpp)

target_link_libraries(ompMatrixProduct PRIVATE OpenMP::OpenMP_CXX /usr/local/lib/libomp.a)











