cmake_minimum_required( VERSION 3.1 )

project( cv1 )
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

include_directories( ${PROJECT_SOURCE_DIR}/lib/soil2/src )
include_directories( ${PROJECT_SOURCE_DIR}/lib/stb )
include_directories( ${PROJECT_SOURCE_DIR}/include )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory( lib/glfw )
add_subdirectory( lib/glm )

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        )

find_package(GLEW 2.0 REQUIRED)
find_package(ASSIMP REQUIRED)

include_directories(${ASSIMP_INCLUDE_DIR})

add_executable( cv1 ${SOURCES}
        src/scene/light/LightManager.cpp
        src/scene/light/LightManager.h
        src/util/math_utils.cpp
        src/util/math_utils.h
        src/model/shader/component/RotationObjectComponent.cpp
        src/model/shader/component/RotationObjectComponent.h
)
target_link_libraries( cv1 ${OPENGL_LIBRARIES} glfw glm GLEW::GLEW
        ${ASSIMP_LIBRARIES}
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/soil2/lib/macosx/libsoil2-debug.a"
        )
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'cv1' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT cv1 )
    endif()
endif()
