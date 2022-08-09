#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "graphics.h"

extern const float X_coordinates[8];
extern const float Y_coordinates[8];

class checker_board
{
private:
	sf::RectangleShape box;
	sf::RectangleShape box_path;

	int col;
	int id;
	int x_cord;
	int y_cord;
	void position();

public:
	checker_board(int clr, int id_loop, graphics*tboard, graphics*tborder);
	sf::Vector2i cord();
	sf::RectangleShape& display();
	sf::RectangleShape& showPath();
};
