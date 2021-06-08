#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

class Menu : public sf::Drawable, public sf::Transformable
{
public:
	Menu(int);
	void init_menu();
	void init_buttons();
	void init_legend();
	void follow_mouse(sf::Vector2i, bool, bool);
	std::vector<Button> buttons;
private:
	const int width, height;
	const float x, y;
	sf::VertexArray quad;
	sf::Text source_text;
	sf::Text target_text;
	sf::Text wall_text;
	sf::Text path_text;
	sf::Text scanned_text;
	const sf::Color color;
	sf::Font font;
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};