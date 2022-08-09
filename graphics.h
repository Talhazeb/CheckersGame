#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <direct.h>
#include <windows.h>

#define getcwd _getcwd
#define DEFSL "\\res\\"



class graphics
{
private:
	sf::Texture textu;
	std::string cwd(const std::string &res);

public:
	void init(const std::string &path);

	sf::Texture *map();
};