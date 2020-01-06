#ifndef SKYBOX_H
#define SKYBOX_H

#include "shader.h"
#include "model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Skybox
{
public:
	Shader* skyboxShader;
	unsigned int skyboxVAO, skyboxVBO;
	Skybox();
	void get_skybox(glm::mat4 view, glm::mat4 projection);
private:
	unsigned int skyboxTexture;
};

#endif