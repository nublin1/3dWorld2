module;
#include <GL/glew.h>

#include <vector>
#include <string>
#include <fileSystem>
#include <iostream>
#include <fstream> 
#include <tuple>

export module ShaderLoader;

import BaseShader;
import ShaderSystem;


export class ShaderLoader {
public:
	ShaderLoader() {};
	~ShaderLoader() {};

	void loadShadersInFolder(std::string shaderName, std::filesystem::path shaderFolder) {
		clear();
		std::filesystem::file_status fileStatus = std::filesystem::file_status{};
		if (std::filesystem::status_known(fileStatus) ? std::filesystem::exists(fileStatus) : std::filesystem::exists(shaderFolder)) {
			std::filesystem::recursive_directory_iterator end;

			for (std::filesystem::recursive_directory_iterator i(shaderFolder); i != end; ++i) {
				const std::filesystem::path fileName = *i;
				if (fileName.extension() == ".vert" || fileName.extension() == ".vs")
					addShader(fileName, GL_VERTEX_SHADER, GL_VERTEX_SHADER_BIT);
				else if (fileName.extension() == ".tcs")
					addShader(fileName, GL_TESS_CONTROL_SHADER, GL_TESS_CONTROL_SHADER_BIT);
				else if (fileName.extension() == ".tes")
					addShader(fileName, GL_TESS_EVALUATION_SHADER, GL_TESS_EVALUATION_SHADER_BIT);
				else if (fileName.extension() == ".gs" || fileName.extension() == ".geom")
					addShader(fileName, GL_GEOMETRY_SHADER, GL_GEOMETRY_SHADER_BIT);
				else if (fileName.extension() == ".frag" || fileName.extension() == ".fs")
					addShader(fileName, GL_FRAGMENT_SHADER, GL_FRAGMENT_SHADER_BIT);
			}

			addShaderProgram();

			ShaderSystem::ShaderProgram shader_program(std::make_tuple(ShaderProgramID, shaders, shaderName, shaderFolder));
			//ResourcesStorage::addShader(shaderName, shader_program);
		}

		else {
			std::cout << shaderFolder << " does not exist\n";
			clear();
		}
	}

private:
	GLuint ShaderProgramID;
	std::vector<ShaderSystem::BaseShader> shaders;
	std::string shaderProgramName;

	void clear() {
		ShaderProgramID = 0;
		shaderProgramName = "";
		shaders.clear();
	}

	void addShader(std::filesystem::path filename, GLenum shadertype, GLbitfield shaderTypeBit) {
		ShaderSystem::BaseShader baseShader;
		int shader_lenght = 0;

		std::filesystem::path pathToFile = filename.filename().string();

		std::string name = pathToFile.replace_extension("").string();
		std::string shaderCode = readShader(filename.string(), shader_lenght);
		baseShader.shaderID = makeShader(shaderCode, shadertype, name);
		//baseShader.shadertype = shadertype;
		baseShader.shadertype = shaderTypeBit;
		baseShader.shaderName = pathToFile.string();

		shaders.push_back(baseShader);
	}

	std::string readShader(std::string filename, int& shaderLenght) {
		std::string ShaderCode;
		std::ifstream f_in(filename);
		std::string Line;

		if (f_in.is_open() && f_in.good()) {
			while (getline(f_in, Line)) {
				ShaderCode += "\n" + Line;
			}
		}
		f_in.close();
		if (!ShaderCode.empty()) {
			shaderLenght = ShaderCode.length();
		}
		else {
			std::cout << "ShaderCode is empty" << std::endl;
		}

		return ShaderCode;
	}

	GLuint makeShader(std::string& shaderCode, GLenum shadertype, std::string _shadername) {
		const char* shadercource_cstr = shaderCode.c_str();
		GLint ShaderID = glCreateShader(shadertype);
		glShaderSource(ShaderID, 1, &shadercource_cstr, NULL);
		glCompileShader(ShaderID);
		//GLint ShaderID = glCreateShaderProgramv(shadertype, 1, &shadercource_cstr);

		GLint success = 0;
		GLchar infoLog[1024];
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(ShaderID, 1024, NULL, infoLog);
			std::cout << "ERROR::" << _shadername << "::COMPILATION_FAILED" << infoLog << std::endl;
		}
		else {
			//cout << _shadername << "::COMPILATION_SUCCESS" << endl;
		}
		return ShaderID;
	}

	void addShaderProgram() {
		ShaderProgramID = glCreateProgram();

		if (!shaders.empty()) {
			for (ShaderSystem::BaseShader shad : shaders) {
				glAttachShader(ShaderProgramID, shad.shaderID);
				//glUseProgramStages(ShaderProgramID, shad.shadertype, shad.shaderID);
			}

			glLinkProgram(ShaderProgramID);
			//glValidateProgram(ShaderProgramID);
			GLint linkSuccess;
			GLchar infoLog[1024];
			glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &linkSuccess);
			if (!linkSuccess) {
				glGetProgramInfoLog(ShaderProgramID, 1024, NULL, infoLog);
				std::cout << "ERROR::LINK_STATUS::FAILED\n" << infoLog << std::endl;
			}
			else {
				printf("%sShaderID is %d\n", shaderProgramName.c_str(), ShaderProgramID);
				std::cout << "LINK_STATUS::SUCCESS" << std::endl;
			}

			std::cout << "" << std::endl;
		}
		else {
			std::cout << "ERROR::SHADER ARRAY IS EMPTY" << std::endl;
		}
	}
};