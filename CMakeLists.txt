cmake_minimum_required(VERSION 3.10)

project(harmonizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(FetchContent)

FetchContent_Declare(
  RtAudio
  GIT_REPOSITORY https://github.com/thestk/rtaudio.git
  GIT_TAG 6.0.1
)

FetchContent_MakeAvailable(RtAudio)

add_executable(harmonizer main.cpp)

include_directories(${RtAudio_SOURCE_DIR})
link_libraries(${RtAudio_LIBS})
target_link_libraries(harmonizer PRIVATE RtAudio)
