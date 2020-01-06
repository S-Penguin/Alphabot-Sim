#include "alphabot.h"
using namespace std;

Alphabot::Alphabot(): target_angle(0.0f),
					  right(true),
					  instruction_num(1),
					  up(true)
{
	X = 1.0f;
	Y = -2.0f;
	Z = 1.0f;
	Speed = 0.02f;
	Angle = 0.0f;
	x_target = X;
	z_target = Z;

	ourShader = new Shader("model.vs", "model.fs");
	ourModel = new Model("Alphabot.obj");

	modelTexture = loadTexture("hei.jpg");
}

void Alphabot::generate(glm::mat4 view, glm::mat4 projection, glm::vec3 cubePositions[], unsigned int n)
{
	// don't forget to enable shader before setting uniforms
    ourShader->use();
    ourShader->setInt("texture_diffuse1", 0);

    ourShader->setMat4("projection", projection);
    ourShader->setMat4("view", view);

     // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
	//if(abs(Angle) < abs(target_angle))
	if(right == true)
    {
    	if(Angle > target_angle)
    		Angle = Angle-Speed;
    }
    else
    {
    	if(Angle < target_angle)
    		Angle = Angle+Speed;
    }

    collisionAvoid(cubePositions, n);
	if(!(X-Speed < x_target && x_target < X+Speed && Z-Speed < z_target && z_target < Z+Speed))
	{
		if(up == true)
		{
			X = X-sin(Angle)*Speed;
			Z = Z-cos(Angle)*Speed;
		}
		else
		{
			X = X+sin(Angle)*Speed;
			Z = Z+cos(Angle)*Speed;
		}
	}
    model = glm::translate(model, glm::vec3(X, Y, Z)); // translate it down so it's at the center of the scene
    model = glm::rotate(model, Angle, glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
    ourShader->setMat4("model", model);
    ourModel->Draw(ourShader);
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, modelTexture);
}

void Alphabot::turn_right(float new_angle, int num)
{
	if(instruction_num == num)
	{
		right = true;
		target_angle -= new_angle;
	}
}

void Alphabot::turn_left(float new_angle, int num)
{
	if(instruction_num == num)
	{
		right = false;
		target_angle += new_angle;
	}
}

void Alphabot::go_forward(float distance, int num)
{
	if(instruction_num == num)
	{
		x_target = X-sin(Angle)*distance;
		z_target = Z-cos(Angle)*distance;
		up = true;
	}
}

void Alphabot::go_backward(float distance, int num)
{
	if(instruction_num == num)
	{
		x_target = X+sin(Angle)*distance;
		z_target = Z+cos(Angle)*distance;
		up = false;
	}
}


void Alphabot::collisionAvoid(glm::vec3 cubePositions[], unsigned int n)
{
	float expected_x;
	float expected_z;

    if (up == true)
    {
        expected_x = X-sin(Angle)*Speed;
        expected_z = Z-cos(Angle)*Speed;
    }
    else
    {
        expected_x = X + sin(Angle)*Speed;
        expected_z = Z + cos(Angle)*Speed;
    }
    int closest_i = detectClosestObject(cubePositions, n);
    if((cubePositions[closest_i].x-0.5f <= expected_x && cubePositions[closest_i].x+0.5f >= expected_x) && (cubePositions[closest_i].z-0.5f <= expected_z && cubePositions[closest_i].z+0.5f >= expected_z))
    {   
        printf("stop");
        x_target = X;
        z_target = Z;
    }

}

float Alphabot::detectClosestObject(glm::vec3 cubePositions[], unsigned int n)
{
    int closest_i = 0;
    float closest_length = 10;
    float length = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        length = sqrt((cubePositions[i].x-X)*(cubePositions[i].x-X)+(cubePositions[i].z-Z)*(cubePositions[i].z-Z));
        if(length < closest_length)
        {
            closest_length = length;
            closest_i = i;
        }
    }
    return closest_i;

}

bool Alphabot::check()
{
	bool check = false;
	if(Angle-Speed < target_angle && Angle+Speed > target_angle && X-Speed < x_target && X+Speed > x_target
		&& Z-Speed < z_target && Z+Speed > z_target)
		check = true;
	return check;
}

void Alphabot::set_pos(float x, float z)
{
	X = x;
	Z = z;
}

void Alphabot::set_speed(float speed)
{
	Speed = speed;
}