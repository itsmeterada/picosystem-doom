set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
cmake_minimum_required(VERSION 3.13)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)
include(pico_extras_import.cmake)

#
# Project Name
#
project("Picosystem rp2040 doom" VERSION 0.1.0 LANGUAGES C CXX ASM)
enable_language(CXX)

#
# Some custom settings
#
# we are using git@github.com:liamfraser/tinyusb.git as it has some RP2040 fixes that aren't upstreamed yet
#set(PICO_TINYUSB_PATH ${CMAKE_CURRENT_LIST_DIR}/3rdparty/tinyusb)
# this only affects device builds device, but we want to use zone for malloc in this case so we don't have two separate elastic spaces and can fit more in
set(SKIP_PICO_MALLOC 1)

#
# Set the rp2040 build setting
#
set(CMAKE_BUILD_TYPE MinSizeRel)

# Initialize the SDK
pico_sdk_init()

if (PICO_ON_DEVICE AND NOT CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  message(WARNING "You should do a MinSizeRel build when targeting the RP2040
  (with -DCMAKE_BUILD_TYPE=MinSizeRel)")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Include the PicoSystem library
include(${CMAKE_CURRENT_LIST_DIR}/tiny_library/tiny_picosystem.cmake REQUIRED)



# Autotools variables
set(top_srcdir ${CMAKE_CURRENT_SOURCE_DIR})
set(top_builddir ${CMAKE_CURRENT_BINARY_DIR})

# AC_INIT variables
set(PACKAGE_NAME "${PROJECT_NAME}")
set(PACKAGE_TARNAME "chocolate-doom")
set(PACKAGE_VERSION "${PROJECT_VERSION}")
set(PACKAGE_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
set(PACKAGE_BUGREPORT "chocolate-doom-dev-list@chocolate-doom.org")

string(REGEX REPLACE " Doom$" "" PACKAGE_SHORTNAME "${PACKAGE_NAME}")
set(PACKAGE_COPYRIGHT "Copyright (C) 1993-2017")
set(PACKAGE_LICENSE "GNU General Public License, version 2")

# Any settings that should apply to all targets in this directory and all
# subdirectories should go here.  Use judiciously.
add_compile_options("-Wall" "-Wredundant-decls")

set(HAVE_MMAP 1)
find_package(m)

include(CheckSymbolExists)
include(CheckIncludeFile)
check_symbol_exists(strcasecmp "strings.h" HAVE_DECL_STRCASECMP)
check_symbol_exists(strncasecmp "strings.h" HAVE_DECL_STRNCASECMP)
check_include_file("dirent.h" HAVE_DIRENT_H)

# Without a hyphen. This is used for the bash-completion scripts.
string(TOLOWER "${PACKAGE_SHORTNAME}" PROGRAM_SPREFIX)

# With a hyphen, used almost everywhere else.
set(PROGRAM_PREFIX "${PROGRAM_SPREFIX}-")

configure_file(cmake/config.h.cin config.h)

# setup release packages
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)

foreach(SUBDIR textscreen opl pcsound src)
    add_subdirectory("${SUBDIR}")
endforeach()
