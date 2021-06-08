#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable, public sf::Transformable
{
public:
	Button();
	Button(int, int, int, sf::String);
	static sf::Color mask_default_color;
	static sf::Color mask_blocked_color;
	static sf::Color mask_focused_color;
	static sf::Color color;
	static enum class State {
		Default,
		Blocked,
		Focused
	};
	State state;
	void init();
	void update();
	int getWidth();
	int getHeight();
	float getX();
	float getY();
	void set_state(State);
	void set_mask_color(sf::Color);
	void set_focused(sf::Vector2i);
private:
	int id;
	int width, height;
	float x, y;
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	sf::VertexArray quad;
	sf::VertexArray mask;
	sf::Color mask_color;
	sf::String strr;
	sf::Text text;
	sf::Font font;
};