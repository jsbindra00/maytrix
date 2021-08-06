#include <string>
namespace nr {
	class Shader {
		using GLuint = unsigned int;
	private:
		std::string shaderName_;
		std::string shaderSource_;
		GLuint shaderID_;
	public:
		Shader(const int& shaderType_, const std::string& shaderName, const std::string& shaderSourceFile);
		bool CheckShader();
		void Destroy();
		GLuint ID() const noexcept;
		~Shader();
	};
}