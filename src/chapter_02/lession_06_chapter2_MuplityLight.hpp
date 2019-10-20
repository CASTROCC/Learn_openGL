//
// Created by Superman on 2019/10/18.
//

#ifndef LEARNOPENGL_CLION_LESSION_06_CHAPTER2_MUPLITYLIGHT_HPP
#define LEARNOPENGL_CLION_LESSION_06_CHAPTER2_MUPLITYLIGHT_HPP

namespace lession_06_chapter2_MuplityLight {
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

    glm::vec3 pointLightPositions[] = {
            glm::vec3( 0.7f,  0.2f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    struct Pointlight {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float linear;
        float quadratic;
        float constant;
    };

    struct DirLight {
        glm::vec3 direction;

        glm::vec3 ambient;  // 环境光
        glm::vec3 diffuse;  // 漫反色
        glm::vec3 specular; // 镜面反射
    };

    Pointlight pointlightAttr {
        glm::vec3(0.05f, 0.05f, 0.05f),
        glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.09,
        0.039,
        1.0
    };

    DirLight dirlightAttr {
        glm::vec3(-0.2f, -1.0f, -0.3f),

        glm::vec3(0.05f, 0.05f, 0.05f),
        glm::vec3(0.4f, 0.4f, 0.4f),
        glm::vec3(0.5f, 0.5f, 0.5f)
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

    int muplityLight_Demo () {

        GLFWwindow* window = createWindow(screenWidth, screenHeight);

        SharderClass selfSharder("./sharderUtils/sharderLibs/light_sharder/Muplitylight_Sharder/cube_vert.glsl",
                                 "./sharderUtils/sharderLibs/light_sharder/Muplitylight_Sharder/cube_frag.glsl"); // cube Sharder

        SharderClass lightSharder("./sharderUtils/sharderLibs/light_sharder/Muplitylight_Sharder/light_vert.glsl",
                                  "./sharderUtils/sharderLibs/light_sharder/Muplitylight_Sharder/light_frag.glsl"); // light Sharder



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
        unsigned int texture, texture1;
        glGenTextures(0, &texture);
        glGenTextures(1, &texture1);

        glActiveTexture(GL_TEXTURE0);
        // 纹理单元GL_TEXTURE0默认总是被激活，所以当我们使用glBindTexture的时候，无需激活任何纹理单元
        //OpenGL至少保证有16个纹理单元供你使用，也就是说你可以激活从GL_TEXTURE0到GL_TEXTRUE15
        glBindTexture(GL_TEXTURE_2D, texture);
        generateTexture("./assets/texture/box.png");
        // texture1
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        generateTexture("./assets/texture/steel.png");


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
        selfSharder.setInt("material.diffuse", 0);
        selfSharder.setInt("material.specular", 1);

        while (!glfwWindowShouldClose(window)) {
            float currentFrame = glfwGetTime();
            deltatime = currentFrame - lastFrametime;
            lastFrametime = currentFrame;

            // 按键注册
            processInput(window, &camera, deltatime);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除上一帧储存的深度缓存

            selfSharder.use();

            // 材质反光度
            selfSharder.setFloat("material.shininess", 32.0f);
            // 设置观察位置 对于glsl来说是及其重要的一个参数
            selfSharder.setVec3("viewPos", camera.Position);

            // 点光源
            const string str1 = "PointsLights[";
            const string str2 = "].";
            const string attrs[] = {
                "position", "ambient", "diffuse", "specular", "constant", "linear", "quadratic"
            };

//            for (int j = 0; j < 3; ++j) {
//                glm::vec3 pos = pointLightPositions[j];
//
//                ostringstream position;
//                position << str1 << j << str2 << attrs[0];
//
//                ostringstream ambient;
//                ambient << str1 << j << str2 << attrs[1];
//
//                ostringstream diffuse;
//                diffuse << str1 << j << str2 << attrs[2];
//
//                ostringstream specular;
//                specular << str1 << j << str2 << attrs[3];
//
//                ostringstream constant;
//                constant << str1 << j << str2 << attrs[4];
//
//                ostringstream linear;
//                linear << str1 << j << str2 << attrs[5];
//
//                ostringstream quadratic;
//                quadratic << str1 << j << str2 << attrs[6];
//
//                selfSharder.setVec3(position.str(), pointLightPositions[j]);
//                selfSharder.setVec3(ambient.str(), pointlightAttr.ambient);
//                selfSharder.setVec3(diffuse.str(),  pointlightAttr.diffuse);
//                selfSharder.setVec3(specular.str(),  pointlightAttr.specular);
//                selfSharder.setFloat(constant.str(),  pointlightAttr.constant);
//                selfSharder.setFloat(linear.str(), pointlightAttr.linear);
//                selfSharder.setFloat(quadratic.str(), pointlightAttr.quadratic);
//            }

            // point light 1
            selfSharder.setVec3("pointLights[0].position", pointLightPositions[0]);
            selfSharder.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
            selfSharder.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
            selfSharder.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
            selfSharder.setFloat("pointLights[0].constant", 1.0f);
            selfSharder.setFloat("pointLights[0].linear", 0.09);
            selfSharder.setFloat("pointLights[0].quadratic", 0.032);
            // point light 2
            selfSharder.setVec3("pointLights[1].position", pointLightPositions[1]);
            selfSharder.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
            selfSharder.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
            selfSharder.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
            selfSharder.setFloat("pointLights[1].constant", 1.0f);
            selfSharder.setFloat("pointLights[1].linear", 0.09);
            selfSharder.setFloat("pointLights[1].quadratic", 0.032);
            // point light 3
            selfSharder.setVec3("pointLights[2].position", pointLightPositions[2]);
            selfSharder.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
            selfSharder.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
            selfSharder.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
            selfSharder.setFloat("pointLights[2].constant", 1.0f);
            selfSharder.setFloat("pointLights[2].linear", 0.09);
            selfSharder.setFloat("pointLights[2].quadratic", 0.032);
            // point light 4
            selfSharder.setVec3("pointLights[3].position", pointLightPositions[3]);
            selfSharder.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
            selfSharder.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
            selfSharder.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
            selfSharder.setFloat("pointLights[3].constant", 1.0f);
            selfSharder.setFloat("pointLights[3].linear", 0.09);
            selfSharder.setFloat("pointLights[3].quadratic", 0.032);

            // 方向光
            selfSharder.setVec3("dirLight.direction", dirlightAttr.direction);
            selfSharder.setVec3("dirLight.ambient", dirlightAttr.ambient);
            selfSharder.setVec3("dirLight.diffuse", dirlightAttr.diffuse);
            selfSharder.setVec3("dirLight.specular", dirlightAttr.specular);

            // 聚光
            selfSharder.setVec3("spotLight.position", camera.Position);
            selfSharder.setVec3("spotLight.direction", camera.Front);
            selfSharder.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            selfSharder.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            selfSharder.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            selfSharder.setFloat("spotLight.constant", 1.0f);
            selfSharder.setFloat("spotLight.linear", 0.09);
            selfSharder.setFloat("spotLight.quadratic", 0.032);
            selfSharder.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            selfSharder.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));




            // 剪裁矩阵
            glm::mat4 perspective = glm::mat4(1.0f);
            glm::mat4 view        = glm::mat4(1.0f);
            glm::mat4 model       = glm::mat4(1.0f);

            perspective = glm::perspective(glm::radians(fov), screenWidth/ screenWidth, 0.1f, 100.0f);  // 生成投影矩阵（透视投影）
            view        = camera.GetMatrix();
            model       = glm::mat4(1.0f);

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

            // also draw the lamp object(s)
            lightSharder.use();
            lightSharder.setMatrix( perspective, "projection");
            lightSharder.setMatrix(view,"view");

            // we now draw as many light bulbs as we have point lights.
            glBindVertexArray(lightVAO);
            for (unsigned int i = 0; i < 4; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
                lightSharder.setMatrix(model,"model");
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

#endif //LEARNOPENGL_CLION_LESSION_06_CHAPTER2_MUPLITYLIGHT_HPP
