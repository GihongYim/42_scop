#include "Application.hpp"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	try
	{
		const std::string modelPath = argc > 1 ? argv[1] : "assets/42.obj";
		Application app(modelPath);
		return app.run();
	}
	catch (const std::exception &error)
	{
		std::cerr << "scop: " << error.what() << std::endl;
		return 1;
	}
}
