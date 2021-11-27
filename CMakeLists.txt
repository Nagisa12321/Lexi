cmake_minimum_required(VERSION 3.10)

# set the project name
set(project_name "Lexi")
project(${project_name})
message(STATUS "start project....")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# the .h files
add_library(lexi_interface INTERFACE)
target_include_directories(lexi_interface INTERFACE include include/_linux)

# include SDL2
find_package(SDL2 REQUIRED)
include_directories(${project_name} ${SDL2_INCLUDE_DIRS})

set(PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/_linux)
set(PROJECT_TESTS ${PROJECT_SOURCE_DIR}/test)
FILE(GLOB LEXI_SOURCE_FILES ${PROJECT_SOURCES}/*.cpp)
FILE(GLOB LEXI_TEST_FILES ${PROJECT_TESTS}/*.cpp)

# add the executable
add_executable(Lexi main.cpp ${LEXI_SOURCE_FILES})
# link
target_link_libraries(${project_name} PRIVATE lexi_interface ${SDL2_LIBRARIES} SDL2)

# create the test files
foreach(X ${LEXI_TEST_FILES})
    get_filename_component(raw_name ${X} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" cooked_name ${raw_name})

    message(STATUS "make and link the test file \"${cooked_name}\"")
    add_executable(${cooked_name} ${X} ${LEXI_SOURCE_FILES})
    target_link_libraries(${cooked_name} PRIVATE lexi_interface SDL2)
endforeach()

# install
install(TARGETS Lexi DESTINATION bin)