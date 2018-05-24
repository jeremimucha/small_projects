cmake_minimum_required(VERSION 3.1)

project(BoostProcessTutorial)

# find a boost install with the libraries filesystem and system
find_package(Boost 1.60 REQUIRED COMPONENTS system filesystem)

# check if boost was found
if(Boost_FOUND)
    message("boost found")
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Cannot find Boost")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file( GLOB target_sources RELATIVE "${PROJECT_SOURCE_DIR}"
      "${PROJECT_SOURCE_DIR}/*.cpp" )

foreach( target ${target_sources} )
  string(REGEX MATCH "^[^ .]*" fname ${target} )
  message( STATUS "Executable: ${fname}" )
  add_executable( ${fname} ${target} )
  target_compile_options( ${fname} PUBLIC
    -Wall -Wextra -pedantic -Werror
    -fconcepts
  )
  target_link_libraries( ${fname}
   ${Boost_LIBRARIES}
   wsock32 ws2_32
   )
endforeach(target)
