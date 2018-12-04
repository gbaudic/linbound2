cmake_minimum_required(VERSION 3.2)
project(linbound)

set(CMAKE_CXX_STANDARD 11)

# The version number.
set (Linbound_VERSION_MAJOR 0)
set (Linbound_VERSION_MINOR 1)
set (Linbound_VERSION_RELEASE 0)
option (ENABLE_SERVER "Also enable server abilities" OFF)
option (ENABLE_TESTS "Build the test suite" ON)

if(ENABLE_SERVER)
	set(Linbound_ENABLE_SERVER true)
else()
	set(Linbound_ENABLE_SERVER false)
endif()

if(NOT UNIX)
	set(resource_prefix "./res")
else()
	set(resource_prefix "/usr/share/games/${PROJECT_NAME}")
endif()

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.hpp.in"
  "${PROJECT_SOURCE_DIR}/src/config.hpp"
)

file(GLOB_RECURSE source_files src/*)

add_executable(${PROJECT_NAME} ${source_files})

if(NOT MSVC)
	INCLUDE(FindPkgConfig)
	INCLUDE(FindGettext)
endif()
INCLUDE(CheckIncludeFiles)

if(NOT MSVC)
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
	PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)
	PKG_SEARCH_MODULE(SDL2_GFX REQUIRED SDL2_gfx)
	PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
	PKG_SEARCH_MODULE(SDL2_NET REQUIRED SDL2_net)
	PKG_SEARCH_MODULE(GUISAN REQUIRED guisan>=0.9.0)
	if(ENABLE_TESTS)
		PKG_SEARCH_MODULE(GTEST REQUIRED gtest_main)
	endif()
	
	find_library(TINYXML2 REQUIRED libtinyxml2)
	find_library(SQLITE3 REQUIRED libsqlite3)
	find_library(BOX2D REQUIRED libbox2d)
else(MSVC)
	find_library(SDL2 REQUIRED sdl2)
	find_library(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
	find_library(SDL2_TTF REQUIRED SDL2_ttf)
	find_library(SDL2_GFX REQUIRED SDL2_gfx)
	find_library(SDL2_MIXER REQUIRED SDL2_mixer)
	find_library(SDL2_NET REQUIRED SDL2_net)
	find_library(GUISAN REQUIRED guisan>=0.9.0)
	
	if(ENABLE_TESTS)
		find_library(GTEST REQUIRED gtest_main)
	endif()

	find_library(TINYXML2 REQUIRED tinyxml2)
	find_library(SQLITE3 REQUIRED sqlite3)
	find_library(BOX2D CONFIG REQUIRED)
endif()

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} 
	${SDL2_IMAGE_INCLUDE_DIRS} 
	${SDL2_TTF_INCLUDE_DIRS}
	${SDL2_GFX_INCLUDE_DIRS}
	${SDL2_MIXER_INCLUDE_DIRS}
	${SDL2_NET_INCLUDE_DIRS}
	${GUISAN_INCLUDE_DIRS}
	${TINYXML2_INCLUDE_DIRS}
	${SQLITE3_INCLUDE_DIRS}
	${BOX2D_INCLUDE_DIRS})
	
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} 
	${SDL2_IMAGE_LIBRARIES} 
	${SDL2_TTF_LIBRARIES}
	${SDL2_GFX_LIBRARIES}
	${SDL2_MIXER_LIBRARIES}
	${SDL2_NET_LIBRARIES}
	${GUISAN_LIBRARIES}
	${TINYXML2_LIBRARIES}
	${SQLITE3_LIBRARIES}
	${BOX2D_LIBRARIES})
	
# TODO install targets
if(WIN32)
	set(EXECUTABLE_NAME ${PROJECT_NAME}.exe)
else()
	set(EXECUTABLE_NAME ${PROJECT_NAME})
endif()


if(ENABLE_TESTS)
	include(GoogleTest)
	include(CTest)
	enable_testing()
	set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
	file(GLOB_RECURSE test_files RELATIVE ${PROJECT_SOURCE_DIR} test/*.cpp)
	add_executable(${PROJECT_TEST_NAME} ${test_files})
	add_dependencies(${PROJECT_TEST_NAME} ${PROJECT_NAME})
	target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LDFLAGS})
	target_compile_options(${PROJECT_TEST_NAME} PUBLIC ${GTEST_CFLAGS})
	gtest_discover_tests(${PROJECT_TEST_NAME})
endif()


# install(TARGETS ${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE_NAME} DESTINATION bin)

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${Linbound_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Linbound_VERSION_MINOR}")
include (CPack)
