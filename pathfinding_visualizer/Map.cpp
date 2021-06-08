#include "Map.h"
#include "Tile.h"

#include <iostream>

Map::Map(int w) :
	width(w * 0.975),
	height(width / 2),
	x(w * 0.0125),
	y(x * 5),
	cols(64),
	rows(32),
	num_of_tiles(cols* rows),
	grid(sf::Lines, (cols + rows + 2) * 2)
{
	Tile::set_size((double)width / cols);
	tiles.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		tiles[i].resize(cols);
	}

	is_focused = false;
	generate_grid();
	generate_tiles();
	generate_adjacency();
}

void Map::generate_grid()
{
	for (int i = 0; i < cols + 1; i++)
	{
		sf::Vertex* line = &grid[i * 2];
		line[0].color = grid_color;
		line[1].color = grid_color;
		line[0].position = sf::Vector2f(x + (i * ((double)width / cols)), y);
		line[1].position = sf::Vector2f(x + (i * ((double)width / cols)), y + height);
	}

	for (int i = 0; i < rows + 1; i++)
	{
		sf::Vertex* line = &grid[(i * 2) + ((cols + 1) * 2)];
		line[0].color = grid_color;
		line[1].color = grid_color;
		line[0].position = sf::Vector2f(x, y + (i * ((double)height / rows)));
		line[1].position = sf::Vector2f(x + width, y + (i * ((double)height / rows)));
	}
}

void Map::generate_tiles()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			tiles[i][j] = Tile(x + (j * Tile::get_size()), y + (i * Tile::get_size()));
			tiles[i][j].init();
			tiles[i][j].set_id(i, j);
		}
	}

	Tile::set_source_id(14, 11);
	Tile::set_target_id(14, 52);

	tiles[Tile::source_id_i][Tile::source_id_j].set_state(Tile::State::Source);
	tiles[Tile::target_id_i][Tile::target_id_j].set_state(Tile::State::Target);
	tiles[Tile::source_id_i][Tile::source_id_j].update();
	tiles[Tile::target_id_i][Tile::target_id_j].update();
}

void Map::generate_adjacency()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i > 0)
			{
				if (tiles[i - 1][j].state != Tile::State::Wall) tiles[i][j].add_neighbor(i - 1, j);
			}
			if (j < cols - 1)
			{
				if (tiles[i][j + 1].state != Tile::State::Wall) tiles[i][j].add_neighbor(i, j + 1);
			}
			if (i < rows - 1)
			{
				if (tiles[i + 1][j].state != Tile::State::Wall) tiles[i][j].add_neighbor(i + 1, j);
			}
			if (j > 0)
			{
				if (tiles[i][j - 1].state != Tile::State::Wall) tiles[i][j].add_neighbor(i, j - 1);
			}
		}
	}
}

void Map::reset()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			tiles[i][j].set_state(Tile::State::Default);
			tiles[i][j].set_visited(false);
			tiles[i][j].set_distance(INT_MAX);
			tiles[i][j].set_previous_id(0, 0);
			tiles[i][j].update();
		}
	}

	clear_adjacency();
	generate_adjacency();

	Tile::set_source_id(14, 11);
	Tile::set_target_id(14, 52);

	tiles[Tile::source_id_i][Tile::source_id_j].set_state(Tile::State::Source);
	tiles[Tile::target_id_i][Tile::target_id_j].set_state(Tile::State::Target);
	tiles[Tile::source_id_i][Tile::source_id_j].update();
	tiles[Tile::target_id_i][Tile::target_id_j].update();
}

void Map::clear_adjacency()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			tiles[i][j].adjacent.clear();
		}
	}
}

void Map::unvisite_all()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (tiles[i][j].state == Tile::State::Wall) continue;
			tiles[i][j].set_state(Tile::State::Default);
			tiles[i][j].set_visited(false);
			tiles[i][j].set_distance(INT_MAX);
			tiles[i][j].set_previous_id(0, 0);
			tiles[i][j].update();
		}
	}

	tiles[Tile::source_id_i][Tile::source_id_j].set_state(Tile::State::Source);
	tiles[Tile::target_id_i][Tile::target_id_j].set_state(Tile::State::Target);
	tiles[Tile::source_id_i][Tile::source_id_j].update();
	tiles[Tile::target_id_i][Tile::target_id_j].update();
}

void Map::dijkstra()
{
	Tile& source = tiles[Tile::source_id_i][Tile::source_id_j];
	Tile& target = tiles[Tile::target_id_i][Tile::target_id_j];

	source.set_distance(0);

	for (int i = 0; i < num_of_tiles; i++)
	{
		Tile& u = min_dist_tile();
		if (u.get_distance() == INT_MAX) break;
		u.set_visited(true);
		if (u.state == Tile::State::Default) u.set_state(Tile::State::Scanned);
		u.update();
		if (u.id_i == target.id_i and u.id_j == target.id_j)
		{
			show_path(u, target);
			break;
		}
		else
		{
			for (int next = 0; next < u.adjacent.size(); next += 2)
			{
				int next_i = u.adjacent[next];
				int next_j = u.adjacent[next + 1];
				if (tiles[next_i][next_j].is_visited()) continue;
				int new_distance = u.get_distance() + 1;
				if (new_distance < tiles[next_i][next_j].get_distance())
				{
					tiles[next_i][next_j].set_distance(new_distance);
					tiles[next_i][next_j].set_previous_id(u.id_i, u.id_j);
				}
			}
		}
	}
}

