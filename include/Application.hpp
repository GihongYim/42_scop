#ifndef APPLICATION_HPP
# define APPLICATION_HPP

# include "Window.hpp"

class Application
{
public:
	Application(void);
	~Application(void);

	int run(void);

private:
	Window _window;

	Application(const Application &other);
	Application &operator=(const Application &other);
};

#endif
