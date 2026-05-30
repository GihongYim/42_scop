cmake_minimum_required(VERSION 3.14)

project(scop LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)

if(EXISTS "${CMAKE_SOURCE_DIR}/vendor/glfw/CMakeLists.txt")
	add_subdirectory(vendor/glfw)
else()
	include(FetchContent)
	FetchContent_Declare(
		glfw
		GIT_REPOSITORY https://github.com/glfw/glfw.git
		GIT_TAG 3.3.10
	)
	FetchContent_MakeAvailable(glfw)
endif()

add_executable(scop
	src/Application.cpp
	src/Math.cpp
	src/Mesh.cpp
	src/ObjParser.cpp
	src/Shader.cpp
	src/Window.cpp
	src/main.cpp
	src/glad.c
)

target_include_directories(scop PRIVATE
	${CMAKE_SOURCE_DIR}/include
)

target_compile_options(scop PRIVATE
	-Wall
	-Wextra
	-Werror
)

target_link_libraries(scop PRIVATE
	glfw
	OpenGL::GL
	Threads::Threads
	${CMAKE_DL_LIBS}
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_link_options(scop PRIVATE
		-static-libstdc++
		-static-libgcc
	)
endif()
