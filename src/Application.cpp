#include "Application.hpp"

#include "ObjParser.hpp"

#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application::Application(void)
	: _window(800, 600, "scop"),
	  _shader(NULL),
	  _mesh(NULL),
	  _position(0.0f, 0.0f, 0.0f),
	  _rotation(0.0f, 0.0f, 0.0f),
	  _lastFrameTime(0.0f)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("failed to initialize GLAD");

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);

	_shader = new Shader("shaders/mesh.vert", "shaders/mesh.frag");
	_mesh = new Mesh(ObjParser::parse("assets/cube.obj"));
	_lastFrameTime = static_cast<float>(glfwGetTime());
}

Application::~Application(void)
{
	delete _mesh;
	delete _shader;
}

int Application::run(void)
{
	while (!_window.shouldClose())
	{
		const float currentTime = static_cast<float>(glfwGetTime());
		const float deltaTime = currentTime - _lastFrameTime;
		_lastFrameTime = currentTime;

		processInput(deltaTime);

		const Mat4 model = modelMatrix();
		const Mat4 view = Mat4::translate(Vec3(0.0f, 0.0f, -2.3f));
		const Mat4 projection = Mat4::perspective(45.0f * 3.1415926535f / 180.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		const Mat4 mvp = projection * view * model;
		const GLint mvpLocation = glGetUniformLocation(_shader->id(), "uMVP");

		glClearColor(0.18f, 0.22f, 0.28f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_shader->use();
		if (mvpLocation >= 0)
			glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.ptr());
		_mesh->draw();

		_window.swapBuffers();
		_window.pollEvents();
	}
	return 0;
}

void Application::processInput(float deltaTime)
{
	const float moveSpeed = 1.2f * deltaTime;
	const float rotationSpeed = 1.8f * deltaTime;
	GLFWwindow *window = _window.handle();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		_position.x -= moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		_position.x += moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		_position.y -= moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		_position.y += moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		_position.z -= moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		_position.z += moveSpeed;

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		_rotation.x -= rotationSpeed;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		_rotation.x += rotationSpeed;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		_rotation.y -= rotationSpeed;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		_rotation.y += rotationSpeed;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		_rotation.z -= rotationSpeed;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		_rotation.z += rotationSpeed;
}

Mat4 Application::modelMatrix(void) const
{
	return Mat4::translate(_position)
		* Mat4::rotateZ(_rotation.z)
		* Mat4::rotateY(_rotation.y)
		* Mat4::rotateX(_rotation.x);
}
