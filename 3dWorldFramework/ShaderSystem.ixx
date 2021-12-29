module;
#include <GL/glew.h>

#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <fileSystem>

export module ShaderSystem;

import BaseShader;

export namespace ShaderSystem {
	class ShaderProgram {
	public:
		ShaderProgram() {};
		ShaderProgram(std::tuple<GLint, std::vector<BaseShader>, std::string, std::filesystem::path> shadProgram) {
			shaderProgramID = std::get<0>(shadProgram);
			shaders = std::get<1>(shadProgram);
			shaderProgramName = std::get<2>(shadProgram);
			m_shaderFolder = std::get<3>(shadProgram);
		}
		virtual ~ShaderProgram() {};

		void reloadShader() {
			glLinkProgram(shaderProgramID);
			for (auto shad : shaders) {
				glDeleteShader(shad.shaderID);
			}
			glDeleteProgram(shaderProgramID);

			if (m_shaderFolder != "") {
				//loadShadersInFolder(m_shaderFolder);
				isReloaded = true;
			}
		}

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