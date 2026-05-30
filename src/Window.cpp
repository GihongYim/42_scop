#include "Window.hpp"

#include <stdexcept>
#include <glad/glad.h>

Window::Window(int width, int height, const std::string &title)
	: _handle(NULL), _width(width), _height(height)
{
	if (!glfwInit())
		throw std::runtime_error("failed to initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_handle = glfwCreateWindow(_width, _height, title.c_str(), NULL, NULL);
	if (!_handle)
	{
		glfwTerminate();
		throw std::runtime_error("failed to create GLFW window");
	}

	glfwMakeContextCurrent(_handle);
	glfwSetFramebufferSizeCallback(_handle, Window::framebufferSizeCallback);
}

Window::~Window(void)
{
	if (_handle)
		glfwDestroyWindow(_handle);
	glfwTerminate();
}

bool Window::shouldClose(void) const
{
	return glfwWindowShouldClose(_handle) != 0;
}

void Window::swapBuffers(void)
{
	glfwSwapBuffers(_handle);
}

void Window::pollEvents(void) const
{
	glfwPollEvents();
}

GLFWwindow *Window::handle(void) const
{
	return _handle;
}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}
