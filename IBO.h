#ifndef IBO_CLASS_H
#define IBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class IBO {
public:
	GLuint ID;
	IBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !IBO_CLASS_H
