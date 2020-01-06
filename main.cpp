#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "cube.h"
#include "skybox.h"
#include "alphabot.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Alphabot alphabot);
float detectClosestObject(glm::vec3 cubePositions[], float x, float z);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float A_SPEED = 0.02;
bool FREE = true;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 9.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Alphabot", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f, -0.5f,  0.0f), 
      glm::vec3( 4.0f, -0.5f, -15.0f), 
      glm::vec3(-3.5f, -0.5f, -2.5f),  
      glm::vec3(-6.8f, -0.5f, -12.3f),  
      glm::vec3( 4.4f, -0.5f, -3.5f),  
      glm::vec3(-8.7f, -0.5f, -7.5f),  
      glm::vec3( 10.3f, -0.5f, -2.5f),  
      glm::vec3( 11.5f, -0.5f, -2.5f), 
      glm::vec3( 10.5f, -0.5f, -1.5f), 
      glm::vec3(-8.3f, -0.5f, -1.5f)  
    };

    Cube cube;
    cube.set_as_obstacle();

    Cube floor;
    floor.set_as_ground();

    Alphabot alphabot;

    Skybox skybox;
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window, alphabot);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(35.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        //Set object as wanted
        floor.get_cube_as_ground(view, projection, 40.0f);
        cube.get_cube_as_obstacle(view, projection, cubePositions, 10);

        if(alphabot.check() && camera.check())
        {
            //enter your instructions here
            alphabot.turn_right(1.56f, 1);
            alphabot.go_forward(1, 2);
            alphabot.go_backward(1,3);
            alphabot.turn_left(0.5f, 4);
            camera.turn_left(FREE, 0.5f, 5);
            alphabot.go_forward(2, 6);
            alphabot.instruction_num += 1;
            camera.instruction_num += 1;
        }
        alphabot.generate(view, projection, cubePositions, 10);
        camera.move();
        
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skybox.get_skybox(view, projection);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, Alphabot alphabot )//float pos_x, float pos_z, float Angle)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        FREE = false;
    if(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        FREE = true;
    if(FREE == true)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    else
    {
        camera.Position = glm::vec3(alphabot.X,0.0f,alphabot.Z);
        camera.View = glm::vec3(alphabot.X-sin(alphabot.Angle+camera.CameraXAngle),0.0f,alphabot.Z-cos(alphabot.Angle+camera.CameraXAngle)); //glm::vec3(pos_x-sin(Angle),0.0f,pos_z-cos(Angle));
        printf("camera X: %f\n", camera.View.x);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

