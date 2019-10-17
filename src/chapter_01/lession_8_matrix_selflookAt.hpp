//
// Created by Superman on 2019/10/12.
//

#ifndef LEARNOPENGL_CLION_LESSION_8_MATRIX_SELFLOOKAT_HPP
#define LEARNOPENGL_CLION_LESSION_8_MATRIX_SELFLOOKAT_HPP

int lession_8_matrix_selflookAt();
void mouse_callback_camera(GLFWwindow* window, double xpos, double ypos);

Camera camera;

void mouse_callback_camera(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.mouseInput(xoffset, yoffset);
}


int lession_8_matrix_selflookAt() {

    GLFWwindow* window = createWindow(1920.0f, 1080.0f);

    SharderClass selfSharder("./sharderUtils/sharderLibs/coordsystem_texture/texture.vs",
                             "./sharderUtils/sharderLibs/coordsystem_texture/texture.fs");

    // 想渲染一个立方体，我们一共需要36个顶点
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // 设置10个cube的位置信息
    glm::vec3 positions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 注入顶点数据
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 绑定EBo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // 告诉openGL如何解析顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    generateTexture("./assets/texture/face.png");  // 生成texture像素点交给glsl渲染

    // camera object
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f)); // 初始相机坐标为(0.0f, 0.0f, 3.0f);

    // 开启深度测试
    glEnable(GL_DEPTH_TEST);
    // 隐藏光标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // deltatime
    float lastFrametime = glfwGetTime();
    float deltatime;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltatime = currentFrame - lastFrametime;
        lastFrametime = currentFrame;

        // 按键注册
        processInput(window);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            cout << "press _w" << endl;
            camera.processInputs(Camera_Movement::FORWARD, deltatime);
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            cout << "press _s" << endl;
            camera.processInputs(Camera_Movement::BACKWARD, deltatime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            cout << "press _a" << endl;
            camera.processInputs(Camera_Movement::LEFT, deltatime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            cout << "press _d" << endl;
            camera.processInputs(Camera_Movement::RIGHT, deltatime);
        }

        // 注册鼠标移动回调用
        glfwSetCursorPosCallback(window, mouse_callback_camera);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 清除上一帧储存的深度缓存
        glClear(GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
//        selfSharder.setMatrix(rota, "model");

        selfSharder.use();

        // 剪裁矩阵
        glm::mat4 perspective = glm::mat4(1.0f);
        glm::mat4 view        = glm::mat4(1.0f);;

        perspective = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);  // 生成投影矩阵（透视投影）
        view        = camera.GetMatrix();

        selfSharder.setMatrix(perspective, "perspective");
        selfSharder.setMatrix(view, "view");

        glBindVertexArray(VAO);

        for(unsigned int i = 0; i < 10; i++)
        {
            // 模型矩阵
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            selfSharder.setMatrix(model,"model" ); // 使10个cube产生不同的旋转缩放
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

#endif //LEARNOPENGL_CLION_LESSION_8_MATRIX_SELFLOOKAT_HPP
