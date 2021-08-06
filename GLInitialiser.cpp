#include "GLInitialiser.h"
#include "Camera.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include "imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>



nr::GLInitialiser::GLInitialiser(unsigned int windowWidth, unsigned int windowHeight, const char* windowName)
	: shaderProgram_(std::make_unique<nr::ShaderProgram>("shaderProgram")),
	camera_(std::make_unique<nr::Camera>(glm::vec3(0, 0, 1)))
{
	Init(windowWidth, windowHeight, windowName);
}
void nr::GLInitialiser::InitialiseArrays()
{


	const float CUBE_DIM = 1;
	const float POINT_SPACING = 0.1;

	std::vector<float> points;
	std::vector<unsigned int> indices;


	auto N_POINTS = static_cast<unsigned int>(CUBE_DIM) / POINT_SPACING;
	for (unsigned int y = 0; y < N_POINTS; ++y)
	{
	//unsigned int y = 1;
		for (unsigned int z = 0; z < N_POINTS; ++z)
		{
			for (unsigned int x = 0; x < N_POINTS; ++x)
			{
				float vx = -(CUBE_DIM / 2) + x * (CUBE_DIM / N_POINTS);
				float vy = -(CUBE_DIM / 2) + y * (CUBE_DIM / N_POINTS);
				float vz = -(CUBE_DIM / 2) + z * (CUBE_DIM / N_POINTS);
				points.insert(points.end(), { vx,vy,vz });
				unsigned int index = y * N_POINTS*N_POINTS + z * N_POINTS + x;
				indices.push_back((index + 1));
				std::cout << index << std::endl;
				NUMPOINTS++;

			}
		}
	}
	//for (float y = 0; y < CUBE_DIM; y += POINT_SPACING)
	//{
	//	for (float z = -CUBE_DIM / 2; z < CUBE_DIM / 2; z += POINT_SPACING)
	//	{
	//		for (float x = -CUBE_DIM / 2; x < CUBE_DIM / 2; x += POINT_SPACING)
	//		{
	//			points.insert(points.end(), { x,y,z });
	//			NUMPOINTS++;
	//			indices.push_back(NUMPOINTS % (CUBE_DIM / POINT_SPACING) + )
	//		}
	//		
	//	}
	//	
	//}

	
	
	
	

	glGenVertexArrays(1, &VAO_);
	glBindVertexArray(VAO_);

	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.data()), indices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
}
void nr::GLInitialiser::Render()
{
	bool active;
	float size;
	float color[4];


	float start = 0;
	int frameNumber = 0;
	bool swap = false;

	while (!glfwWindowShouldClose(window_))
	{
		float elapsedTime = glfwGetTime();
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open Directory", "Ctrl+O"))
				{
					/*	std::string defaultPath = "C:\\Users\\jasbi\\OneDrive\\Documents\\Items";
						std::optional<std::string> dir = nr::util::windows::NavigationDialogue::BrowseFolder();
						if (dir.has_value())
						{
							std::vector<boost::filesystem::path> paths = nr::utility::ListItems<boost::filesystem::directory_iterator>(boost::filesystem::path(*dir));
							std::for_each(paths.begin(), paths.end(), [](const boost::filesystem::path& path) {
								});
						}*/
				}
				if (ImGui::MenuItem("Save", "Ctrl+S"))
				{
				}
				if (ImGui::MenuItem("Exit", "Ctrl+E"))
				{
					return;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}


		shaderProgram_->SetUniformMat4("projectionMatrix_", glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 10000.0f));

		static float radius = 10;
		static float speed = 0;
		static float cameraHeight = 0;
		static float matrix[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

	
		ImGui::BeginGroup();
		ImGui::SliderFloat("Camera Speed", &speed, 0.0f, 0.01f, "%.3f");
		ImGui::SliderFloat("Camera Height", &cameraHeight, 0.0f, 10.0f, "%.3f");
		ImGui::SliderFloat("Camera Radius", &radius, 0.0f, 10.0f, "%.3f");
		if (ImGui::BeginTable("table", 3)) {
			ImGui::TableNextColumn();
			ImGui::InputFloat("0", &matrix[0]);
			ImGui::TableNextColumn();
			ImGui::InputFloat("1", &matrix[4]);
			ImGui::TableNextColumn();
			ImGui::InputFloat("2", &matrix[8]);
			ImGui::TableNextColumn();
			ImGui::InputFloat("3", &matrix[1]);
			ImGui::TableNextColumn();
			ImGui::InputFloat("4", &matrix[5]);
			ImGui::TableNextColumn();
			ImGui::InputFloat("5", &matrix[9]);
			ImGui::TableNextColumn();
			ImGui::InputFloat("6", &matrix[2]);
			ImGui::TableNextColumn();
			ImGui::InputFloat("7", &matrix[6]);
			ImGui::TableNextColumn();
			ImGui::InputFloat("8", &matrix[10]);
			ImGui::EndTable();
		}
		ImGui::EndGroup();

		
		glm::mat4 model = glm::make_mat4(matrix);
		shaderProgram_->SetUniformMat4("modelMatrix_", model);


		


		double normalSpeed = speed / 100;
		float posX = radius * cos((2 * 3.14 * normalSpeed) * frameNumber);
		float posZ = radius * sin((2 * 3.14 * normalSpeed) * frameNumber);

		glm::mat4 viewMatrix = glm::lookAt(glm::vec3(posX, cameraHeight, posZ), glm::vec3(0.0f,0.0f,0.0f), camera_->Up());
		shaderProgram_->SetUniformMat4("viewMatrix_", viewMatrix);


		glBindVertexArray(VAO_);
		//glDrawElements(GL_LINE_LOOP, NUMPOINTS, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_LINE_LOOP, 0, NUMPOINTS);
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window_);
		glfwPollEvents();
		++frameNumber;
	}
}
void nr::GLInitialiser::Init(unsigned int windowWidth, unsigned int windowHeight, const char* windowTitle)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window_ = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	if (window_ == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetWindowUserPointer(window_, this);
	glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {static_cast<nr::GLInitialiser*>(glfwGetWindowUserPointer(window))->KeyCallback(window, key, scancode, action, mods); });
	glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {static_cast<nr::GLInitialiser*>(glfwGetWindowUserPointer(window))->MouseButtonCallback(window, button, action, mods); });
	glfwMakeContextCurrent(window_);
	gladLoadGL();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window_, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	shaderProgram_->RegisterShader(std::make_unique<nr::Shader>(GL_VERTEX_SHADER, "vertexShader", "vertexShader.vert"));
	shaderProgram_->RegisterShader(std::make_unique<nr::Shader>(GL_FRAGMENT_SHADER, "fragmentShader", "fragmentShader.frag"));
	shaderProgram_->Run();
	shaderProgram_->Use();

	InitialiseArrays();
	// create the image quad
}
void nr::GLInitialiser::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key) {
	case GLFW_KEY_S:
	{
		camera_->MoveSouth(0);
		break;
	}
	case GLFW_KEY_W:
	{
		camera_->MoveNorth(0);
		break;
	}
	case GLFW_KEY_A:
	{
		camera_->MoveEast(0);
		break;
	}
	case GLFW_KEY_D:
	{
		camera_->MoveWest(0);
		break;
	}
	case GLFW_KEY_UP:
	{
		camera_->MoveUp();
		break;
	}
	case GLFW_KEY_DOWN:
	{
		camera_->MoveDown();
		break;
	}
	}
}
void nr::GLInitialiser::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action != GLFW_PRESS) return;
	glm::vec2 mousePos;
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	std::cout << "{" << xPos << "," << yPos << "}" << std::endl;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		
		break;
	}
	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		break;
	}
	}
}
nr::GLInitialiser::~GLInitialiser()
{

}
