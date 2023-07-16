#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera {
public:
	glm::vec3 Position; // default pos: origin
	glm::vec3 Orientation{ 0.0f, 0.0f, -1.0f }; // default camera direction: -z
	glm::vec3 Up{ 0.0f, 1.0f, 0.0f }; // default camera up direction: +y
	glm::mat4 camMatrix{ 1.0f };

	bool firstClick = true;
	int width, height;
	float speed = 0.1f;
	float sensitivity = 100.f;

	Camera(int width, int height, glm::vec3 position);

	void updateMatrix(float FOVdeg, float zNear, float zFar);
	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
};


#endif //!CAMERA_CLASS_H
