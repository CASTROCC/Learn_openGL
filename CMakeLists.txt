cmake_minimum_required(VERSION 3.15)
project(learnOpenGL_Clion)

set(CMAKE_CXX_STANDARD 14)
# PROJECT_SOURCE_DIR 是 CMake 定义的宏，指向项目根目录

#set include
#include_directories("${PROJECT_SOURCE_DIR}/include")

# 添加头文件
set(ALL_H /usr/local/include)
include_directories(${ALL_H})


# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.0.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.3.dylib)

link_libraries( ${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

set(SOURCE_FILES "./libs/glad.c" "main.cpp" src/sharderUtils/SharderClass.hpp src/chapter_01/lession_3_sharderClassUse.hpp src/chapter_01/lession_4_2texture_mix.hpp src/chapter_01/lession_5_matrix_trans.hpp src/chapter_01/lession_6_matrix_coordsystem.hpp src/chapter_01/lession_7_matrix_lookAt.hpp src/Utils/Camera.hpp src/chapter_01/lession_8_matrix_selflookAt.hpp src/chapter_02/lession_01_chapter2_light.hpp src/Utils/template_Camera.hpp src/chapter_02/lession_02_chapter2_pongLight.hpp src/chapter_02/lession_03_chapter2_Materials.hpp src/chapter_02/lession_04_chapter2_LightMaps.hpp src/chapter_02/lession_05_chapter2_Light.hpp src/chapter_02/lession_06_chapter2_MuplityLight.hpp)
add_executable(learnOpenGL_Clion ${SOURCE_FILES})  #把main.app 作为入口函数

if (APPLE)
    target_link_libraries(learnOpenGL_Clion "-framework OpenGL")
    target_link_libraries(learnOpenGL_Clion "-framework GLUT")
endif()