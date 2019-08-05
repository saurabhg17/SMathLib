
SET(HDRS Impl/GeometryAlgo.hpp
         Impl/PointLine.hpp
         Impl/Statistics.hpp
         Impl/VectorAlgo.hpp
         Impl/VectorOnStack.hpp
         AxisAngle.h
         BarycentricCoords.h
         CompareDouble.h
         Config.h
         Constants.h
         Distance.h
         FPMaths.h
         GeometryAlgo.h
         Helpers.h
         Matrix.h
         MinMax.h
         PointAccessor.h
         PointConverter.h
         PointLine.h
         Quaternion.h
         RandomDoubleGenerator.h
         RandomInt64Generator.h
         RandomIntGenerator.h
         Spherical.h
         Statistics.h
         Trigono.h
         Types.h
         Vector2D.h
         Vector3D.h
         VectorAlgo.h
         VectorOnStack.h)
         
SET(SRCS AxisAngle.cpp
         CompareDouble.cpp
         FPMaths.cpp
         Matrix.cpp
         Quaternion.cpp
         RandomDoubleGenerator.cpp
         RandomInt64Generator.cpp
         RandomIntGenerator.cpp
         Trigono.cpp
         Vector2D.cpp
         Vector3D.cpp)


# Set the resource file for Windows and some compiler specific stuff.
if(WIN32)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Platform/version.rc.in ${CMAKE_CURRENT_BINARY_DIR}/version.rc @ONLY)
	set(rcFile ${SRCS} ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
else()
    set(rcFile)
endif()

add_library(SMathLib SHARED ${SRCS} ${HDRS} ${rcFile})


# Find SUtils header files.
message(STATUS "Finding SUtils header files...")
find_path(SUtils_Include 
          NAMES Types.h InvalidArgumentException.h InvalidOperationException.h
		  PATHS SUtils
		  PATH_SUFFIXES Exceptions
		  DOC "Include path for SUtils library"
		  NO_DEFAULT_PATH)

if(NOT SUtils_Include STREQUAL SUtils_Include-NOTFOUND)
	message(STATUS "Found SUtils header files in: ${SUtils_Include}")
	target_include_directories(SMathLib PRIVATE ${SUtils_Include})
endif()


# Find SUtils libraries.
message(STATUS "Finding SUtils library files...")
if(WIN32)
	find_library(SUtils_Lib_Debug
              	 NAMES SUtilsd.lib SUtilsd_x64.lib
			     DOC "SUtils debug library"
			     NO_DEFAULT_PATH)
	
	if(NOT SUtils_Lib_Debug STREQUAL SUtils_Lib_Debug-NOTFOUND)
		message(STATUS "Found SUtils debug library")
	endif()
	
	find_library(SUtils_Lib_Release
             	 NAMES SUtils.lib SUtils_x64.lib
			     DOC "SUtils release library"
			     NO_DEFAULT_PATH)
	
	if(NOT SUtils_Lib_Release STREQUAL SUtils_Lib_Release-NOTFOUND)
		message(STATUS "Found SUtils release library")
		target_link_libraries(SMathLib debug ${SUtils_Lib_Debug} optimized ${SUtils_Lib_Release})
	endif()
else()
    find_file(SUtils_Lib
	          NAMES SUtils
			  DOC "SUtils library"
			  NO_DEFAULT_PATH)
	
	if(NOT SUtils_Lib STREQUAL SUtils_Lib-NOTFOUND)
		message(STATUS "Found SUtils release library")
		target_link_libraries(SMathLib optimized ${SUtils_Lib})
	endif()
endif()

if(SUtils_Include STREQUAL SUtils_Include-NOTFOUND)
	message(FATAL_ERROR "Cannot find SUtils header files")
endif()
if(SUtils_Lib_Debug   STREQUAL SUtils_Lib_Debug-NOTFOUND OR
   SUtils_Lib_Release STREQUAL SUtils_Lib_Release-NOTFOUND OR
   SUtils_Lib         STREQUAL SUtils_Lib-NOTFOUND)
	message(FATAL_ERROR "Cannot find SUtils library files")
endif()



# Set the name of targets based on configurations.
if(WIN32)
	set(RELEASE_MANGLED_NAME "SMathLib")
	set(DEBUG_MANGLED_NAME   "SMathLib${SMATHLIB_DEBUG_POSTFIX}")
	
	set_target_properties(SMathLib PROPERTIES 
                        OUTPUT_NAME_DEBUG          "${DEBUG_MANGLED_NAME}" 
						OUTPUT_NAME_RELEASE        "${RELEASE_MANGLED_NAME}" 
						OUTPUT_NAME_MINSIZEREL     "${RELEASE_MANGLED_NAME}" 
						OUTPUT_NAME_RELWITHDEBINFO "${RELEASE_MANGLED_NAME}")
	
	set_target_properties(SMathLib PROPERTIES DEFINE_SYMBOL "SMATHLIB_EXPORTS")
  	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
else()
    set(SMATHLIB_VERSION   ${SMATHLIB_VERSION_MAJOR}.${SMATHLIB_VERSION_MINOR}.${SMATHLIB_VERSION_BUGFIX})
	set(SMATHLIB_SOVERSION ${SMATHLIB_VERSION_MAJOR}.${SMATHLIB_VERSION_MINOR}.${SMATHLIB_VERSION_BUGFIX})
	
	set_target_properties(SMathLib PROPERTIES 
                            VERSION   "${SMATHLIB_VERSION}" 
							SOVERSION "${SMATHLIB_SOVERSION}")
endif()


# Install the target (DLL and LIB files for windows and SO file for Linux)
install(TARGETS SMathLib
          RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
          LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
          ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# For MSVC install PDB files as well.
if(MSVC)
	install(FILES ${CMAKE_BINARY_DIR}/Bin/Debug/${DEBUG_MANGLED_NAME}.pdb            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin CONFIGURATIONS DEBUG)
	install(FILES ${CMAKE_BINARY_DIR}/Bin/RelWithDebInfo/${RELEASE_MANGLED_NAME}.pdb DESTINATION ${CMAKE_INSTALL_PREFIX}/bin CONFIGURATIONS RELWITHDEBINFO)
endif(MSVC)

# Install the header files.
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX}/include 
        FILES_MATCHING 
			PATTERN "*.h"
			PATTERN "*.hpp"
			PATTERN "Platform" EXCLUDE)