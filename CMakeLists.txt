cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(cpp-project-template LANGUAGES CXX)

#add_executable(cpp-project-template helloworld.cpp)


set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Catch2/single_include) 
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(XSTL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/include) 
add_library(xstl INTERFACE)
target_include_directories(xstl INTERFACE ${XSTL_INCLUDE_DIR})

file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

add_executable(Atest ${TEST_FILES})
target_link_libraries(Atest Catch)
target_link_libraries(Atest xstl)

enable_testing()

add_test(
  NAME Sample_test
  COMMAND $<TARGET_FILE:Atest>
)