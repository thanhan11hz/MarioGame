cmake_minimum_required(VERSION 3.10)
project(Game LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_PATH "C:/raylib") 

include_directories(${RAYLIB_PATH}/include) 
link_directories(${RAYLIB_PATH}/lib)

add_library(box2d STATIC IMPORTED)          

set_target_properties(box2d PROPERTIES
    IMPORTED_LOCATION "C:/box2d/lib/libbox2d.a"      
    INTERFACE_INCLUDE_DIRECTORIES "C:/box2d/include" 
)

include_directories(include)

file(GLOB_RECURSE SOURCES "source/*.cpp")
add_executable(main ${SOURCES})

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resource
            $<TARGET_FILE_DIR:main>/resource)

target_link_libraries(main
    PRIVATE
        box2d     
        raylib
        -lopengl32 -lgdi32 -lwinmm)