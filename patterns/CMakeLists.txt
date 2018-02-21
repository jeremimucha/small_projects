cmake_minimum_required(VERSION 3.1)

project(Patterns)

set( CMAKE_CXX_STANDARD 17 )
if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set( CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
endif()


file( GLOB target_sources RELATIVE "${PROJECT_SOURCE_DIR}"
      "${PROJECT_SOURCE_DIR}/*.cpp" )

foreach( target ${target_sources} )
  string(REGEX MATCH "^[^ .]*" fname ${target} )
  MESSAGE( STATUS "Executable: ${fname}" )
  add_executable( ${fname} ${target} )
  target_include_directories( ${fname} PUBLIC ${PROJECT_SOURCE_DIR} )
  target_compile_options( ${fname} PUBLIC -Wall -Wextra -pedantic )
endforeach(target)
