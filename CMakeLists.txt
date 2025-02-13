# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(PlanetLeaper)

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

FetchContent_MakeAvailable(glm)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively find all source files in src directory
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.cxx"
    "src/*.cc"
)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)