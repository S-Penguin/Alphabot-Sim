#ifndef CUBE_H
#define CUBE_H

#include "shader.h"
#include "model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube
{
public:
	Shader* cubeShader;
	unsigned int cubeVAO, cubeVBO;
	Cube();

	void set_as_obstacle();
	void set_as_ground();
	void get_cube_as_obstacle(glm::mat4 view, glm::mat4 projection, glm::vec3 cubePositions[],unsigned int n);
	void get_cube_as_ground(glm::mat4 view, glm::mat4 projection, float size);
private:
	unsigned int cubeTexture;
};
#endif