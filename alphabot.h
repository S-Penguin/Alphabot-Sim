#ifndef ALPHABOT_H
#define ALPHABOT_H

#include "shader.h"
#include "model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Alphabot
{
public:
	Shader* ourShader;
	Model* ourModel;
	float X;
	float Y;
	float Z;
	float target_angle;
	float Angle;
	bool right;
	int instruction_num;
	float Speed;
	Alphabot();
	void set_pos(float x, float z);
	void set_speed(float speed);
	void generate(glm::mat4 view, glm::mat4 projection, glm::vec3 cubePositions[], unsigned int n);
	void turn_left(float new_angle, int num);
	void turn_right(float new_angle, int num);
	void go_forward(float distance, int num);
	void go_backward(float distance, int num);
	bool check();
private:
	float x_target;
	float z_target;
    unsigned int modelTexture;
    bool up;
    void collisionAvoid(glm::vec3 cubePositions[], unsigned int n);
    float detectClosestObject(glm::vec3 cubePositions[], unsigned int n);
};
#endif