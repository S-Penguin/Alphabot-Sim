#include "cube.h"
using namespace std;

Cube::Cube()
{
	float cubeVertices[] = {
    // positions          // texture Coords
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
	//VAO VBO
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

}
void Cube::set_as_obstacle()
{
	cubeShader = new Shader("cube.vs", "cube.fs");
	cubeTexture = loadTexture("bleu.jpg");
    cubeShader->use();
	cubeShader->setInt("cube_texture", 1);
}

void Cube::set_as_ground()
{
	cubeShader = new Shader("ground.vs", "ground.fs");
	cubeTexture = loadTexture("brick.jpeg");
    cubeShader->use();
	cubeShader->setInt("ground_texture", 2);
}

void Cube::get_cube_as_obstacle(glm::mat4 view, glm::mat4 projection, glm::vec3 cubePositions[], unsigned int n)
{
	// cubes
    cubeShader->use();
    cubeShader->setMat4("view", view);
    cubeShader->setMat4("projection", projection);
    glBindVertexArray(cubeVAO);
    glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    //bind vertex

    for (unsigned int i = 0; i < n; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 cube = glm::mat4(1.0f);
        cube = glm::translate(cube, cubePositions[i]);
        cubeShader->setMat4("model", cube);

        
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Cube::get_cube_as_ground(glm::mat4 view, glm::mat4 projection, float size)
{
	//ground
        cubeShader->use();
        cubeShader->setMat4("view", view);
        cubeShader->setMat4("projection", projection);
        glm::mat4 ground = glm::mat4(1.0f);
        ground = glm::translate(ground, glm::vec3(0.0f, -1.5f, -5.0f));
        ground = glm::scale(ground, glm::vec3(size, 0.5f, size));
        cubeShader->setMat4("model", ground);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glActiveTexture(GL_TEXTURE2); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
}