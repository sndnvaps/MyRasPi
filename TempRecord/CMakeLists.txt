#cmake 
# support connect to mysql 5.5 
#
#//compile guide
#//$ g++ -o rt record_temp.cpp -lmysqlclient -L/usr/lib/mysql -I/usr/include/mysql
cmake_minimum_required(VERSION 2.8)

AUX_SOURCE_DIRECTORY(. MYSQL_TEMP_RECORD_SRCS)
ADD_DEFINITIONS("-L/usr/lib/mysql")
ADD_DEFINITIONS("-I/usr/include/mysql")
#add iniparser support 
#ADD_DEFINITIONS("-I../iniparser")
#ADD_DEFINITIONS("-L../iniparser")
#ADD_SUBDIRECTORY(../iniparser)
#set(EXTRA_LIBS ${EXTRA_LIBS} iniparser)

#include_directories("/usr/include/mysql")
SET(CMAKE_INSTALL_PREFIX /usr)
ADD_LIBRARY(TempRecord SHARED ${MYSQL_TEMP_RECORD_SRCS})

set(CMAKE_CXX_CFLAGS "-Wl,-soname=libTempRecord.so,-rpath=/usr/lib")
set(CMAKE_CXX_CFLAGS "-I${PROJECT_SOURCE_DIR}/iniparser")
#set(CMAKE_CXX_CFLAGS "-Wl,-rpath=../iniparser")
target_link_libraries(TempRecord -lmysqlclient )
target_link_libraries(TempRecord -L../iniparser  -I../iniparser -Wl,-rpath=../iniparser)
target_link_libraries(TempRecord iniparser )
INSTALL(TARGETS TempRecord   DESTINATION lib)
#INSTALL(FILES record_temp.hpp DESTINATION include)

set_target_properties(TempRecord PROPERTIES OUTPUT_NAME "TempRecord")


	
