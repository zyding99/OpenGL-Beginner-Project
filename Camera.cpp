#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) : 
	width(width), height(height), Position(position) {}

void Camera::updateMatrix(float FOVdeg, float zNear, float zFar) {

	glm::mat4 view{ 1.0f };
	glm::mat4 proj{ 1.0f };

	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::perspective(glm::radians(FOVdeg), (float)width / height, zNear, zFar);

	camMatrix = proj * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}


void Camera::Inputs(GLFWwindow* window) {
	
	// KEY INPUTS
	// WASD
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}

	// UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		Position += speed * -Up;
	}

	// SPEED UP / DOWN
	//if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
	//	speed += 0.1f;
	//}
	//if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
	//	speed -= 0.1f;
	//}
	//if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
	//	speed = 0.1f;
	//}

	// DASH
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}

	// MOUSE INPUTS
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick) {
			glfwSetCursorPos(window, width / 2, height / 2);
			firstClick = false;
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - 0.5 * height) / height;
		float rotY = sensitivity * (float)(mouseX - 0.5 * width) / width;

		// rotate around X axis (local)
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		if (glm::angle(newOrientation, Up) > glm::radians(5.0f) && glm::angle(newOrientation, -Up) > glm::radians(5.0f)) {
			Orientation = newOrientation;
		}
		// rotate around Y axis (local)
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
		glfwSetCursorPos(window, width / 2, height / 2);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}