#ifndef APPLICATION_HPP
# define APPLICATION_HPP

# include "Math.hpp"
# include "Mesh.hpp"
# include "Shader.hpp"
# include "Window.hpp"

class Application
{
public:
	Application(void);
	~Application(void);

	int run(void);

private:
	Window _window;
	Shader *_shader;
	Mesh *_mesh;
	Vec3 _position;
	Vec3 _rotation;
	float _lastFrameTime;

	void processInput(float deltaTime);
	Mat4 modelMatrix(void) const;

	Application(const Application &other);
	Application &operator=(const Application &other);
};

#endif
