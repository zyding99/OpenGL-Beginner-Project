#include "Model.h"


int main() {
    // INITIALIZATION THE WINDOW
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // opengl version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // using CORE profile, which means only modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // set window size
    unsigned width = 800;
    unsigned height = 800;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(width, height, "My GLFW Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGL()) {
        return -1;
    }

    glViewport(0, 0, width, height);



    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");

    // set light color
    glm::vec4 lightColor{ 1.0f, 1.0f, 1.0f, 1.0f }; // white
    // set initial position
    glm::vec3 lightPos{ 0.0f, 2.0f, 0.0f };
    glm::mat4 lightModel{ 1.0f };
    lightModel = glm::translate(lightModel, lightPos);


    // set uniform values for shader
    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // create Camera Object
    Camera camera(width, height, glm::vec3(0.0f, 0.2f, 2.0f));

    // load models
    Model model("Models/bunny/scene.gltf");

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here

        // Set Background color
        // Set the clear color to customized color
        glClearColor(0.25f, 0.5f, 0.25f, 1.0f);
        // Clear the back color buffer && depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera operations and settings
        camera.Inputs(window);
        camera.updateMatrix(60.0f, 0.1f, 200.f);

        // RENDER OBJECT
        model.Draw(shaderProgram, camera);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }


    // Cleanup
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
