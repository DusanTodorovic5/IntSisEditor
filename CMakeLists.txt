
cmake_minimum_required(VERSION 3.0.0)
project(intsisEditor VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories("src/")
include_directories("hpp/")
file(GLOB files CONFIGURE_DEPENDS
     "*.h"
     "*.cpp"
     "hpp/*.hpp"
     "src/*.cpp"
)

add_executable(intsisEditor ${files})

target_link_libraries(intsisEditor sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)