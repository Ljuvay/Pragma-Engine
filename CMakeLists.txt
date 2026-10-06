# CMakeList.txt : CMake project for RayMarchingFractals, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Raymarching-Fractals")

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add source to this project's executable.
add_executable (RayMarchingFractals
	main.cpp
	${SOURCES}
	third_party/tinyexr/miniz.c
)

target_include_directories(RayMarchingFractals PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/third_party/tinyexr)

find_package(Threads REQUIRED)
target_link_libraries(RayMarchingFractals PRIVATE Threads::Threads)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayMarchingFractals PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
