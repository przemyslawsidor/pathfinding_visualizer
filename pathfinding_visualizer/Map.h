#pragma once

#include <SFML/Graphics.hpp>
#include <thread> 
#include "Tile.h"

class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map(int);
	void generate_grid();
	void generate_tiles();
	void generate_adjacency();
	void reset();
	void clear_adjacency();
	void unvisite_all();
	void dijkstra();
	void dijkstra_anim(bool&, bool&);
	void show_path(Tile&, Tile&);
	void follow_mouse(sf::Vector2i, bool);
	void set_focused(sf::Vector2i);
	Tile& min_dist_tile();
	std::vector<std::vector<Tile>> tiles;
	bool is_focused;
private:
	const int width, height;
	const float x, y;
	const int cols, rows;
	const int num_of_tiles;
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	sf::VertexArray grid;
	sf::Color grid_color = sf::Color(120, 120, 120, 255);
};