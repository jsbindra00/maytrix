#include "Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Utility.h"
nr::Shader::Shader(const int& shaderType_, const std::string& shaderName, const std::string& shaderSourceFile) :
	shaderName_(shaderName),
	shaderSource_(nr::utility::ReadFile(shaderSourceFile))
{
	// allocate an id for the shader
	shaderID_ = glCreateShader(shaderType_);
	// bind the source code
	auto str = shaderSource_.data();
	glShaderSource(shaderID_, 1, &str, NULL);
	// compile shader
	glCompileShader(shaderID_);
}

bool nr::Shader::CheckShader()
{
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID_, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID_, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return false;
	}
	std::cout << "SHADER FINE" << std::endl;
	return true;
}

void nr::Shader::Destroy()
{

}

GLuint nr::Shader::ID() const noexcept
{
	return shaderID_;
}

nr::Shader::~Shader()
{
	Destroy();
}

