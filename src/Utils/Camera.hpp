//
// Created by Superman on 2019/10/12.
//

#ifndef LEARNOPENGL_CLION_CAMERA_HPP
#define LEARNOPENGL_CLION_CAMERA_HPP

enum Camera_Movement {
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// 默认相机属性
const float YAM                 = -90.0f;
const float PITCH               = 0.0f;
const float MOVEMENTSPEED       = 2.5f;
const float MOUSESENSITIVITY    = 1.0f;
const float ZOOM                = 1.0f;

class Camera {

    public:
        // 生成相机矩阵属性
        glm::vec3 Position;
        glm::vec3 Up;
        glm::vec3 Front;
        glm::vec3 Right;

        glm::vec3 WorldUp;

        // 欧拉角
        float Yam;
        float Pitch;

        // 相机自身属性
        float MovementSpeed = 1.0f;
        float MouseSensitivity = 0.25f;
        float Zoom = 0.25f;

        // constructor
        Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                float yam = YAM, float pitch = PITCH
                ) {
            Position = pos; // Camera Position
            WorldUp = up;
            Yam = yam;
            Pitch = pitch;
            updateCameraVectors();
        }

        // Constructor with scalar values
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
            : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(MOVEMENTSPEED), MouseSensitivity(MOUSESENSITIVITY), Zoom(ZOOM)
        {
            Position = glm::vec3(posX, posY, posZ);
            WorldUp = glm::vec3(upX, upY, upZ);
            Yam = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }

        glm::mat4 GetMatrix() {
            return glm::lookAt(Position, Front + Position, Up);
        }

        void processInputs(Camera_Movement direction, float deltaTime) {
            float velocity = MovementSpeed * deltaTime; // 移动相机位置
            if (direction == FORWARD)
                Position += Front * velocity;
            if (direction == BACKWARD)
                Position -= Front * velocity;
            if (direction == LEFT)
                Position -= Right * velocity;
            if (direction == RIGHT)
                Position += Right * velocity;
            if (direction == UP)
                Position += Up * velocity;
            if (direction == DOWN)
                Position -= Up * velocity;

//            Position.y = 0.0f; // 将摄像机的位置固定在y轴的0.0f
        }

        void mouseInput(float offsetX, float offsetY, bool isRestraintYaw = true) {
            offsetX *= MouseSensitivity;
            offsetY *= MouseSensitivity;

            Yam     += offsetX;
            Pitch   += offsetY;

            if(isRestraintYaw) {
                if (Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }

            updateCameraVectors();
        }

        void scrollInputforFov( float offsetY, float *fov) {
            if(*fov >= 1.0f && *fov <= 45.0f)
                *fov -= offsetY;
            if(*fov <= 1.0f)
                *fov = 1.0f;
            if(*fov >= 45.0f)
                *fov = 45.0f;
        }

    private:
        void updateCameraVectors() {
            glm::vec3 front;

            front.x = cos(glm::radians(Yam)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yam)) * cos(glm::radians(Pitch));

            Front = glm::normalize(front);

            Right = glm::normalize(glm::cross(front, WorldUp)); // 右向量 = 前向量 ✖️ 往上的一个向量
            Up    = glm::normalize(glm::cross(Right, Front));
        }


};

#endif //LEARNOPENGL_CLION_CAMERA_HPP
