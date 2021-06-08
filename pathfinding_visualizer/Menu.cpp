#include "Menu.h"
#include "Button.h"
#include "Tile.h"

#include <iostream>

Menu::Menu(int w) :
	width(w),
	height(w * 0.05),
	x(0),
	y(0),
	color(sf::Color(70, 200, 200, 255)),
	quad(sf::Quads, 24)
{
	buttons.resize(2);
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error" << std::endl;
	}
	init_menu();
	init_buttons();
	init_legend();
}

void Menu::init_menu()
{
	quad[0].position = sf::Vector2f(x, y);
	quad[1].position = sf::Vector2f(x + width, y);
	quad[2].position = sf::Vector2f(x + width, y + height);
	quad[3].position = sf::Vector2f(x, y + height);

	quad[0].color = color;
	quad[1].color = color;
	quad[2].color = color;
	quad[3].color = color;
}

void Menu::init_buttons()
{
	buttons[0] = Button(width, height, 0, "Run");
	buttons[0].init();

	buttons[1] = Button(width, height, 1, "Reset");
	buttons[1].init();
}

void Menu::init_legend()
{
	int legend_x = buttons[buttons.size() - 1].getX() + buttons[buttons.size() - 1].getWidth() + 0.01 * width;
	int top_tile_legend_y = buttons[buttons.size() - 1].getY();
	int bot_tile_legend_y = buttons[buttons.size() - 1].getY() + buttons[buttons.size() - 1].getHeight() - Tile::get_size();
	quad[4].position = sf::Vector2f(legend_x, top_tile_legend_y);
	quad[5].position = sf::Vector2f(legend_x + Tile::get_size(), top_tile_legend_y);
	quad[6].position = sf::Vector2f(legend_x + Tile::get_size(), top_tile_legend_y + Tile::get_size());
	quad[7].position = sf::Vector2f(legend_x, top_tile_legend_y + Tile::get_size());

	quad[4].color = Tile::source_color;
	quad[5].color = Tile::source_color;
	quad[6].color = Tile::source_color;
	quad[7].color = Tile::source_color;

	source_text = sf::Text(" source ", font, Tile::get_size());
	source_text.setPosition(legend_x + Tile::get_size(), top_tile_legend_y - Tile::get_size() / 5);

	quad[8].position = sf::Vector2f(legend_x, bot_tile_legend_y);
	quad[9].position = sf::Vector2f(legend_x + Tile::get_size(), bot_tile_legend_y);
	quad[10].position = sf::Vector2f(legend_x + Tile::get_size(), bot_tile_legend_y + Tile::get_size());
	quad[11].position = sf::Vector2f(legend_x, bot_tile_legend_y + Tile::get_size());

	quad[8].color = Tile::target_color;
	quad[9].color = Tile::target_color;
	quad[10].color = Tile::target_color;
	quad[11].color = Tile::target_color;

	target_text = sf::Text(" target", font, Tile::get_size());
	target_text.setPosition(legend_x + Tile::get_size(), bot_tile_legend_y - Tile::get_size() / 6);

	quad[12].position = sf::Vector2f(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width, top_tile_legend_y);
	quad[13].position = sf::Vector2f(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width + Tile::get_size(), top_tile_legend_y);
	quad[14].position = sf::Vector2f(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width + Tile::get_size(), top_tile_legend_y + Tile::get_size());
	quad[15].position = sf::Vector2f(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width, top_tile_legend_y + Tile::get_size());

	quad[12].color = Tile::wall_color;
	quad[13].color = Tile::wall_color;
	quad[14].color = Tile::wall_color;
	quad[15].color = Tile::wall_color;

	wall_text = sf::Text(" wall", font, Tile::get_size());
	wall_text.setPosition(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width + Tile::get_size(), top_tile_legend_y - Tile::get_size() / 6);

	quad[16].position = sf::Vector2f(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width, bot_tile_legend_y);
	quad[17].position = sf::Vector2f(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width + Tile::get_size(), bot_tile_legend_y);
	quad[18].position = sf::Vector2f(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width + Tile::get_size(), bot_tile_legend_y + Tile::get_size());
	quad[19].position = sf::Vector2f(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width, bot_tile_legend_y + Tile::get_size());

	quad[16].color = Tile::path_color;
	quad[17].color = Tile::path_color;
	quad[18].color = Tile::path_color;
	quad[19].color = Tile::path_color;

	path_text = sf::Text(" path ", font, Tile::get_size());
	path_text.setPosition(source_text.getGlobalBounds().left + source_text.getGlobalBounds().width + Tile::get_size(), bot_tile_legend_y - Tile::get_size() / 6);

	quad[20].position = sf::Vector2f(path_text.getGlobalBounds().left + path_text.getGlobalBounds().width, top_tile_legend_y);
	quad[21].position = sf::Vector2f(path_text.getGlobalBounds().left + path_text.getGlobalBounds().width + Tile::get_size(), top_tile_legend_y);
	quad[22].position = sf::Vector2f(path_text.getGlobalBounds().left + path_text.getGlobalBounds().width + Tile::get_size(), top_tile_legend_y + Tile::get_size());
	quad[23].position = sf::Vector2f(path_text.getGlobalBounds().left + path_text.getGlobalBounds().width, top_tile_legend_y + Tile::get_size());

	quad[20].color = Tile::scanned_color;
	quad[21].color = Tile::scanned_color;
	quad[22].color = Tile::scanned_color;
	quad[23].color = Tile::scanned_color;

	scanned_text = sf::Text(" scanned", font, Tile::get_size());
	scanned_text.setPosition(path_text.getGlobalBounds().left + path_text.getGlobalBounds().width + Tile::get_size(), top_tile_legend_y - Tile::get_size() / 6);
}

void Menu::follow_mouse(sf::Vector2i m, bool r, bool d)
{
	if (!r)
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].set_focused(m);
			buttons[i].update();
		}
	}
	else
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].set_state(Button::State::Blocked);
			buttons[i].update();
		}
	}
	if (d)
	{
		buttons[0].set_state(Button::State::Blocked);
		buttons[0].update();
	}
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(quad, states);
	target.draw(source_text, states);
	target.draw(target_text, states);
	target.draw(wall_text, states);
	target.draw(path_text, states);
	target.draw(scanned_text, states);
	for (int i = 0; i < buttons.size(); i++)
	{
		target.draw(buttons[i], states);
	}
}