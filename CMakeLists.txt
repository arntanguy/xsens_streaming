cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME xsens_streaming)
set(PROJECT_DESCRIPTION xsens_streaming)
set(PROJECT_VERSION 0.1.0)
set(PROJECT_URL https://github.com/arntanguy/xsens_streaming)
set(PROJECT_DEBUG_POSTFIX "_d")
set(PROJECT_USE_CMAKE_EXPORT TRUE)
set(CXX_DISABLE_WERROR 1)
set(CMAKE_CXX_STANDARD 17)

include(cmake/base.cmake)
include(cmake/cython/cython.cmake)

project(${PROJECT_NAME} LANGUAGES C CXX)

find_package(Boost REQUIRED COMPONENTS program_options)

set(THREADS_PREFER_PTHREAD_FLAG ON)
add_project_dependency(Threads REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMakeModules)
find_package(mtsdk REQUIRED COMPONENTS xstypes)
if(NOT ${mtsdk_FOUND})
  message(FATAL_ERROR "MTSDK not found. Please install it manually according to the instructions provided in the README: https://github.com/arntanguy/xsens_streaming")
endif()

add_subdirectory(src)
add_subdirectory(CMakeModules)

if(${PYTHON_BINDING})
    add_subdirectory(binding/python)
endif()
