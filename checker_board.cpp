#include "checker_board.h"

checker_board::checker_board(int clr, int id_loop, graphics*tboard, graphics*tborder) : col(clr)
{

	box = sf::RectangleShape(sf::Vector2f(100, 100)); 
	id = id_loop;										
	box.setTexture(tboard->map());

	if (col == 0) // if board black
	{
		box_path = sf::RectangleShape(sf::Vector2f(100, 100));
		box_path.setTexture(tborder->map());
	}
	position();
}

void checker_board::position()
{

	if ((id / 4) % 2 == 0)
	{
		x_cord = id % 4 * 2 + !col; 
		y_cord = id / 4;
		box.setPosition(X_coordinates[x_cord], Y_coordinates[y_cord]);
	}
	else
	{
		x_cord = id % 4 * 2 + col;
		y_cord = id / 4;
		box.setPosition(X_coordinates[x_cord], Y_coordinates[y_cord]);
	}
	if (col == 0)
		box_path.setPosition(X_coordinates[x_cord], Y_coordinates[y_cord]);
}

sf::Vector2i checker_board::cord()
{
	return sf::Vector2i(x_cord, y_cord);
}

sf::RectangleShape& checker_board::display()
{
	return box;
}

sf::RectangleShape& checker_board::showPath()
{
	return box_path;
}