#include "shaderClass.h"

std::string get_file_contents(const char* filename) {

    std::ifstream inputFile(filename, std::ios::binary);

    if (!inputFile) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        throw(errno);
    }

    std::string contents;
    // Read the entire file into a buffer
    inputFile.seekg(0, std::ios::end);
    contents.resize(inputFile.tellg());
    inputFile.seekg(0, std::ios::beg);
    inputFile.read(&contents[0], contents.size());
    inputFile.close();

    return contents;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {

    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create Vertex shader and Fragment shader:

    // Vertex shader creation
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation error: " << infoLog << std::endl;
    }

    // Fragment shader creation
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation error: " << infoLog << std::endl;
    }

    // Shader program creation and linking
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Check for shader program linking errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "Shader program linking error: " << infoLog << std::endl;
    }

    // Cleanup shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // Shader Program Creation Complete!
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}

