#include "camera.h"
using namespace std;

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(CameraXAngle)) * cos(glm::radians(CameraYAngle));
    front.y = sin(glm::radians(CameraYAngle));
    front.z = sin(glm::radians(CameraXAngle)) * cos(glm::radians(CameraYAngle));
    Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 view) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
																   MovementSpeed(SPEED), 
																   MouseSensitivity(SENSITIVITY)
																   
    {
        Position = position;
        WorldUp = up;
        View = view;
        CameraXAngle = 0.0f;
        x_angle_target = 0.0f;
        CameraYAngle = -1.5708f;
        instruction_num = 1;
        right = true;
        updateCameraVectors();
    }
// Constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
																					  MovementSpeed(SPEED), 
																				      MouseSensitivity(SENSITIVITY)
																					  
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    View = glm::vec3(posX, posY, posZ);
    CameraXAngle = 0.0f;
    x_angle_target = 0.0f;
    CameraYAngle = -1.5708f;
    instruction_num = 1;
    right = true;
    updateCameraVectors();
}


// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, View, Up);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    printf("CameraXAngle :%f\n", CameraXAngle);
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
    {
        Position.x += velocity*sin(CameraXAngle);
        Position.z += velocity*cos(CameraXAngle);
        View.x += velocity*sin(CameraXAngle);
		View.z += velocity*cos(CameraXAngle);
    }
    if (direction == BACKWARD)
    {
        Position.x -= velocity*sin(CameraXAngle);
        Position.z -= velocity*cos(CameraXAngle);
        View.x -= velocity*sin(CameraXAngle);
        View.z -= velocity*cos(CameraXAngle);
    }
    if (direction == LEFT)
    {   
        CameraXAngle += velocity;
        View.x = Position.x-sin(CameraXAngle);
        View.z = Position.z-cos(CameraXAngle);
    }
    if (direction == RIGHT)
    {
        CameraXAngle -= velocity;
        View.x = Position.x-sin(CameraXAngle);
        View.z = Position.z-cos(CameraXAngle);
    }
}

void Camera::turn_left(bool FREE, float angle, int num)
{
    if(FREE == false && num == instruction_num)
    {
        right = false;
        x_angle_target = angle;
    } 
}

void Camera::turn_right(bool FREE, float angle, int num)
{
    if(FREE == false && num == instruction_num)
    {
        right = true;
        x_angle_target = angle;

    } 
}

void Camera::move()
{
    if(right == true)
    {
        if(CameraXAngle > x_angle_target)
        {
            CameraXAngle = CameraXAngle+0.01;
        }
    }
    else
    {
        if(CameraXAngle < x_angle_target)
        {
            CameraXAngle = CameraXAngle+0.01;
        }
    }
}

bool Camera::check()
{
    bool check = false;
    if(CameraXAngle-0.02 < x_angle_target && x_angle_target < CameraXAngle+0.02)
        check = true;
    return check;
}



