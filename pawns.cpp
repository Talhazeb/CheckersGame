
#include "pawns.h"

#include <cstdlib>

pawns::pawns(int redorblue, int loop_id, graphics*gtpawn, graphics*gtkpawn, graphics*gtborder)
{

	player_id = redorblue;
	tpawn = gtpawn;
	tkpawn = gtkpawn;
	tborder = gtborder;

	circle = (sf::CircleShape(50));

	squareborder = sf::RectangleShape(sf::Vector2f(100, 100));
	squareborder.setTexture(tborder->map());

	circle.setTexture(tpawn->map());
	position(loop_id);
}

void pawns::position(int id)
{
	int x_cord, y_cord;
	if ((id / 4) % 2 == 0)
	{
		x_cord = id % 4 * 2 + !player_id;
		y_cord = id / 4 + player_id;
		circle.setPosition(X_coordinates[x_cord], Y_coordinates[y_cord]);
		squareborder.setPosition(X_coordinates[x_cord], Y_coordinates[y_cord]);
	}
	else
	{
		x_cord = id % 4 * 2 + !!player_id;
		y_cord = id / 4 + player_id;
		circle.setPosition(X_coordinates[x_cord], Y_coordinates[y_cord]);

		squareborder.setPosition(X_coordinates[x_cord], Y_coordinates[y_cord]);
	}
	id_cord = pawnmove{id, x_cord, y_cord};
}

void pawns::select(int x, int y)
{
	lastpos = circle.getPosition();
	mouseRectOffset.x = x - circle.getGlobalBounds().left - circle.getOrigin().x;
	mouseRectOffset.y = y - circle.getGlobalBounds().top - circle.getOrigin().y;
}

void pawns::move(int movex, int movey)
{
	circle.setPosition(movex - mouseRectOffset.x, movey - mouseRectOffset.x);
	squareborder.setPosition(movex - mouseRectOffset.x, movey - mouseRectOffset.x);
}

void pawns::resetmove()
{
	circle.setPosition(lastpos);
	squareborder.setPosition(lastpos);
}

void pawns::moveforward(sf::Vector2i coor)
{

	id_cord.x = coor.x;
	id_cord.y = coor.y;
	circle.setPosition(X_coordinates[coor.x], Y_coordinates[coor.y]);
	squareborder.setPosition(X_coordinates[coor.x], Y_coordinates[coor.y]);
}

void pawns::transform()
{

	circle.setTexture(tkpawn->map());
}

void pawns::dell()
{

	id_cord = pawnmove{12, -1, -1};
	circle.setRadius(0);
	squareborder.setSize(sf::Vector2f(0, 0));
}

sf::Vector2i pawns::cord()
{
	return sf::Vector2i(id_cord.x, id_cord.y);
}

pawnmove& pawns::struct_id()
{
	return id_cord;
}

sf::CircleShape& pawns::display()
{
	return circle;
}

sf::RectangleShape& pawns::displayborder()
{
	return squareborder;
}
