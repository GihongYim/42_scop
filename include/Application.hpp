#ifndef APPLICATION_HPP
# define APPLICATION_HPP

# include "Math.hpp"
# include "Mesh.hpp"
# include "Shader.hpp"
# include "Window.hpp"

# include <string>
# include <vector>
# include <glad/glad.h>

class Application
{
public:
	explicit Application(const std::string &modelPath);
	~Application(void);

	int run(void);

private:
	Window _window;
	Shader *_shader;
	Mesh *_mesh;
	GLuint _texture;
	Vec3 _position;
	Vec3 _rotation;
	float _lastFrameTime;
	float _textureMix;
	float _textureTarget;
	bool _textureEnabled;
	bool _autoRotate;
	bool _tWasPressed;
	bool _rWasPressed;

	void processInput(float deltaTime);
	void updateTextureTransition(float deltaTime);
	void createCheerfulTexture(void);
	void setPixel(std::vector<unsigned char> &pixels, int width, int x, int y, unsigned char r, unsigned char g, unsigned char b);
	Mat4 modelMatrix(void) const;

	Application(const Application &other);
	Application &operator=(const Application &other);
};

#endif
