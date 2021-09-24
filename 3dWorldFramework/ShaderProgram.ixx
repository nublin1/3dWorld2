
#include <GL/glew.h>

#include <tuple>
#include <vector>
#include <string>
#include <fileSystem>

export module ShaderProgram;

export namespace ShaderProgram {
	struct BaseShader {
		GLint shaderID;
		GLenum shadertype;
		std::string shaderName;
	};

	class ShaderProgram {
	public:
		ShaderProgram() {};
		ShaderProgram(std::tuple<GLint, std::vector<BaseShader>, std::string, std::filesystem::path> shadProgram) {
			shaderProgramID = std::get<0>(shadProgram);
			shaders = std::get<1>(shadProgram);
			shaderProgramName = std::get<2>(shadProgram);
			m_shaderFolder = std::get<3>(shadProgram);
		}
		~ShaderProgram() {};

		void useShaderProgram() const { glUseProgram(shaderProgramID); }

		// getters & setters
		GLint					getShaderProgramID() { return shaderProgramID; }
		std::string				getShaderName() { return shaderProgramName; }
		std::filesystem::path	getShaderFolder() { return m_shaderFolder; }

		void setShaderProgramID(GLint ID) { this->shaderProgramID = ID; }

	private:
		GLint shaderProgramID;
		std::vector<BaseShader> shaders;
		std::string shaderProgramName;
		std::filesystem::path m_shaderFolder;
		bool isReloaded = false;
	};

}