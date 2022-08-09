
#include "graphics.h"

std::string graphics::cwd(const std::string &res)
{
	char currwd[FILENAME_MAX];
	std::string resu;

	if (getcwd(currwd, sizeof(currwd)) != NULL)
	{
		resu = currwd;
		resu += DEFSL + res;
	}
	return resu;
}

void graphics::init(const std::string &path)
{

	try
	{

		if (!textu.loadFromFile(cwd(path))) 
			throw 1;
	}
	catch (int)
	{
		std::string err = cwd(path);
		err += " not found";
		MessageBoxA(NULL, err.c_str(), "Error!", MB_ICONEXCLAMATION | MB_OK);

		throw;
	}
}
sf::Texture * graphics::map()
{

	return &textu;
}
