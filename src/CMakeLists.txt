cmake_minimum_required(VERSION 3.2)
project(divider)

set(SOURCE_FILES main.cpp)

add_executable(divider ${SOURCE_FILES})
target_link_libraries(divider ${PQXX_LIBRARIES})
install(TARGETS divider DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
