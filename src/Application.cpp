#include "Application.hpp"

#include "ObjParser.hpp"

#include <cmath>
#include <stdexcept>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application::Application(const std::string &modelPath)
	: _window(800, 600, "scop"),
	  _shader(NULL),
	  _mesh(NULL),
	  _texture(0),
	  _position(0.0f, 0.0f, 0.0f),
	  _rotation(0.0f, 0.0f, 0.0f),
	  _lastFrameTime(0.0f),
	  _textureMix(0.0f),
	  _textureTarget(0.0f),
	  _textureEnabled(false),
	  _autoRotate(true),
	  _tWasPressed(false),
	  _rWasPressed(false)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("failed to initialize GLAD");

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);

	_shader = new Shader("shaders/mesh.vert", "shaders/mesh.frag");
	createCheerfulTexture();
	_mesh = new Mesh(ObjParser::parse(modelPath));
	_lastFrameTime = static_cast<float>(glfwGetTime());
}

Application::~Application(void)
{
	delete _mesh;
	delete _shader;
	if (_texture)
		glDeleteTextures(1, &_texture);
}

int Application::run(void)
{
	while (!_window.shouldClose())
	{
		const float currentTime = static_cast<float>(glfwGetTime());
		const float deltaTime = currentTime - _lastFrameTime;
		_lastFrameTime = currentTime;

		processInput(deltaTime);
		updateTextureTransition(deltaTime);

		const Mat4 model = modelMatrix();
		const Mat4 view = Mat4::translate(Vec3(0.0f, 0.0f, -3.0f));
		int framebufferWidth = 800;
		int framebufferHeight = 600;

		glfwGetFramebufferSize(_window.handle(), &framebufferWidth, &framebufferHeight);
		if (framebufferHeight <= 0)
			framebufferHeight = 1;
		const Mat4 projection = Mat4::perspective(
			45.0f * 3.1415926535f / 180.0f,
			static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight),
			0.1f,
			100.0f
		);
		const Mat4 mvp = projection * view * model;
		const GLint mvpLocation = glGetUniformLocation(_shader->id(), "uMVP");
		const GLint textureMixLocation = glGetUniformLocation(_shader->id(), "uTextureMix");
		const GLint textureLocation = glGetUniformLocation(_shader->id(), "uTexture");

		glClearColor(0.18f, 0.22f, 0.28f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_shader->use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);
		if (mvpLocation >= 0)
			glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.ptr());
		if (textureMixLocation >= 0)
			glUniform1f(textureMixLocation, _textureMix);
		if (textureLocation >= 0)
			glUniform1i(textureLocation, 0);
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
	const bool tPressed = glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;
	const bool rPressed = glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (tPressed && !_tWasPressed)
	{
		_textureEnabled = !_textureEnabled;
		_textureTarget = _textureEnabled ? 1.0f : 0.0f;
	}
	if (rPressed && !_rWasPressed)
		_autoRotate = !_autoRotate;
	_tWasPressed = tPressed;
	_rWasPressed = rPressed;

	if (_autoRotate)
		_rotation.y += 0.55f * deltaTime;

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

void Application::updateTextureTransition(float deltaTime)
{
	const float speed = 1.4f * deltaTime;

	if (_textureMix < _textureTarget)
	{
		_textureMix += speed;
		if (_textureMix > _textureTarget)
			_textureMix = _textureTarget;
	}
	else if (_textureMix > _textureTarget)
	{
		_textureMix -= speed;
		if (_textureMix < _textureTarget)
			_textureMix = _textureTarget;
	}
}

void Application::setPixel(std::vector<unsigned char> &pixels, int width, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	const int index = (y * width + x) * 3;

	pixels[index] = r;
	pixels[index + 1] = g;
	pixels[index + 2] = b;
}

void Application::createCheerfulTexture(void)
{
	const int width = 128;
	const int height = 128;
	std::vector<unsigned char> pixels(width * height * 3);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			unsigned char r = 126;
			unsigned char g = 190;
			unsigned char b = 244;
			const float fx = static_cast<float>(x) / static_cast<float>(width - 1);
			const float fy = static_cast<float>(y) / static_cast<float>(height - 1);
			const float dx = fx - 0.72f;
			const float dy = fy - 0.28f;
			const float sun = std::sqrt(dx * dx + dy * dy);

			if (fy > 0.68f)
			{
				r = 84;
				g = 196;
				b = 112;
			}
			if (sun < 0.18f)
			{
				r = 255;
				g = 220;
				b = 78;
			}
			if (fx > 0.10f && fx < 0.58f && fy > 0.14f && fy < 0.56f)
			{
				const float arc = std::fabs((fy - 0.56f) - (fx - 0.34f) * (fx - 0.34f) * 2.0f);
				if (arc < 0.025f)
				{
					r = 238;
					g = 64;
					b = 72;
				}
				else if (arc < 0.050f)
				{
					r = 255;
					g = 160;
					b = 56;
				}
				else if (arc < 0.075f)
				{
					r = 255;
					g = 222;
					b = 80;
				}
				else if (arc < 0.100f)
				{
					r = 64;
					g = 190;
					b = 116;
				}
				else if (arc < 0.125f)
				{
					r = 78;
					g = 142;
					b = 236;
				}
			}
			setPixel(pixels, width, x, y, r, g, b);
		}
	}

	for (int y = 44; y < 84; ++y)
	{
		for (int x = 45; x < 83; ++x)
		{
			const float dx = (static_cast<float>(x) - 64.0f) / 19.0f;
			const float dy = (static_cast<float>(y) - 64.0f) / 20.0f;

			if (dx * dx + dy * dy <= 1.0f)
				setPixel(pixels, width, x, y, 255, 238, 168);
		}
	}
	for (int y = 58; y < 62; ++y)
	{
		for (int x = 55; x < 59; ++x)
			setPixel(pixels, width, x, y, 60, 60, 60);
		for (int x = 70; x < 74; ++x)
			setPixel(pixels, width, x, y, 60, 60, 60);
	}
	for (int x = 55; x < 74; ++x)
	{
		const int y = 70 + static_cast<int>(4.0f * std::sin((static_cast<float>(x - 55) / 18.0f) * 3.1415926535f));
		for (int yy = y; yy < y + 3; ++yy)
			setPixel(pixels, width, x, yy, 80, 80, 80);
	}

	glGenTextures(1, &_texture);
	if (!_texture)
		throw std::runtime_error("failed to create texture");
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
	glGenerateMipmap(GL_TEXTURE_2D);
}

Mat4 Application::modelMatrix(void) const
{
	return Mat4::translate(_position)
		* Mat4::rotateZ(_rotation.z)
		* Mat4::rotateY(_rotation.y)
		* Mat4::rotateX(_rotation.x);
}
