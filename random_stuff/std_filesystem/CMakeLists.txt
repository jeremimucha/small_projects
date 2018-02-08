cmake_minimum_required(VERSION 3.1)

project(BoostFilesystemTutorial)

# # find a boost install with the libraries filesystem and system
# find_package(Boost 1.60 REQUIRED COMPONENTS system filesystem)

# # check if boost was found
# if(Boost_FOUND)
#     message ("boost found")
#     include_directories(${Boost_INCLUDE_DIRS})
# else()
#     message (FATAL_ERROR "Cannot find Boost")
# endif()

set( CXX_STANDARD 17 )
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

###############################
# manually linking a library - point cmake to the exact path
add_library(stdc++fs UNKNOWN IMPORTED)
set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "C:/Projects/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/7.3.0/libstdc++fs.a")

file( GLOB target_sources RELATIVE "${PROJECT_SOURCE_DIR}"
      "${PROJECT_SOURCE_DIR}/*.cpp" )

foreach( target ${target_sources} )
  string(REGEX MATCH "^[^ .]*" fname ${target} )
  MESSAGE( STATUS "Executable: ${fname}" )
  add_executable( ${fname} ${target} )
  target_compile_definitions( ${fname} PUBLIC Wall Wextra Wpedantic )
  target_link_libraries( ${fname}
#    ${Boost_LIBRARIES}
    stdc++fs
   )
#   target_include_directories( ${fname} PUBLIC ${PROJECT_SOURCE_DIR} )
endforeach(target)