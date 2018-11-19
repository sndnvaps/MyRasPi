#CMakeLists.txt for build machtalk_upload 
project(machtalk_dht22)
cmake_minimum_required(VERSION 2.8)
#INCLUDE (CheckTypeSize)
SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")
#check c++11 support 
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#add config.h support 
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

set(SRC_LIST dht22.c 
		locking.c 
		machtalk.c 
		rpi_cpu_temp.c
		machtalk_dht22.cpp)

#set(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(machtalk_dht22 ${SRC_LIST})

option(SUPPORT_MYSQL_DB 
	"insert the temp data to local database" OFF)
if (SUPPORT_MYSQL_DB)
	include_directories ("${PROJECT_SOURCE_DIR}/TempRecord")
	ADD_SUBDIRECTORY(TempRecord)
	set(EXTRA_LIBS ${EXTRA_LIBS} TempRecord)
endif (SUPPORT_MYSQL_DB) 


target_link_libraries(machtalk_dht22 -lwiringPi)
target_link_libraries(machtalk_dht22 -lpthread)

if (SUPPORT_MYSQL_DB)
#	LINK_DIRECTORIES("/usr/local/lib")
#	TARGET_LINK_LIBRARIES(machtalk_dht22   -ldl -lrt -Wl,-rpath=./TempRecord,-rpath=/usr/lib  -L/usr/lib -L./TempRecord -lTempRecord)
	TARGET_LINK_LIBRARIES(machtalk_dht22  TempRecord)
endif (SUPPORT_MYSQL_DB)

#SET(EXECUTABLE_OUTPUT_PATH /usr/local/bin)
#SET(CMAKE_INSTALL_PREFIX /usr)

INSTALL(TARGETS machtalk_dht22 DESTINATION bin)
#INSTALL(FILES "${PROJECT_BINARY_DIR}/config.h"
#			DESTINATION include)
