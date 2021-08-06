#pragma once
#include <memory>
struct GLFWwindow;

namespace nr
{
	class Camera;
	class ShaderProgram;

	class GLInitialiser
	{
		using GLuint = unsigned int;
	protected:
		GLuint VBO_;
		GLuint EBO_;
		GLuint VAO_;

		GLFWwindow* window_;
		std::unique_ptr<Camera> camera_;
		std::unique_ptr<ShaderProgram> shaderProgram_;

		unsigned int NUMPOINTS{ 0 };

		void Init(unsigned int width, unsigned int height, const char* windowTitle);
		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		void InitialiseArrays();
	public:
		GLInitialiser(unsigned int windowWidth, unsigned int windowHeight, const char* windowName);
		
		void Render();
		~GLInitialiser();
	};
}