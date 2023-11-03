cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    gallow
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    gallow_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    gallow_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(gallow_lib PUBLIC cxx_std_17)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(gallow_lib PRIVATE raylib)
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
target_include_directories(gallow_lib PRIVATE ${RAYGUI_INCLUDE_DIRS})
IF (WIN32)
target_link_libraries(gallow_lib PRIVATE winmm.lib)
ENDIF()
# ---- Declare executable ----

add_executable(gallow_exe source/main.cpp)
add_executable(gallow::exe ALIAS gallow_exe)

set_property(TARGET gallow_exe PROPERTY OUTPUT_NAME gallow)

target_compile_features(gallow_exe PRIVATE cxx_std_17)

target_link_libraries(gallow_exe PRIVATE gallow_lib)
target_include_directories(gallow_exe PRIVATE ${RAYGUI_INCLUDE_DIRS})

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT gallow_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of gallow"
  )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/dev-mode.cmake)
