module;
#include <GL/glew.h>

#include <string>

export module BaseShader;

export namespace ShaderSystem {
	struct BaseShader {
		GLint shaderID;
		GLenum shadertype;
		std::string shaderName;
	};
}