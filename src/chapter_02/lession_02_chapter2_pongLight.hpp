//
// Created by Superman on 2019/10/13.
//

#ifndef LEARNOPENGL_CLION_LESSION_02_CHAPTER2_PONGLIGHT_HPP
#define LEARNOPENGL_CLION_LESSION_02_CHAPTER2_PONGLIGHT_HPP

// 环境光
// 漫反射
// 镜面反射

namespace lession_02_chapter02_Pong {
    int lightDemo();
    void mouse_callback_camera(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(float offsetX, float offsetY);


    float  screenWidth  = 1920.0;
    float  screenHeight = 1080.0;

    Camera camera;
    float  firstMouse = true;
    float  lastX      = 0.0f;
    float  lastY      = 0.0f;

    float  fov        = 45.0f;

    glm::vec3 cubePosition = glm::vec3( 0.0f,  0.0f,  0.0f);

    glm::vec3 light_Pos = glm::vec3(1.2f, 1.0f, 2.0f);

    // 三角渲染顺序
    const unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    const float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    void mouse_callback_camera(GLFWwindow* window, double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

        camera.mouseInput(xoffset, yoffset);
    }

    void scroll_callback(GLFWwindow *window, double offsetX, double offsetY) {
        camera.scrollInputforFov(offsetY, &fov);
    }

    int Pong_lightDemo() {

        GLFWwindow* window = createWindow(screenWidth, screenHeight);

        SharderClass selfSharder("./sharderUtils/sharderLibs/light_sharder/Pong_light/cube_vert.glsl",
                                 "./sharderUtils/sharderLibs/light_sharder/Pong_light/cube_frag.glsl"); // cube Sharder

        SharderClass lightSharder("./sharderUtils/sharderLibs/light_sharder/Pong_light/light_vert.glsl",
                "./sharderUtils/sharderLibs/light_sharder/Pong_light/light_frag.glsl"); // light Sharder

        unsigned int VBO, VAO, EBO, lightVAO;
        glGenVertexArrays(1, &VAO);

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 绑定EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // 告诉openGL如何解析顶点数据
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1); // layout pos = 1;

        // light顶点  (此处的灯使用的同样的顶点数组作为它的顶点数据，然而灯的着色器并没使用新添加的法向量，所以并不需要修改着色器或是添加新的属性配置)
        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // 但是应该告诉openGL如何解析修改后的顶点数组
        glEnableVertexAttribArray(0);

        // 相机矩阵
        camera = Camera(glm::vec3(0.0f, 0.0f, 6.0f)); // 初始相机坐标为(0.0f, 0.0f, 3.0f);

        // 开启深度测试
        glEnable(GL_DEPTH_TEST);
        // 隐藏光标
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // 注册鼠标移动回调用
        glfwSetCursorPosCallback(window, mouse_callback_camera);
        glfwSetScrollCallback(window, scroll_callback);

        // deltatime
        float lastFrametime = glfwGetTime();
        float deltatime;

        while (!glfwWindowShouldClose(window)) {
            float currentFrame = glfwGetTime();
            deltatime = currentFrame - lastFrametime;
            lastFrametime = currentFrame;

            // 按键注册
            processInput(window, &camera, deltatime);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除上一帧储存的深度缓存


            selfSharder.use();

            light_Pos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
            light_Pos.y = sin(glfwGetTime() / 2.0f) * 1.0f;

            selfSharder.setVec3("objColor", glm::vec3(1.0f, 0.5f, 0.31f));
            selfSharder.setVec3("lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));
            selfSharder.setVec3("lightPos", light_Pos);
            selfSharder.setVec3("viewPos", camera.Position);

            // 剪裁矩阵
            glm::mat4 perspective = glm::mat4(1.0f);
            glm::mat4 view        = glm::mat4(1.0f);
            glm::mat4 model       = glm::mat4(1.0f);

            perspective = glm::perspective(glm::radians(fov), screenWidth/ screenWidth, 0.1f, 100.0f);  // 生成投影矩阵（透视投影）
            view        = camera.GetMatrix();
            model       = glm::translate(model, cubePosition);


            selfSharder.setMatrix(perspective, "perspective");
            selfSharder.setMatrix(view, "view");
            selfSharder.setMatrix(model, "model");

            glBindVertexArray(VAO); // 重新启用VAO
            glDrawArrays(GL_TRIANGLES, 0, 36);

            lightSharder.use();
            glm::mat4 lightModel  = glm::mat4(1.0f);
            lightModel            = glm::translate(lightModel, light_Pos);
            lightModel            = glm::scale(lightModel, glm::vec3(0.2f));

            lightSharder.setMatrix(lightModel, "model");
            lightSharder.setMatrix(perspective,"perspective" );
            lightSharder.setMatrix(view, "view" );

            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteBuffers(1, &VBO);
        glfwTerminate();
        return 0;
    }
}
#endif //LEARNOPENGL_CLION_LESSION_02_CHAPTER2_PONGLIGHT_HPP
