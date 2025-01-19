cmake_minimum_required(VERSION 3.10)

project(harmonizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(harmonizer src/main.cpp)

include(cmake/CPM.cmake)

CPMAddPackage(
	NAME rtaudio
	GITHUB_REPOSITORY thestk/rtaudio
	GIT_TAG 6.0.1
)

CPMAddPackage(
	NAME fftw3
	VERSION 3.3.10
	URL https://www.fftw.org/fftw-3.3.10.tar.gz
)

target_link_libraries(harmonizer PRIVATE rtaudio fftw3)
