#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <string>

#ifndef GLFW_INCLUDE_NONE
# define GLFW_INCLUDE_NONE
#endif
# include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const std::string &title);
	~Window(void);

	bool shouldClose(void) const;
	void swapBuffers(void);
	void pollEvents(void) const;
	GLFWwindow *handle(void) const;

private:
	GLFWwindow *_handle;
	int _width;
	int _height;

	Window(const Window &other);
	Window &operator=(const Window &other);

	static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};

#endif
