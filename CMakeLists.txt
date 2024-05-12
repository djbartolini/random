cmake_minimum_required(VERSION 3.28)
project(random)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Find SDL_image include directory
find_path(SDL2_IMAGE_INCLUDE_DIR SDL2/SDL_image.h)

# Find SDL_image library
find_library(SDL2_IMAGE_LIBRARY SDL2_image)

# Find SDL_image
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})

# Add executable
add_executable(random image_on_screen.cpp
)

target_include_directories(random PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "Assets Directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# Link against SDL2 library
target_link_libraries(random ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY})