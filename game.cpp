
#include "game.h"

const float X_coordinates[8] = {0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 600.0f, 700.0f};
const float Y_coordinates[8] = {0.0f, 100.0f, 200.f, 300.0f, 400.0f, 500.0f, 600.0f, 700.0f};


Game::Game() : window(sf::VideoMode(800, 800), "Checkers", sf::Style::Close){};

bool Game::textureinit()
{
	try
	{
		black_board_texture.init("black.png");
		white_board_texture.init("white.png");
		border.init("frame.png");
		pawn_border.init("borderr.png");
		red_texture.init("fire.png");
		blue_texture.init("blue.png");
	}
	catch (...)
	{

		return true;
	}
	return false;
}

void Game::boardinit()
{
	for (int i = 0; i < box_num; ++i)
	{

		boardwhite.push_back(checker_board(1, i, &white_board_texture, nullptr));
		boardblack.push_back(checker_board(0, i, &black_board_texture, &border));
	}
}

void Game::playerinit()
{
	P2 = player(PLAYER_TWO, &blue_texture, &blue_king_texture, &pawn_border);
	P1 = player(PLAYER_ONE, &red_texture, &red_king_texture, &pawn_border);
}
void Game::endblackrectangle()
{
	end = sf::RectangleShape(sf::Vector2f(800, 800));
	end.setFillColor(sf::Color(0, 0, 0, 70));
}

bool Game::initfont()
{
	txt.setFont(font);
	txt.setCharacterSize(40);
	txt.setFillColor(sf::Color::White);
	txt.setPosition(275.0, 375.0);
	return false;
}

bool Game::run()
{
	bool stat = false;

	window.setFramerateLimit(40);

	initfont();
	if (textureinit())
		return true;

	boardinit();
	playerinit();
	endblackrectangle();

	stat = Game::events();
	return stat;
}

void Game::draw()
{

	window.clear();

	for (auto i = 0; i < box_num; ++i)
	{
		window.draw(boardwhite[i].display());

		window.draw(boardblack[i].display());
		if (turn->return_path(boardblack[i].cord()))
			window.draw(boardblack[i].showPath());
	}

	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (nturn->pawn(i).struct_id().id != PAWN_NUMBER)
			window.draw(nturn->pawn(i).display());
	}

	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (turn->pawn(i).struct_id().id != PAWN_NUMBER)
			window.draw(turn->pawn(i).display()); 

		if (turn->legalmove_id(i))
			window.draw(turn->pawn(i).displayborder()); 
	}

	if (turn->checkfinish())
	{
		window.draw(end);

		if (turn->player_id == PLAYER_TWO)
			txt.setString("PLAYER 1 Win");

		if (turn->player_id == PLAYER_ONE)
			txt.setString("PLAYER 2 Win");

		window.draw(txt);
	}

	window.display();
}

bool Game::events()
{
	bool clicked = false;
	int indexx;
	sf::Event event;

	turn = &P1;
	nturn = &P2;
	turn->status(nturn); //check status of player pawn

	while (window.isOpen())
	{

		Game::draw();

		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			
			case sf::Event::MouseButtonPressed:

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && clicked == false)
				{
					if (turn->checkfinish())
						return false;

					for (int i = 0; i < PAWN_NUMBER; ++i)
					{

						if (turn->legalmove_id(i) && turn->pawn(i).display().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
						{
							clicked = true;
							indexx = i;
							turn->lightpath(i);		//reveal moves
							turn->pawn(i).select(event.mouseButton.x, event.mouseButton.y);
							break;
						}
					}
				}
				break;
	
			case sf::Event::MouseMoved:
				if (event.type == sf::Event::MouseMoved && clicked == true)
				{
					turn->pawn(indexx).move(event.mouseMove.x, event.mouseMove.y);
				}
				break;

			case sf::Event::MouseButtonReleased:
				if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && clicked == true)
				{
					for (int i = 0; i < box_num; ++i)
					{
						if (boardblack[i].display().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && turn->movelegal(indexx, boardblack[i].cord()))
						{
							turn->movepawn(indexx, boardblack[i].cord());
							turn->lightpath(PAWN_NUMBER);
							if (turn->multieat < 0)
								swap(); 

							turn->status(nturn);
							clicked = false;
							break;
						}
					}

					if (clicked == true) 
					{
						turn->pawn(indexx).resetmove();
						clicked = false;
					}
				}
				break;
			}
		}
		if (event.type == sf::Event::Closed)
		{
			window.close();

			return true;
		}
	}
}

void Game::swap() 
{
	player *t1;
	t1 = turn;
	turn = nturn;
	nturn = t1;
}