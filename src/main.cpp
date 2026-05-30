#include "Application.hpp"

#include <exception>
#include <iostream>

int main(void)
{
	try
	{
		Application app;
		return app.run();
	}
	catch (const std::exception &error)
	{
		std::cerr << "scop: " << error.what() << std::endl;
		return 1;
	}
}
