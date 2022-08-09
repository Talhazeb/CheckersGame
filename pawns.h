
#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "graphics.h"

extern const float X_coordinates[8];
extern const float Y_coordinates[8];

struct pawnmove
{
	int id;
	int x;
	int y;
};
struct path
{
	pawnmove begin;
	pawnmove end;
	int opponentid;
	bool first;
	bool multi;
};

class pawns
{

private:
	sf::CircleShape circle;
	int player_id;
	int status;
	sf::Vector2f mouseRectOffset;
	sf::Vector2f lastpos;

	int board;
	pawnmove id_cord;
	pawnmove cfour;
	sf::RectangleShape squareborder;
	graphics*tpawn, *tkpawn, *tborder;

public:
	bool king = false;
	std::vector<path> path_pawn;
	sf::CircleShape &display();
	sf::RectangleShape &displayborder();

	pawns(int redorblue, int loop_id, graphics*tpawn, graphics*tkpawn, graphics*tborder);

	pawnmove &struct_id();
	void position(int id);

	void move(int movex, int movey);
	void select(int x, int y);
	void resetmove();
	void moveforward(sf::Vector2i coor);
	void transform();
	void dell();
	sf::Vector2i cord();
};