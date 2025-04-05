cmake_minimum_required(VERSION 3.10)

# Project name and version
project(5G_FEC_Chain VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
add_library(modulation
    modulation/modulation.cpp
)

# Include directories
target_include_directories(modulation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/modulation
)

# Add the executable for the driver
add_executable(driver
    driver/main.cpp
)

# Link the modulation library to the driver
target_link_libraries(driver PRIVATE modulation)