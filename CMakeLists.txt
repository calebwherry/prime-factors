########################################
########################################
##
##  \file CMakeLists.txt
##  \brief Top-level CMakeLists.txt
##  \author J. Caleb Wherry
##
########################################
########################################


#
# CMake version:
#
cmake_minimum_required(VERSION 2.8)


#
# CMake overrides (have to go before project() or they are ignored):
#
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()


#
# CMake project name:
#
project(prime-factors CXX)


#
# Display build type:
#
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


#
# Check compiler versions:
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

  # Check version. If empty, warn. If too old, error out:
  if ("${CMAKE_CXX_COMPILER_VERSION}" STREQUAL "")
    message(WARNING "GCC Compiler version is unknown, proceed at your own risk!")
  elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
    message(FATAL_ERROR "GCC compiler version must be at least 4.8!")
  endif()

	# Set compiler specific flags:
	set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -ggdb -O2 -std=c++11 -pthread")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 -std=c++11 -pthread")

  # Additional compiler flags depending on architecture:
  message(STATUS "System processor: ${CMAKE_SYSTEM_PROCESSOR}")
  if ("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "(.*)arm(.*)")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wl,--no-as-needed")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wl,--no-as-needed")
  endif()

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

  # Check version. If empty, warn. If too old, error out:
  if ("${CMAKE_CXX_COMPILER_VERSION}" STREQUAL "")
    message(WARNING "Clang compiler version is unknown, proceed at your own risk!")
  elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4)
    message(FATAL_ERROR "Clang compiler version must be at least 3.4!")
  endif()

  # Set compiler specific flags:
  set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -ggdb -O2 -std=c++11 -stdlib=libc++ -pthread")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 -std=c++11 -stdlib=libc++ -pthread")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

  # Check version. If empty, warn. If too old, error out:
  if ("${CMAKE_CXX_COMPILER_VERSION}" STREQUAL "")
    message(WARNING "MSVC compiler version is unknown, proceed at your own risk!")
  elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18.0)
    message(FATAL_ERROR "MSVC compiler version must be at least 18.0!")
  endif()

  # Set compiler specific flags:
  set(CMAKE_CXX_FLAGS "")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")

  # Check version. If empty, warn. If too old, error out:
  if ("${CMAKE_CXX_COMPILER_VERSION}" STREQUAL "")
    message(WARNING "Intel compiler version is unknown, proceed at your own risk!")
  elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14.0)
    message(FATAL_ERROR "MSVC compiler version must be at least 14.0!")
  endif()

  # Set compiler specific flags:
  set(CMAKE_CXX_FLAGS "")

else()

  message(WARNING "The '${CMAKE_CXX_COMPILER_ID}' compiler is untested and unsupported, continue at your own risk!")

endif()



#
# For time sake, I went ahead and added all files below. This should, however,
#   be pushed down into individual folders and files.
#

# Add library:
add_library(prime-factors-lib 
  prime-factors-lib/UtilsLib.cpp
  prime-factors-lib/FileParserLib.cpp
)

# Add executable:
include_directories("${CMAKE_SOURCE_DIR}/prime-factors-lib") # Update to target_* when moving to CMake 3.0
add_executable(prime-factors
  prime-factors/prime-factors.cpp
)
target_link_libraries(prime-factors prime-factors-lib)
