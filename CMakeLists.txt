cmake_minimum_required(VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(RayMarchingFractals LANGUAGES C CXX)

# Default to Release on single-config generators (Linux/Make/Ninja).
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(RayMarchingFractals
  main.cpp
  ${SOURCES}
  third_party/tinyexr/miniz.c
)

target_include_directories(RayMarchingFractals PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/tinyexr
)

target_compile_definitions(RayMarchingFractals PRIVATE
  PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)

set_target_properties(RayMarchingFractals PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

find_package(Threads REQUIRED)
target_link_libraries(RayMarchingFractals PRIVATE Threads::Threads)

if (MSVC)
  string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# Warnings on our C++ only, not third-party C.
target_compile_options(RayMarchingFractals PRIVATE
  $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/W4>
  $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>:-Wall -Wextra>
)

# Optional link-time optimization, only if the toolchain supports it.
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_ok OUTPUT ipo_msg)
if (ipo_ok)
  set_property(TARGET RayMarchingFractals PROPERTY
    INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()