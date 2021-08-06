#include "ShaderProgram.h"
#include "glad/glad.h"
#include <algorithm>
#include "Shader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

GLuint nr::ShaderProgram::GetLocation(const std::string& uniformName) const
{
	return glGetUniformLocation(programID_, uniformName.data());
}
nr::ShaderProgram::ShaderProgram(const std::string& programName) :programName_(programName)
{

}
void nr::ShaderProgram::RegisterShader(std::unique_ptr<Shader>&& shader)
{
	shaders_.emplace_back(std::move(shader));
}
bool nr::ShaderProgram::Run()
{
	// check if shaders are fine first
	for (const auto& shader : shaders_) {
		if (!shader->CheckShader()) return false;
	}
	// create the program
	programID_ = glCreateProgram();
	// attatch the registered shaders
	std::for_each(shaders_.begin(), shaders_.end(), [this](const std::unique_ptr<Shader>& shader) {
		glAttachShader(programID_, shader->ID());
		});

	// link the program
	glLinkProgram(programID_);
	int success;
	char infoLog[512];
	glGetProgramiv(programID_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID_, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
	// decouple the shaders
	std::for_each(shaders_.begin(), shaders_.end(), [](std::unique_ptr<Shader>& shader) {
		glDeleteShader(shader->ID());
		});
	return success;
}
void nr::ShaderProgram::Use()
{
	glUseProgram(programID_);
}
void nr::ShaderProgram::SetUniformVec3(const std::string& uniformName, const glm::vec3& vec)
{
	GLuint uniformLoc = GetLocation(uniformName);
	glUniform3f(uniformLoc, vec.x, vec.y, vec.z);
}

void nr::ShaderProgram::SetUniformVec2(const std::string& uniformName, const glm::vec2& vec)
{
	GLuint uniformLoc = GetLocation(uniformName);
	glUniform2f(uniformLoc, vec.x, vec.y);
}

void nr::ShaderProgram::SetUniformMat4(const std::string& uniformName, const glm::mat4& mat)
{
	GLuint uniformLoc = GetLocation(uniformName);
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat));
}
void nr::ShaderProgram::SetUniformInt(const std::string& uniformName, const int& val)
{
	GLuint uniformLoc = GetLocation(uniformName);
	glUniform1i(uniformLoc, val);
}
void nr::ShaderProgram::SetUniformFloat(const std::string& uniformName, const float& val)
{
	GLuint uniformLoc = GetLocation(uniformName);
	glUniform1f(uniformLoc, val);
}
