cmake_minimum_required(VERSION 3.9)
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

if(NOT RESOURCE_PREFIX)
    if(WIN32 OR MSYS OR MINGW)
        set(RESOURCE_PREFIX "./res")
    else()
        set(RESOURCE_PREFIX ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME})
    endif()
endif()

# Print status of compilation variables
message(STATUS "Compilation variables have the following values:")
message(STATUS "  ENABLE_SERVER   : ${ENABLE_SERVER}")
message(STATUS "  ENABLE_TESTS    : ${ENABLE_TESTS}")
message(STATUS "  RESOURCE_PREFIX : ${RESOURCE_PREFIX}")
message(STATUS "")

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.hpp.in"
  "${PROJECT_SOURCE_DIR}/src/config.hpp"
)

file(GLOB source_files LIST_DIRECTORIES false src/*.cpp src/common/* src/ui/* src/views/*)
file(GLOB server_source_files LIST_DIRECTORIES false src/gamemap.cpp src/utils.cpp src/network.cpp src/settings.cpp src/sprite.cpp
    src/server/* src/common/*)
set(SERVER_NAME ${PROJECT_NAME}_server)

add_executable(${PROJECT_NAME} ${source_files})
if(ENABLE_SERVER)
	add_executable(${SERVER_NAME} ${server_source_files})
endif()

if(NOT MSVC)
	INCLUDE(FindPkgConfig)
	INCLUDE(FindGettext)
endif()
INCLUDE(CheckIncludeFiles)

if(NOT MSVC)
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	if(MSYS OR MINGW)
		message(STATUS "Checking for SDL2main, required on Windows systems")
		find_library(SDL2MAIN NAMES SDL2main PATHS /mingw64/lib /mingw32/lib)
	endif()
	PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
	PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)
	PKG_SEARCH_MODULE(SDL2_GFX REQUIRED SDL2_gfx)
	PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
	PKG_SEARCH_MODULE(SDL2_NET REQUIRED SDL2_net)
	PKG_SEARCH_MODULE(GUISAN REQUIRED guisan>=0.9.0)
	if(ENABLE_TESTS)
		PKG_SEARCH_MODULE(GTEST REQUIRED gtest_main)
	endif()
	
	PKG_SEARCH_MODULE(TINYXML2 REQUIRED tinyxml2)
	PKG_SEARCH_MODULE(SQLITE3 REQUIRED sqlite3)
	message(STATUS "Checking for Box2D")
	find_library(BOX2D Box2D PATHS /mingw64/lib /mingw32/lib)
else(MSVC)
	message(STATUS "Finding location of libraries")
	find_library(SDL2_LIBRARIES NAMES SDL2)
	find_library(SDL2MAIN NAMES SDL2main)
	find_library(SDL2_IMAGE_LIBRARIES NAMES SDL2_image)
	find_library(SDL2_TTF_LIBRARIES NAMES SDL2_ttf)
	find_library(SDL2_GFX_LIBRARIES NAMES SDL2_gfx)
	find_library(SDL2_MIXER_LIBRARIES NAMES SDL2_mixer)
	find_library(SDL2_NET_LIBRARIES NAMES SDL2_net)
	find_library(GUISAN_LIBRARIES NAMES Guisan)
	
	if(ENABLE_TESTS)
		find_library(GTEST NAMES gtest)
		find_library(GTEST_MAIN NAMES gtest_main)
	endif()

	find_library(TINYXML2_LIBRARIES NAMES tinyxml2)
	find_library(SQLITE3_LIBRARIES NAMES sqlite3)
	find_library(BOX2D_LIBRARIES NAMES Box2D)

	message(STATUS "Finding location of INCLUDE files")
	find_path(TINYXML2_INCLUDE_DIRS tinyxml2.h)
	find_path(SDL2_INCLUDE_DIRS SDL.h)
	if(SDL2_INCLUDE_DIRS STREQUAL SDL2_INCLUDE_DIRS-NOTFOUND)
		find_path(SDL2_INCLUDE_DIRS SDL.h HINTS "${TINYXML2_INCLUDE_DIRS}/SDL2")
	endif()
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
	${SDL2MAIN}   # only used in Windows
	${SDL2_IMAGE_LIBRARIES} 
	${SDL2_TTF_LIBRARIES}
	${SDL2_GFX_LIBRARIES}
	${SDL2_MIXER_LIBRARIES}
	${SDL2_NET_LIBRARIES}
	${GUISAN_LIBRARIES}
	${TINYXML2_LIBRARIES}
	${SQLITE3_LIBRARIES}
	${BOX2D_LIBRARIES})
	
if(ENABLE_SERVER)
	TARGET_LINK_LIBRARIES(${SERVER_NAME} ${SDL2_LIBRARIES} 
		${SDL2MAIN}   # only used in Windows
		${SDL2_IMAGE_LIBRARIES} 
		${SDL2_TTF_LIBRARIES}
		${SDL2_GFX_LIBRARIES}
		${SDL2_MIXER_LIBRARIES}
		${SDL2_NET_LIBRARIES}
		${GUISAN_LIBRARIES}
		${TINYXML2_LIBRARIES}
		${SQLITE3_LIBRARIES}
		${BOX2D_LIBRARIES})
endif()


if(ENABLE_TESTS)
	include(GoogleTest)
	include(CTest)
	enable_testing()
	set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
	file(GLOB test_files RELATIVE ${PROJECT_SOURCE_DIR} test/*.cpp src/utils.cpp src/network.cpp src/settings.cpp src/gamemap.cpp)
	add_executable(${PROJECT_TEST_NAME} ${test_files})
	add_dependencies(${PROJECT_TEST_NAME} ${PROJECT_NAME})
    if(MSYS OR MINGW)
		# We need a main on Windows
		target_link_libraries(${PROJECT_TEST_NAME} ${SDL2_LIBRARIES}
		${SDL2_IMAGE_LIBRARIES} 
		${SDL2_TTF_LIBRARIES}
		${SDL2_GFX_LIBRARIES}
		${SDL2_MIXER_LIBRARIES}
		${SDL2_NET_LIBRARIES}
		${GUISAN_LIBRARIES}
		${TINYXML2_LIBRARIES}
		${SQLITE3_LIBRARIES}
		${BOX2D_LIBRARIES} ${GTEST_LIBRARIES})
	elseif(MSVC)
		target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_MAIN} ${SDL2_LIBRARIES}
		${SDL2_IMAGE_LIBRARIES} 
		${SDL2_TTF_LIBRARIES}
		${SDL2_GFX_LIBRARIES}
		${SDL2_MIXER_LIBRARIES}
		${SDL2_NET_LIBRARIES}
		${GUISAN_LIBRARIES}
		${TINYXML2_LIBRARIES}
		${SQLITE3_LIBRARIES}
		${BOX2D_LIBRARIES} ${GTEST})
	else()
		target_link_libraries(${PROJECT_TEST_NAME} ${SDL2_LIBRARIES} 
		${SDL2_IMAGE_LIBRARIES} 
		${SDL2_TTF_LIBRARIES}
		${SDL2_GFX_LIBRARIES}
		${SDL2_MIXER_LIBRARIES}
		${SDL2_NET_LIBRARIES}
		${GUISAN_LIBRARIES}
		${TINYXML2_LIBRARIES}
		${SQLITE3_LIBRARIES}
		${BOX2D_LIBRARIES} ${GTEST_LDFLAGS})
	endif()
	target_compile_options(${PROJECT_TEST_NAME} PUBLIC ${GTEST_CFLAGS})
	if(CMAKE_VERSION VERSION_LESS 3.10)
		gtest_add_tests(${PROJECT_TEST_NAME} "" AUTO WORKING_DIRECTORY bin/${CMAKE_BUILD_TYPE})
	else()
		gtest_discover_tests(${PROJECT_TEST_NAME} WORKING_DIRECTORY bin/${CMAKE_BUILD_TYPE})
	endif()
endif()

# Install instructions
if(WIN32)
	install(TARGETS ${PROJECT_NAME} CONFIGURATIONS Release 
		RUNTIME DESTINATION .)
	if(ENABLE_SERVER)	
		install(TARGETS ${SERVER_NAME} CONFIGURATIONS Release 
			RUNTIME DESTINATION .)
	endif()
	install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION .)
	# The next line assumes you have all the necessary DLLs in the dll/ subdirectory
	# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dll/ CONFIGURATIONS Release
	# 	DESTINATION . FILES_MATCHING PATTERN "*.dll")
else()
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
	if(ENABLE_SERVER)
		install(TARGETS ${SERVER_NAME} RUNTIME DESTINATION bin)
	endif()
	install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res/ DESTINATION share/${PROJECT_NAME})
endif()

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${Linbound_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Linbound_VERSION_MINOR}")
include (CPack)
