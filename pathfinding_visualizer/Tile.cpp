#include "Tile.h"

double Tile::size = 0;
int Tile::source_id_i = 0;
int Tile::source_id_j = 0;
int Tile::target_id_i = 0;
int Tile::target_id_j = 0;
int Tile::focused_id_i = 0;
int Tile::focused_id_j = 0;
bool Tile::source_catched = false;
bool Tile::target_catched = false;
bool Tile::wall_print = false;
sf::Color Tile::default_color = sf::Color(0, 0, 0, 0);
sf::Color Tile::scanned_color = sf::Color(0, 255, 0, 255);
sf::Color Tile::source_color = sf::Color(255, 255, 0, 255);
sf::Color Tile::target_color = sf::Color(255, 0, 0, 255);
sf::Color Tile::path_color = sf::Color(0, 0, 255, 255);
sf::Color Tile::wall_color = sf::Color(80, 80, 80, 255);

Tile::Tile() :
	x(0),
	y(0)
{
	visited = false;
	set_id(0, 0);
	set_state(State::Default);
}

Tile::Tile(float X, float Y) :
	x(X),
	y(Y),
	quad(sf::Quads, 4)
{
	set_id(0, 0);
	set_state(State::Default);
	visited = false;
	distance = INT_MAX;
}

void Tile::set_size(double s)
{
	size = s;
}

void Tile::set_source_id(int i, int j)
{
	source_id_i = i;
	source_id_j = j;
}

void Tile::set_target_id(int i, int j)
{
	target_id_i = i;
	target_id_j = j;
}

void Tile::set_focused_id(sf::Vector2i m, std::vector<std::vector<Tile>>& t)
{
	int rows = t.size();
	int cols = t[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (m.x >= t[i][j].x and m.x <= t[i][j].x + size and m.y >= t[i][j].y and m.y <= t[i][j].y + size)
			{
				focused_id_i = i;
				focused_id_j = j;
			}
		}
	}
}

double Tile::get_size()
{
	return size;
}

void Tile::init()
{
	quad[0].position = sf::Vector2f(x, y);
	quad[1].position = sf::Vector2f(x + size, y);
	quad[2].position = sf::Vector2f(x + size, y + size);
	quad[3].position = sf::Vector2f(x, y + size);

	set_color(default_color);
}

void Tile::update()
{
	switch (state)
	{
	case State::Default:
		set_color(default_color);
		break;
	case State::Scanned:
		set_color(scanned_color);
		break;
	case State::Source:
		set_color(source_color);
		break;
	case State::Target:
		set_color(target_color);
		break;
	case State::Path:
		set_color(path_color);
		break;
	case State::Wall:
		set_color(wall_color);
		break;
	}
}

void Tile::set_id(int i, int j)
{
	id_i = i;
	id_j = j;
}

void Tile::set_state(State s)
{
	state = s;
}

void Tile::set_previous_id(int i, int j)
{
	prev_id_i = i;
	prev_id_j = j;
}

void Tile::set_visited(bool v)
{
	visited = v;
}

void Tile::set_distance(int d)
{
	distance = d;
}

void Tile::set_color(sf::Color c)
{
	color = c;
	quad[0].color = color;
	quad[1].color = color;
	quad[2].color = color;
	quad[3].color = color;
}

void Tile::add_neighbor(int i, int j)
{
	adjacent.push_back(i);
	adjacent.push_back(j);
}


bool Tile::is_visited()
{
	return visited;
}

int Tile::get_distance()
{
	return distance;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(quad, states);
}