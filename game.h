#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <iostream>
#include "graphics.h"

#include "checker_board.h"
#include "players.h"
#include "stdint.h"

#define box_num 32

class Game
{

private:
	sf::Event event;
	sf::RectangleShape end;
	sf::RenderWindow window;

	player P1;
	player P2;
	player *turn;
	player *nturn;

	std::vector<checker_board> boardblack;
	std::vector<checker_board> boardwhite;

	sf::Text txt;
	sf::Font font;

	graphics black_board_texture;
	graphics white_board_texture;
	graphics border;

	graphics pawn_border;
	graphics red_texture;
	graphics blue_texture;
	graphics red_king_texture;
	graphics blue_king_texture;

	void draw();
	bool events();

	void boardinit();
	void playerinit();
	void endblackrectangle();
	bool initfont();
	bool textureinit();
	void swap();

public:
	Game();

	bool run();
};