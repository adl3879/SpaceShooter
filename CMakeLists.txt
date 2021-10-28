# CMakeList.txt : CMake project for hello, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.7.2)

project(hello)
set(CMAKE_CXX_STANDARD 11)

# TODO: Add tests and install targets if needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(BIN_DIR ${hello_SOURCE_DIR}/bin)

# This path is used by FindSDL2 module. 
# It will find include and lib folders under this directory.
# This is because find command doesn't include any path for Windows.
# So it can't find anything using default paths.
# SDL2_PATH is already expected in module file. I'm using the same variable.
IF (WIN32)
    set(SDL2_PATH "C:/SDL2-2.0.14")
ENDIF()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIR})

file(GLOB SOURCE_FILES 
    "src/*.cpp"
    "src/*/*.cpp"
    "src/*/*/*.cpp"
)

set(ENGINE_DIR
    src/Engine
    src/Timer
    src/Graphics
    src/Animation
    src/Physics
    src/Object
    src/Events
    src/Game
    src/AssetManager
    src/States
    vendor/TinyXML
)

include_directories(${ENGINE_DIR})

foreach(SUBDIR ${ENGINE_DIR})
    add_subdirectory(${SUBDIR})
endforeach()
 
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${ENGINE_DIR})

foreach(TARGET ${ENGINE_DIR})
    string(REGEX REPLACE ".*/" "" NEW_TARGET ${TARGET})
    target_link_libraries(${PROJECT_NAME} ${NEW_TARGET})
endforeach()

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} SDL2::Image SDL2::TTF SDL2::Mixer)
