//
//  main.cpp
//  Learn_OpenGL
//
//  Created by Superman on 2019/9/30.
//  Copyright © 2019 Superman. All rights reserved.
//
int lession_01();

int lession_01() {
    // 实例化GLFW窗口
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

        GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        // 创建完窗口,通知GLFW将我们窗口的上下文设置为当前线程的主上下文
        glfwMakeContextCurrent(window);

        // GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD
        // 给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }


        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, bframebuffer_size_callback_01);

        while (!glfwWindowShouldClose(window)) {

          
            glClearColor(0.3f, 0.3f, 0.2f, 1.0f);

            // 当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色
            glClear(GL_COLOR_BUFFER_BIT);

            // glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
            glfwSwapBuffers(window);

            // glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
            glfwPollEvents();
            
            processInput(window);
        }

        glfwTerminate();
        return 0;
    }




