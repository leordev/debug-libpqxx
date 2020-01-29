cmake_minimum_required(VERSION 3.2)

project(cmake-project-template)

find_package(PostgreSQL COMPONENTS Libraries)

if (PostgreSQL_INCLUDE_DIR)
  set(SKIP_PQXX_SHARED ON)
  set(SKIP_BUILD_TEST ON)
  add_subdirectory(external/libpqxx EXCLUDE_FROM_ALL)
  set(PQXX_LIBRARIES pqxx_static)
else()
  set(PQXX_LIBRARIES "")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(DIVISIBLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(DIVISIBLE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(DIVISIBLE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(DIVISION_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/division)

include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})
include_directories(${DIVISION_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)


