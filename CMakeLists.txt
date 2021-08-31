cmake_minimum_required(VERSION 3.10)

project(Placement-Management-System)
add_executable(${PROJECT_NAME} main.cpp)
include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib_static_SPMS.a sqlite3)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib_dynamic_SPMS.so sqlite3)

# find_package (SQLite3)
# if (SQLITE3_FOUND)
#   include_directories(${SQLITE3_INCLUDE_DIRS})
#   target_link_libraries (${PROJECT_NAME} ${SQLITE3_LIBRARIES})
# endif (SQLITE3_FOUND)
