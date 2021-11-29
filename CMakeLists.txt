cmake_minimum_required(VERSION 3.10)

# set the project name
set(project_name "Lexi")
project(${project_name})
message(STATUS "start project....")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# debug mode
add_compile_options(-g)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# the .h files
add_library(lexi_interface INTERFACE)
target_include_directories(lexi_interface INTERFACE include/_linux include)

# include SDL2
find_package(SDL2 REQUIRED)
include_directories(${project_name} ${SDL2_INCLUDE_DIRS})

# include SDL2
find_package(SDL2_ttf REQUIRED)
include_directories(${project_name} ${SDL2_TTF_INCLUDE_DIRS})

# project files
set(PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_SOURCES_LINUX ${PROJECT_SOURCE_DIR}/src/_linux)
set(PROJECT_TESTS ${PROJECT_SOURCE_DIR}/test)
FILE(GLOB LEXI_SOURCE_FILES ${PROJECT_SOURCES}/*.cpp)
FILE(GLOB LEXI_SOURCE_LINUX_FILES ${PROJECT_SOURCES_LINUX}/*.cpp)
FILE(GLOB LEXI_TEST_FILES ${PROJECT_TESTS}/*.c*)

# show the file found
message("\n============= now show files found =============")
message(" > source files: ")
foreach(X ${LEXI_SOURCE_FILES})
    get_filename_component(raw_name ${X} NAME)
    message("${raw_name}")
endforeach()
message("\n > source files(linux): ")
foreach(X ${LEXI_SOURCE_LINUX_FILES})
    get_filename_component(raw_name ${X} NAME)
    message("${raw_name}")
endforeach()
message("\n > test files: ")
foreach(X ${LEXI_TEST_FILES})
    get_filename_component(raw_name ${X} NAME)
    message("${raw_name}")
endforeach()
message("")
message("")


# tmp obj
add_library(LEXI_SOURCE OBJECT ${LEXI_SOURCE_FILES})
add_library(LEXI_SOURCE_LINUX_FILES OBJECT ${LEXI_SOURCE_LINUX_FILES})
target_include_directories(LEXI_SOURCE INTERFACE include/_linux include)
target_include_directories(LEXI_SOURCE_LINUX_FILES INTERFACE include/_linux include)
target_link_libraries(LEXI_SOURCE PRIVATE lexi_interface ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_link_libraries(LEXI_SOURCE_LINUX_FILES PRIVATE lexi_interface ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# add the executable
add_executable(${project_name} main.cpp $<TARGET_OBJECTS:LEXI_SOURCE> $<TARGET_OBJECTS:LEXI_SOURCE_LINUX_FILES>)
# link
target_link_libraries(${project_name} PRIVATE lexi_interface ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# create the test files
foreach(X ${LEXI_TEST_FILES})
    get_filename_component(raw_name ${X} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" cooked_name ${raw_name})

    message(STATUS "make and link the test file \"${cooked_name}\"")
    add_executable(${cooked_name} ${X} $<TARGET_OBJECTS:LEXI_SOURCE> $<TARGET_OBJECTS:LEXI_SOURCE_LINUX_FILES>)
    target_link_libraries(${cooked_name} PRIVATE lexi_interface ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endforeach()

# install
install(TARGETS Lexi DESTINATION bin)