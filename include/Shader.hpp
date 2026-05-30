#ifndef SHADER_HPP
# define SHADER_HPP

# include <string>
# include <glad/glad.h>

class Shader
{
public:
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	~Shader(void);

	void use(void) const;
	GLuint id(void) const;

private:
	GLuint _program;

	Shader(const Shader &other);
	Shader &operator=(const Shader &other);

	static std::string loadFile(const std::string &path);
	static GLuint compile(GLenum type, const std::string &source, const std::string &path);
	static void checkCompile(GLuint shader, const std::string &path);
	static void checkLink(GLuint program);
};

#endif
