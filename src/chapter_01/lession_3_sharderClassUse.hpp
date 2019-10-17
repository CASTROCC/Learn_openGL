//
// Created by Superman on 2019/10/7.
//

#ifndef LEARNOPENGL_CLION_LESSION_3_SHARDERCLASSUSE_HPP
#define LEARNOPENGL_CLION_LESSION_3_SHARDERCLASSUSE_HPP

int lession_3_sharderClassUse() {
    GLFWwindow *window = createWindow();

//    SharderClass selfSharder("./sharderUtils/sharderLibs/3.3/3.3sharder.vs",
//                        "./sharderUtils/sharderLibs/3.3/3.3sharder.fs");
    SharderClass selfSharder("./sharderUtils/sharderLibs/3.3_exercise/3.3sharder.vs",
                             "./sharderUtils/sharderLibs/3.3_exercise/3.3sharder.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        selfSharder.use();
        selfSharder.setFloat("xOffset", sin(glfwGetTime()) / 2.0f);
        selfSharder.setFloat("offsetColor", cos(glfwGetTime()) / 2.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


#endif //LEARNOPENGL_CLION_LESSION_3_SHARDERCLASSUSE_HPP
