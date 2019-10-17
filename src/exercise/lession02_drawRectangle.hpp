//
//  lession02_drawRectangle.hpp
//  Learn_OpenGL
//
//  Created by Superman on 2019/10/3.
//  Copyright © 2019 Superman. All rights reserved.
//

#ifndef lession02_drawRectangle_hpp
#define lession02_drawRectangle_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Utils/Common_Func.hpp"
#include <iostream>

void lession02_drawRectangle();

const char *l2_vertexSharderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *l2_exce_fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.1f, 0.2f, 0.1f, 1.0f);\n"
    "}\n\0";

float vertexRectangle[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int drawIndex[] = {
    0, 1, 2, // 第一个三角形
    0, 2, 3  // 第二个三角形
};


// 添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形
float vertexArray[] = {
    0.25f, 0.0f, 0.0f,
    -0.25f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f,
    -0.5f, 0.0f, 0.0f
};
unsigned int drawArrayIndex[] = {
    0, 1, 2,
    0, 1, 3
};

// 创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色
// 两个linkPrograme 两个glUsePrograme, 


GLFWwindow * window;
unsigned int shaderProgram;
unsigned int VAO;
unsigned int EBO;
unsigned int VBO;

void lession02_drawRectangle() {
    
       window = createWindow();
    
       int vertexShader = glCreateShader(GL_VERTEX_SHADER);
       glShaderSource(vertexShader, 1, &l2_vertexSharderSource, NULL);
       glCompileShader(vertexShader);
       // check for shader compile errors
       int success;
       char infoLog[512];
       glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
       if (!success)
       {
           glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
           std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
       }
       // fragment shader
       int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
       glShaderSource(fragmentShader, 1, &l2_exce_fragmentShaderSource, NULL);
       glCompileShader(fragmentShader);
       // check for shader compile errors
       glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
       if (!success)
       {
           glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
           std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
       }
       // link shaders
       int shaderProgram = glCreateProgram();
       glAttachShader(shaderProgram, vertexShader);
       glAttachShader(shaderProgram, fragmentShader);
       glLinkProgram(shaderProgram);
       // check for linking errors
       glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
       if (!success) {
           glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
           std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
       }
       glDeleteShader(vertexShader);
       glDeleteShader(fragmentShader);

    
       unsigned int VBO, VAO, EBO;
       glGenVertexArrays(1, &VAO);
       glGenBuffers(1, &VBO);
       glGenBuffers(1, &EBO);
        
    // 使用2种VAO VBO数据绘制三角形
    // unsigned int VBOs[2], VAOs[2];
    // glGenVertexArrays(2, VAOs);
    // glGenBuffers(2, VBOs);
    
    //glBindVertexArray(VAOs[0]);
    //glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);
    
       glBindVertexArray(VAO);
       glBindBuffer(GL_ARRAY_BUFFER, VBO);
       glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
       glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawArrayIndex), drawArrayIndex, GL_STATIC_DRAW);

       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
       glEnableVertexAttribArray(0);

       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

       while (!glfwWindowShouldClose(window))
       {
           processInput(window);

           // 视口渲染
           glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
           glClear(GL_COLOR_BUFFER_BIT);

           glUseProgram(shaderProgram);
           glBindVertexArray(VAO);
           //glDrawArrays(GL_TRIANGLES, 0, 6);
//           glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
           glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
           glfwSwapBuffers(window);
           glfwPollEvents();
       }

       glDeleteVertexArrays(1, &VAO);
       glDeleteBuffers(1, &VBO);
       glDeleteBuffers(1, &EBO);

       glfwTerminate();
  
    
}

#endif /* lession02_drawRectangle_hpp */
