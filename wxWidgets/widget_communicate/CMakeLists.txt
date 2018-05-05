cmake_minimum_required(  VERSION 3.1 )

set( Project widgets_communicate )
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

add_executable( ${PROJECT_NAME} ${Sources} )

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
           ${PROJECT_SOURCE_DIR}/dat
    )
if( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    target_compile_options( ${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic -Werror )
endif()
if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_compile_options( ${PROJECT_NAME} PRIVATE /W4 /WX )
endif()

# if using any external libraries include them here
# they need to be properly found first. See find_package section
target_link_libraries( ${PROJECT_NAME}
    ${wxWidgets_LIBRARIES}
    # ${Boost_LIBRARIES}
    )

set( CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE )
include(InstallRequiredSystemLibraries)
get_filename_component( MSYS_Path ${CMAKE_CXX_COMPILER} PATH )
set( CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS
      ${MSYS_Path}/libgcc_s_dw2-1.dll
      ${MSYS_Path}/libstdc++-6.dll
      ${MSYS_Path}/libwinpthread-1.dll
      ${MSYS_Path}/wxbase30u_gcc_custom.dll
      ${MSYS_Path}/zlib1.dll
      ${MSYS_Path}/wxmsw30u_core_gcc_custom.dll
      ${MSYS_Path}/libjpeg-8.dll
      ${MSYS_Path}/libpng16-16.dll
      ${MSYS_Path}/libtiff-5.dll
      ${MSYS_Path}/liblzma-5.dll
)
set( CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" )
install( TARGETS ${PROJECT_NAME}
         RUNTIME DESTINATION .
       )
install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION .)
include(CPack)
