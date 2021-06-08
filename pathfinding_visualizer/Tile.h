#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable, public sf::Transformable
{
public:
	Tile();
	Tile(float, float);
	static void set_size(double);
	static void set_source_id(int, int);
	static void set_target_id(int, int);
	static void set_focused_id(sf::Vector2i, std::vector<std::vector<Tile>>&);
	static double get_size();
	static int source_id_i, source_id_j;
	static int target_id_i, target_id_j;
	static int focused_id_i, focused_id_j;
	static bool source_catched;
	static bool target_catched;
	static bool wall_print;
	static sf::Color default_color;
	static sf::Color scanned_color;
	static sf::Color source_color;
	static sf::Color target_color;
	static sf::Color path_color;
	static sf::Color wall_color;
	static enum class State {
		Default,
		Scanned,
		Source,
		Target,
		Path,
		Wall
	};
	State state;
	void init();
	void update();
	void set_id(int, int);
	void set_state(State);
	void set_previous_id(int, int);
	void set_visited(bool);
	void set_distance(int);
	void set_color(sf::Color);
	void add_neighbor(int, int);
	bool is_visited();
	int get_distance();
	int id_i, id_j;
	int prev_id_i, prev_id_j;
	std::vector<int> adjacent;
private:
	float x, y;
	bool visited;
	int distance;
	static double size;
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	sf::Color color;
	sf::VertexArray quad;
};