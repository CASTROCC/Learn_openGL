//
// Created by Superman on 2019/10/9.
//

#ifndef LEARNOPENGL_CLION_LESSION_5_MATRIX_TRANS_HPP
#define LEARNOPENGL_CLION_LESSION_5_MATRIX_TRANS_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int lession_5_matrix_trans();

int lession_5_matrix_trans() {
    // 纹理映射采用的是坐下角为（0，0）的坐标系统

    // GL_NEAREST 邻近过滤 （舍）马赛克
    // GL_LINEAR 线性过滤 （入） 模糊

    // 我们需要使用glTexParameter*函数为放大和缩小指定过滤方式。这段代码看起来会和纹理环绕方式的设置很相似：
    //
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLFWwindow *window = createWindow();

    SharderClass selfSharder("./sharderUtils/sharderLibs/trans_texture/texture.vs",
                             "./sharderUtils/sharderLibs/trans_texture/texture.fs");


    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    unsigned int texture;
    glGenTextures(1, &texture);
//    glActiveTexture(GL_TEXTURE0);
    // 纹理单元GL_TEXTURE0默认总是被激活，所以当我们使用glBindTexture的时候，无需激活任何纹理单元
    //OpenGL至少保证有16个纹理单元供你使用，也就是说你可以激活从GL_TEXTURE0到GL_TEXTRUE15
    glBindTexture(GL_TEXTURE_2D, texture);

    generateTexture("./assets/texture/face.png");  // 生成texture像素点交给glsl渲染

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

//    glm::mat4 trans = glm::mat4(1.0f);// 初始化矩阵，设置齐次坐标为0
//    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 1.0f));  // 创建（位移）矩阵 这里可以使用缩放或 评移 或 旋转矩阵进行变换
//    vec = trans * vec;   // 210


//    glm::mat4 trans = glm::mat4(1.0f);
//    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));  // 创建旋转矩阵
//    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
//
//    unsigned int transformLoc = glGetUniformLocation(selfSharder.ID, "transform"); // uniform transofrm 属性并修改
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container

        glm::mat4 trans = glm::mat4(1.0f);

        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // 根据时间的推移创建旋转矩阵

        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f)); // 创建平移矩阵 平移位于旋转之后！

        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));


//        float scaleAmount = sin(glfwGetTime());
//        trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
//        glUniformMatrix4fv(glGetUniformLocation(selfSharder.ID, "transform"), 1, GL_FALSE, &trans[0][0]); // this time take the matrix value array's first element as its memory pointer value

        selfSharder.use();


        unsigned int transformLoc = glGetUniformLocation(selfSharder.ID, "transform"); // 查找uniform transofrm 属性并修改
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    return 0;
}


#endif //LEARNOPENGL_CLION_LESSION_5_MATRIX_TRANS_HPP
