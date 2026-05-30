#include "Shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
	: _program(0)
{
	const std::string vertexSource = Shader::loadFile(vertexPath);
	const std::string fragmentSource = Shader::loadFile(fragmentPath);
	const GLuint vertex = Shader::compile(GL_VERTEX_SHADER, vertexSource, vertexPath);
	const GLuint fragment = Shader::compile(GL_FRAGMENT_SHADER, fragmentSource, fragmentPath);

	_program = glCreateProgram();
	if (!_program)
	{
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		throw std::runtime_error("failed to create shader program");
	}

	glAttachShader(_program, vertex);
	glAttachShader(_program, fragment);
	glLinkProgram(_program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	try
	{
		Shader::checkLink(_program);
	}
	catch (...)
	{
		glDeleteProgram(_program);
		_program = 0;
		throw;
	}
}

Shader::~Shader(void)
{
	if (_program)
		glDeleteProgram(_program);
}

void Shader::use(void) const
{
	glUseProgram(_program);
}

GLuint Shader::id(void) const
{
	return _program;
}

std::string Shader::loadFile(const std::string &path)
{
	std::ifstream file(path.c_str());
	std::stringstream buffer;

	if (!file)
		throw std::runtime_error("failed to open shader file: " + path);
	buffer << file.rdbuf();
	if (file.bad())
		throw std::runtime_error("failed to read shader file: " + path);
	return buffer.str();
}

GLuint Shader::compile(GLenum type, const std::string &source, const std::string &path)
{
	const char *sourcePtr = source.c_str();
	const GLuint shader = glCreateShader(type);

	if (!shader)
		throw std::runtime_error("failed to create shader: " + path);
	glShaderSource(shader, 1, &sourcePtr, NULL);
	glCompileShader(shader);

	try
	{
		Shader::checkCompile(shader, path);
	}
	catch (...)
	{
		glDeleteShader(shader);
		throw;
	}
	return shader;
}

void Shader::checkCompile(GLuint shader, const std::string &path)
{
	GLint success = GL_FALSE;
	GLint logLength = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_TRUE)
		return;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength < 1)
		logLength = 1;

	std::vector<GLchar> log(logLength);
	glGetShaderInfoLog(shader, logLength, NULL, &log[0]);

	throw std::runtime_error("shader compile error in " + path + ":\n" + &log[0]);
}

void Shader::checkLink(GLuint program)
{
	GLint success = GL_FALSE;
	GLint logLength = 0;

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_TRUE)
		return;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength < 1)
		logLength = 1;

	std::vector<GLchar> log(logLength);
	glGetProgramInfoLog(program, logLength, NULL, &log[0]);

	throw std::runtime_error("shader link error:\n" + std::string(&log[0]));
}
