cmake_minimum_required(VERSION 3.13)
project(Ubuntu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Ubuntu
        source/Main/Core.cpp
        source/Main/Core.hpp
        source/Main/Interface.cpp
        source/Main/Interface.hpp
        source/Scenes/MenuScene.hpp
        source/Scenes/MenuScene.cpp
        source/Scenes/Scene.hpp
        source/Scenes/Scene.cpp
        source/Scenes/SceneEvent.hpp
        source/Scenes/SceneEvent.cpp
        source/UIObjects/Buttons/Button.cpp
        source/UIObjects/Buttons/Button.hpp
        source/UIObjects/UIObject.hpp
        source/UIObjects/UIObject.cpp
        main.cpp
        source/Tools/Queue.cpp
        source/Tools/Queue.hpp source/UIObjects/UIinformation.cpp source/UIObjects/UIinformation.h source/Main/Pipes.cpp source/Main/Pipes.h source/Tools/Time.cpp source/Tools/Time.h source/UIObjects/Buttons/FunnyButton.cpp source/UIObjects/Buttons/FunnyButton.h source/Tools/DrawArray.cpp source/Tools/DrawArray.h source/GameObjects/GameInformation.h source/Tools/ICMessage.h source/Tools/ICMessage.cpp source/GameObjects/GameInformation.cpp source/GameObjects/GameInformation.cpp source/GameObjects/GameInformation.h source/Tools/ICMessage.cpp source/Tools/ICMessage.h)

# Detect and add SFML
set(SFML_DIR "/usr/share/SFML/cmake/Modules")
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Ubuntu ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

#Detect and add OpenGl
#find_package(OpenGL REQUIRED)

#set(GLFW_DIR "/usr/share/SFML/cmake/Modules")
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/include)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/libs)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLEW/include/GL)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLEW/libs)

#target_link_libraries(Ubuntu glfw3.a libglew32.a ${OPENGL_LIBRARIES})



