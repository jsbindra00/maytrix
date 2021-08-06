#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include <string>
#include <memory>
namespace nr {
	
	class Shader;
	class ShaderProgram {
		using GLuint = unsigned int;
	private:
		std::string programName_;
		std::vector<std::unique_ptr<nr::Shader>> shaders_;
		GLuint programID_;
		GLuint GetLocation(const std::string& uniformName) const;
	public:
		ShaderProgram(const std::string& programName);
		void RegisterShader(std::unique_ptr<Shader>&& shader);
		bool Run();
		void Use();
		void SetUniformVec3(const std::string& uniformName, const glm::vec3& vec);
		void SetUniformVec2(const std::string& uniformName, const glm::vec2& vec);
		void SetUniformMat4(const std::string& uniformName, const glm::mat4& mat);
		void SetUniformInt(const std::string& uniformName, const int& val);
		void SetUniformFloat(const std::string& uniformName, const float& val);
	};
}