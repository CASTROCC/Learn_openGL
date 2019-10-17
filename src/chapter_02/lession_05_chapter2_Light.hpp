//
// Created by Superman on 2019/10/16.
//

#ifndef LEARNOPENGL_CLION_LESSION_05_CHAPTER2_LIGHT_HPP
#define LEARNOPENGL_CLION_LESSION_05_CHAPTER2_LIGHT_HPP

namespace lession_05_chapter02_Light {
    int Light_Demo();
    void mouse_callback_camera(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(float offsetX, float offsetY);


    float  screenWidth  = 800.0;
    float  screenHeight = 600.0;

    Camera camera;
    float  firstMouse = true;
    float  lastX      = 0.0f;
    float  lastY      = 0.0f;

    float  fov        = 45.0f;

    glm::vec3 cubePosition = glm::vec3( 0.0f,  0.0f,  0.0f);

    // 平行光
//    glm::vec3 light_Dir = glm::vec3( -0.2f, -1.0f, -0.3f); // 光源射向片段

    // 点光源
    glm::vec3 light_Pos = glm::vec3(0.0, 0.0, 2.0);

    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    // cube Position
    glm::vec3 cubePositions[] = {
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

//    // 三角渲染顺序
//    const unsigned int indices[] = {
//            0, 1, 3, // first triangle
//            1, 2, 3  // second triangle
//    };

    const float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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

    int Light_Demo() {

        GLFWwindow* window = createWindow(screenWidth, screenHeight);

        SharderClass selfSharder("./sharderUtils/sharderLibs/light_sharder/Light_Direction/cube_vert.glsl",
                                 "./sharderUtils/sharderLibs/light_sharder/Light_Direction/cube_frag.glsl"); // cube Sharder

        SharderClass lightSharder("./sharderUtils/sharderLibs/light_sharder/Light_Direction/light_vert.glsl",
                                  "./sharderUtils/sharderLibs/light_sharder/Light_Direction/light_frag.glsl"); // light Sharder



        unsigned int VBO, VAO, EBO, lightVAO;
        glGenVertexArrays(1, &VAO);

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 绑定EBO
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // 告诉openGL如何解析顶点数据
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1); // layout pos = 1;

        // 纹理
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2); // layout pos = 2;
        // 声明texture
        unsigned int texture, texture1, texture2;
        glGenTextures(0, &texture);
        glGenTextures(1, &texture1);
        glGenTextures(2, &texture2);

        glActiveTexture(GL_TEXTURE0);
        // 纹理单元GL_TEXTURE0默认总是被激活，所以当我们使用glBindTexture的时候，无需激活任何纹理单元
        //OpenGL至少保证有16个纹理单元供你使用，也就是说你可以激活从GL_TEXTURE0到GL_TEXTRUE15
        glBindTexture(GL_TEXTURE_2D, texture);
        generateTexture("./assets/texture/box.png");
        // texture1
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        generateTexture("./assets/texture/steel.png");
        // texture2
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        generateTexture("./assets/texture/matrix.jpg");


        // light顶点  (此处的灯使用的同样的顶点数组作为它的顶点数据，然而灯的着色器并没使用新添加的法向量，所以并不需要修改着色器或是添加新的属性配置)
        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // 但是应该告诉openGL如何解析修改后的顶点数组
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

        selfSharder.use();
        // 植入texure顶点数据
        selfSharder.setInt("material.lightMap", 0);
        selfSharder.setInt("material.specMap", 1);
        selfSharder.setInt("material.rayMap", 2);

        while (!glfwWindowShouldClose(window)) {
            float currentFrame = glfwGetTime();
            deltatime = currentFrame - lastFrametime;
            lastFrametime = currentFrame;

            // 按键注册
            processInput(window, &camera, deltatime);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除上一帧储存的深度缓存

            selfSharder.use();

            // 改变光源颜色
//            lightColor.x = sin(glfwGetTime() * 2.0f);
//            lightColor.y = sin(glfwGetTime() * 0.7f);
//            lightColor.z = sin(glfwGetTime() * 1.3f);

            // 设置材质状态
            selfSharder.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
            selfSharder.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
            selfSharder.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
            selfSharder.setFloat("material.shininess", 32.0f);

            selfSharder.setVec3("objColor", glm::vec3(1.0f, 0.5f, 0.31f));
            selfSharder.setVec3("lightColor",  lightColor);
            selfSharder.setVec3("viewPos", camera.Position);

            // 改变光源位置
//            light_Pos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
//            light_Pos.x = 1.0f + sin(glfwGetTime()) * 2.0f;

            // 设置材质光源混合状态
            //selfSharder.setVec3("light.direction", light_Dir);
            selfSharder.setVec3("light.ambient", lightColor * glm::vec3(0.5));
            selfSharder.setVec3("light.diffuse", lightColor * glm::vec3(0.2));
            selfSharder.setVec3("light.specular", 1.0f, 1.0f, 1.0f); // 镜面反射设置为1.0

            // 设置光源衰减值
            selfSharder.setFloat("light.constant", 1.0f);
            selfSharder.setFloat("light.linear", 0.09f);
            selfSharder.setFloat("light.quadratic", 0.032f);


            // 聚光
            selfSharder.setVec3("light.position",  camera.Position);
            selfSharder.setVec3("light.direction", camera.Front);
            selfSharder.setFloat("light.cutoff",   glm::cos(glm::radians(4.5f)));
            selfSharder.setFloat("light.outcutoff",   glm::cos(glm::radians(6.5f)));

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

            // 最后绘制顶点
            for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                selfSharder.setMatrix(model, "model");

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }


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
#endif //LEARNOPENGL_CLION_LESSION_05_CHAPTER2_LIGHT_HPP
