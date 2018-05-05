cmake_minimum_required(  VERSION 3.1 )

set( Project sizers )
project( ${Project} )


###############################################################################
# Prepare external dependencies
###############################################################################
# If using any external libraries create a 'external'
# subdir with an appropriate CMakeLists and add the following
# for each library
# add_subdirectory( external/clara )

# Find any external libraries via find_backage
# see cmake --help-module-list and cmake --help-module ModuleName
# for details on a specific module
find_package( wxWidgets REQUIRED
  COMPONENTS
  core base
  )
if( wxWidgets_FOUND )
  include( ${wxWidgets_USE_FILE} )
else()
  message( FATAL_ERROR "Cannon find wxWidgets" )
endif()


###############################################################################
# Prepare source files for build
###############################################################################
# Create a Sources variable to all the cpp files necessary
# to build the target
# set( Sources
#     ${PROJECT_SOURCE_DIR}/src/file1.cpp
#     ${PROJECT_SOURCE_DIR}/src/file2.cpp
#    )

# Or glob all the files
file( GLOB Sources 
      "${PROJECT_SOURCE_DIR}/src/*.cpp"
    )


###############################################################################
# Configure build
###############################################################################
# Set required C++ standard
set( CMAKE_CXX_STANDARD 17 )
# Set build type
if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set( CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
endif()

# Export compile_commands.json for use with cppcheck
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


###############################################################################
# Build target
###############################################################################
# set( Executable !!_ENTER_EXECUTABLE_NAME_HERE_!! )

foreach( target ${Sources} )
  string(REGEX REPLACE "^.*\/(.+\/)*(.+)\.(cpp|cc)$" "\\2" fname ${target})
  MESSAGE( STATUS "---Adding exec: ${fname}" )
  add_executable( ${fname} ${target} )
  target_include_directories( ${fname} PUBLIC ${PROJECT_SOURCE_DIR}/include)
  target_compile_options( ${fname} PUBLIC -Wall -Wextra -pedantic -Werror )
  target_link_libraries( ${fname} ${wxWidgets_LIBRARIES} )
endforeach(target)
