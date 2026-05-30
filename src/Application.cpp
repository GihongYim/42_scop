#include "Application.hpp"

#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application::Application(void)
	: _window(800, 600, "scop")
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("failed to initialize GLAD");
	glViewport(0, 0, 800, 600);
}

Application::~Application(void)
{
}

int Application::run(void)
{
	while (!_window.shouldClose())
	{
		glClearColor(0.18f, 0.22f, 0.28f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		_window.swapBuffers();
		_window.pollEvents();
	}
	return 0;
}