void Map::dijkstra_anim(bool& r, bool& d)
{
	r = true;
	Tile& source = tiles[Tile::source_id_i][Tile::source_id_j];
	Tile& target = tiles[Tile::target_id_i][Tile::target_id_j];

	sf::Clock clock;
	sf::Time elapsed;
	int t = 0;

	source.set_distance(0);

	while (t < num_of_tiles)
	{
		elapsed += clock.restart();
		if (elapsed.asMilliseconds() >= 5)
		{
			Tile& u = min_dist_tile();
			if (u.get_distance() == INT_MAX) break;
			u.set_visited(true);
			if (u.state == Tile::State::Default) u.set_state(Tile::State::Scanned);
			u.update();
			if (u.id_i == target.id_i and u.id_j == target.id_j)
			{
				show_path(u, target);
				break;
			}
			else
			{
				for (int next = 0; next < u.adjacent.size(); next += 2)
				{
					int next_i = u.adjacent[next];
					int next_j = u.adjacent[next + 1];
					if (tiles[next_i][next_j].is_visited()) continue;
					int new_distance = u.get_distance() + 1;
					if (new_distance < tiles[next_i][next_j].get_distance())
					{
						tiles[next_i][next_j].set_distance(new_distance);
						tiles[next_i][next_j].set_previous_id(u.id_i, u.id_j);
					}
				}
				elapsed = clock.restart();
				t++;
			}
		}
	}
	d = true;
	r = false;
}

void Map::show_path(Tile& u, Tile& t)
{
	std::vector<int> path;
	Tile temp = u;
	for (int i = 0; i < t.get_distance() - 1; i++)
	{
		path.push_back(temp.prev_id_i);
		path.push_back(temp.prev_id_j);
		temp = tiles[temp.prev_id_i][temp.prev_id_j];
	}
	for (int j = 0; j < path.size(); j += 2)
	{
		tiles[path[j]][path[j + 1]].set_state(Tile::State::Path);
		tiles[path[j]][path[j + 1]].update();
	}
}

void Map::follow_mouse(sf::Vector2i m, bool d)
{
	Tile::set_focused_id(m, tiles);
	set_focused(m);
	if (Tile::source_catched)
	{
		if (tiles[Tile::focused_id_i][Tile::focused_id_j].state != Tile::State::Wall and
			tiles[Tile::focused_id_i][Tile::focused_id_j].state != Tile::State::Target)
		{
			tiles[Tile::source_id_i][Tile::source_id_j].set_state(Tile::State::Default);
			tiles[Tile::source_id_i][Tile::source_id_j].update();
			Tile::source_id_i = Tile::focused_id_i;
			Tile::source_id_j = Tile::focused_id_j;
			tiles[Tile::focused_id_i][Tile::focused_id_j].set_state(Tile::State::Source);
			tiles[Tile::focused_id_i][Tile::focused_id_j].update();
			if (d)
			{
				unvisite_all();
				dijkstra();
			}
		}
	}

	if (Tile::target_catched)
	{
		if (tiles[Tile::focused_id_i][Tile::focused_id_j].state != Tile::State::Wall and
			tiles[Tile::focused_id_i][Tile::focused_id_j].state != Tile::State::Source)
		{
			tiles[Tile::target_id_i][Tile::target_id_j].set_state(Tile::State::Default);
			tiles[Tile::target_id_i][Tile::target_id_j].update();
			Tile::target_id_i = Tile::focused_id_i;
			Tile::target_id_j = Tile::focused_id_j;
			tiles[Tile::focused_id_i][Tile::focused_id_j].set_state(Tile::State::Target);
			tiles[Tile::focused_id_i][Tile::focused_id_j].update();
			if (d)
			{
				unvisite_all();
				dijkstra();
			}
		}
	}

	if (Tile::wall_print)
	{
		if (tiles[Tile::focused_id_i][Tile::focused_id_j].state != Tile::State::Source and
			tiles[Tile::focused_id_i][Tile::focused_id_j].state != Tile::State::Target)
		{
			tiles[Tile::focused_id_i][Tile::focused_id_j].set_state(Tile::State::Wall);
			tiles[Tile::focused_id_i][Tile::focused_id_j].set_visited(true);
			tiles[Tile::focused_id_i][Tile::focused_id_j].update();
		}
	}
}

void Map::set_focused(sf::Vector2i m)
{
	if (m.x >= x and m.x <= x + width and m.y >= y and m.y <= y + height)
	{
		is_focused = true;
	}
	else
	{
		is_focused = false;
	}
}

Tile& Map::min_dist_tile() {
	int min = INT_MAX;
	int min_id_i = 0;
	int min_id_j = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) {
			if (!tiles[i][j].is_visited() and tiles[i][j].get_distance() < min)
			{
				min = tiles[i][j].get_distance();
				min_id_i = i;
				min_id_j = j;
			}
		}
	}
	return tiles[min_id_i][min_id_j];
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			target.draw(tiles[i][j], states);
		}
	}
	target.draw(grid, states);
}