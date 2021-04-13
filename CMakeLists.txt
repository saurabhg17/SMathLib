
cmake_minimum_required(VERSION 2.8.0)

# Top level CMakeLists.txt for SMathLib
# CMakeLists files in this project can refer to the root source 
# directory of the project as ${CMAKE_SOURCE_DIR} and to the 
# root binary directory of the project as ${CMAKE_BINARY_DIR}.
project("SMathLib")

# The version of SMathLib is defined as Major.Minor.BugFix
# The rules for deciding the version are:
#    If the binary interface of the library do not change from the previous release as in the case
#      of bugfixes, increase SMATHLIB_VERSION_BUGFIX.
#    If the binary interface is changed, but remains compatible with the previous release then 
#      increase SMATHLIB_VERSION_MINOR and set SMATHLIB_VERSION_BUGFIX to 0.
#    If the binary interface is changed in an incompatible way to the previous release, then 
#      increase the SMATHLIB_VERSION_MAJOR, and set the two other numbers to 0.
set(SMATHLIB_VERSION_MAJOR  1)
set(SMATHLIB_VERSION_MINOR  0)
set(SMATHLIB_VERSION_BUGFIX 0)

# Set package information.
set(PACKAGE "SMathLib")
set(VERSION ${SMATHLIB_VERSION_MAJOR}.${SMATHLIB_VERSION_MINOR}.${SMATHLIB_VERSION_BUGFIX})

# Set the directories where the output files will be generated. To make it easy all files are
# generated in the bin directory under the root of the build directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 
set(CMAKE_PDB_OUTPUT_DIRECTORY     ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SMathLib uses relative path to the include the header files and so does all the examples.
# Hence, we define the include directory as the root of the source directory where SMathLib directory
# resides with all the source and header files.
include_directories(${CMAKE_SOURCE_DIR})

# Various parameters used for configuring.
set(SMATHLIB_DEBUG_POSTFIX d CACHE STRING "Add a suffix for debug builds")

# Don't use CMake defined suffix; otherwise CMake adds an extra suffix at the end.
set(CMAKE_DEBUG_POSTFIX)

# First build the SMathLib and then all examples.
add_subdirectory (SMathLib)
