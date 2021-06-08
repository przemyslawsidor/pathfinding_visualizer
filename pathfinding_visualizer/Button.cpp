#include "Button.h"

#include <iostream>

sf::Color Button::mask_default_color = sf::Color(0, 0, 0, 0);
sf::Color Button::mask_blocked_color = sf::Color(255, 255, 255, 150);
sf::Color Button::mask_focused_color = sf::Color(150, 150, 150, 150);
sf::Color Button::color = sf::Color(70, 150, 150, 255);

Button::Button() :
	id(0),
	width(0),
	height(0),
	x(0),
	y(0),
	state(State::Default)
{}

Button::Button(int w, int h, int i, sf::String s) :
	id(i),
	width(w * 0.1),
	height(h * 0.75),
	x(width* i + ((i + 1) * 0.01 * w)),
	y(h * 0.125),
	strr(s),
	quad(sf::Quads, 4),
	mask(sf::Quads, 4),
	state(State::Default)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error" << std::endl;
	}
}

void Button::init()
{
	update();

	quad[0].position = sf::Vector2f(x, y);
	quad[1].position = sf::Vector2f(x + width, y);
	quad[2].position = sf::Vector2f(x + width, y + height);
	quad[3].position = sf::Vector2f(x, y + height);

	mask[0].position = sf::Vector2f(x, y);
	mask[1].position = sf::Vector2f(x + width, y);
	mask[2].position = sf::Vector2f(x + width, y + height);
	mask[3].position = sf::Vector2f(x, y + height);

	text = sf::Text(strr, font, height / 2);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(x + width / 2.0f, y + height / 2.0f));

	quad[0].color = color;
	quad[1].color = color;
	quad[2].color = color;
	quad[3].color = color;
}

void Button::update()
{
	switch (state)
	{
	case State::Default:
		set_mask_color(mask_default_color);
		break;
	case State::Blocked:
		set_mask_color(mask_blocked_color);
		break;
	case State::Focused:
		set_mask_color(mask_focused_color);
		break;
	}
}

int Button::getWidth()
{
	return width;
}

int Button::getHeight()
{
	return height;
}

float Button::getX()
{
	return x;
}

float Button::getY()
{
	return y;
}

void Button::set_state(State s)
{
	state = s;
}

void Button::set_mask_color(sf::Color c)
{
	mask_color = c;
	mask[0].color = mask_color;
	mask[1].color = mask_color;
	mask[2].color = mask_color;
	mask[3].color = mask_color;
}

void Button::set_focused(sf::Vector2i m)
{
	if (m.x >= x and m.x <= x + width and m.y >= y and m.y <= y + height)
	{
		state = State::Focused;
	}
	else
	{
		state = State::Default;
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(quad, states);
	target.draw(text, states);
	target.draw(mask, states);
}