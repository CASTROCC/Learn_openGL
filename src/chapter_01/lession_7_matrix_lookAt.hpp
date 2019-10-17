//
// Created by Superman on 2019/10/11.
//

#ifndef LEARNOPENGL_CLION_LESSION_7_MATRIX_LOOKAT_HPP
#define LEARNOPENGL_CLION_LESSION_7_MATRIX_LOOKAT_HPP
int lession_7_matrix_lookAt();
//void processInputs(GLFWwindow *window, glm::vec4 *cameraPos);
//
//void processInputs(GLFWwindow *window, glm::vec3 *cameraFront, glm::vec3 *cameraPos, glm::vec3 *cameraUp) {
//    float cameraSpeed = .05f;
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        *cameraPos -= cameraSpeed * (*cameraFront);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        *cameraPos -= cameraSpeed * (*cameraFront);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        *cameraPos -= glm::normalize(glm::cross(cameraFront, *cameraUp)) * cameraSpeed;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        *cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//}

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_back(GLFWwindow* window, double offsetX, double offsetY);


bool    firstMouse = true;
double  lastX = 0.0f;
double  lastY = 0.0f;
float   offsetX = 0.0f;
float   offsetY = 0.0f;
float   yaw = 0.0f;
float   pitch = 0.0f;

// 此处的cameraFront为负数是为了使相机的朝向平行于原点z轴 从而使相机正对前方
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

// 透视投影 视角范围 移动鼠标滚轮时需要每帧更新透视投影 （通过改变fov的值达到放大缩小的效果）
float fov = 45.0f;
void scroll_back(GLFWwindow* window, double offsetX, double offsetY) {
    if(fov >= 1.0f && fov <= 45.0f)
        fov -= offsetY;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 45.0f)
        fov = 45.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX       = xpos;
        lastY       = ypos;
        firstMouse  = false;
    }
    offsetX = xpos - lastX;
    offsetY = ypos - lastY;
    lastX   = xpos;
    lastY   = ypos;

    float sensitivity   = 0.05; // 鼠标移动阻力
    offsetX             = sensitivity * offsetX;
    offsetY             = sensitivity * offsetY;

    // 计算偏航角 及 俯仰角
    yaw += offsetX;
    pitch -= offsetY;

    // 限制上下旋转范围，俯仰角不得超过90度。
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}


int lession_7_matrix_lookAt() {
    GLFWwindow *window = createWindow();

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

    // 绑定vbo 注册 opengl每次解析顶点数据 的方法
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

    // 使用透视矩阵渲染texture 达到近大远小的效果
    glm::mat4 rota = glm::mat4(1.0);
    rota = glm::rotate(rota, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // 沿x轴旋转

    // 此处使用lookAt矩阵
    glm::mat4 view = glm::mat4(1.0f);
//    view =
//            glm::lookAt(
//            glm::vec3(0.0f, 0.0f, 3.0f),
//            glm::vec3(0.0f, 0.0f, 0.0f),
//            glm::vec3(0.0f, 1.0f, 0.0f)
//    );

//    glm::mat4 s = glm::mat4(1.0f);
//    s = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // 创建透视投影
    glEnable(GL_DEPTH_TEST); // 开启深度测试

    // 定义一个自由移动摄像机
    glm::vec3   cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
//    glm::vec3 cameraFront   = glm::vec3(0.0f, 0.0f, -1.0f); // 相机距离？
    glm::vec3          up   = glm::vec3(0.0f, 1.0f, 0.0f);

    // 隐藏光标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 注册鼠标移动回调用
    glfwSetCursorPosCallback(window, mouse_callback);

    // 注册鼠标滚轮回调
    glfwSetScrollCallback(window, scroll_back);

    // deltatime
    float lastFrametime = glfwGetTime();
    float deltatime;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltatime = currentFrame - lastFrametime;
        lastFrametime = currentFrame;
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 清除上一帧储存的深度缓存
        glClear(GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
//        selfSharder.setMatrix(rota, "model");

        selfSharder.use();

        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);

        //float raduis = 10.0f;
        // Y轴不变 绕Y轴旋转摄像机
        // float cameraX = sin(glfwGetTime()) * raduis; // 变换摄像机的X轴
        // float cameraZ = cos(glfwGetTime()) * raduis; // 变换摄像机的Y轴
//        view       = glm::lookAt(
//                glm::vec3(cameraX, 0.0f, cameraZ),
//                glm::vec3(0.0f, 0.0f, 0.0f),
//                glm::vec3(0.0f, 1.0f, 0.0f)
//        );  // 生成观察坐标


        // 通过按键修改相机位置
        float cameraSpeed = 2.5f; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront * deltatime;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront * deltatime;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed * deltatime;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed * deltatime;

        // 观察矩阵
        view = glm::lookAt(cameraPos, cameraFront + cameraPos, up);

        // 剪裁矩阵
        projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);  // 生成投影矩阵（透视投影）


        selfSharder.setMatrix(projection, "perspective");
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


#endif //LEARNOPENGL_CLION_LESSION_7_MATRIX_LOOKAT_HPP
