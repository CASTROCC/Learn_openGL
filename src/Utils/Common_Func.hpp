//
//  Common_Func.hpp
//  Learn_OpenGL
//
//  Created by Superman on 2019/10/2.
//  Copyright © 2019 Superman. All rights reserved.
//

#ifndef Common_Func_hpp
#define Common_Func_hpp
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "string.h"

using namespace std;


void bframebuffer_size_callback_01(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, Camera *camera, float delta);
GLFWwindow * createWindow(float screenWidth, float screenHeight);
void generateTexture(const char *path);
//void

void generateTexture(const char *path) {
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 加载并生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    unsigned int colortype;
    if(strstr(path, ".jpg")) {
        colortype = GL_RGB;
    } else if(strstr(path, ".png")) {
        colortype = GL_RGBA;
    } else {
        colortype = GL_RGB;
    }
    stbi_set_flip_vertically_on_load(true);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, colortype, width, height, 0, colortype, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); // 为当前绑定的纹理自动生成所有需要的多级渐远纹理
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void bframebuffer_size_callback_01(GLFWwindow* window, int width, int height) {
    
    glViewport(0, 0, width, height);
    
    cout << "on change frame " << endl;
}

void processInput(GLFWwindow *window , Camera *camera = NULL, float deltatime = 0.0f)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (camera != NULL) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera->processInputs(Camera_Movement::FORWARD, deltatime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera->processInputs(Camera_Movement::BACKWARD, deltatime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera->processInputs(Camera_Movement::LEFT, deltatime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera->processInputs(Camera_Movement::RIGHT, deltatime);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            camera->processInputs(Camera_Movement::UP, deltatime);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            camera->processInputs(Camera_Movement::DOWN, deltatime);
        }
    }
}

GLFWwindow* createWindow(float screenWidth = 800.0f, float screenHeight = 600.0f) {
    glfwInit();

    // 使用glfwWindowHint函数来配置GLFW

    // 因为使用的版本是version3.3 所以需要告诉GLFW 主版本是3
    // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // 次版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // 告诉GLFW我们使用的是核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 使用的是Mac OS X系统，你还需要加下面这行代码到你的初始化代码中这些配置才能起作用
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    // 创建完窗口,通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    // GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD
    // 给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }


    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, bframebuffer_size_callback_01);
    return window;
};
#endif /* Common_Func_hpp */
