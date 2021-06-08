#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Menu.h"
#include <iostream>
#include <thread> 

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "pathfinding_visualizer");
    window.setVerticalSyncEnabled(true);

    sf::Vector2i mouse_position;

    Map map(WINDOW_WIDTH);
    Menu menu(WINDOW_WIDTH);

    std::vector<std::thread> thread;
    bool dijkstra_running = false;
    bool dijkstra_done = false;

    while (window.isOpen())
    {
        mouse_position = sf::Mouse::getPosition(window);
        map.follow_mouse(mouse_position, dijkstra_done);
        menu.follow_mouse(mouse_position, dijkstra_running, dijkstra_done);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (!dijkstra_running)
                    {
                        if (Tile::focused_id_i == Tile::source_id_i and
                            Tile::focused_id_j == Tile::source_id_j) Tile::source_catched = true;
                        if (Tile::focused_id_i == Tile::target_id_i and
                            Tile::focused_id_j == Tile::target_id_j) Tile::target_catched = true;
                        if (!Tile::source_catched and !Tile::target_catched and map.is_focused) Tile::wall_print = true;

                        if (menu.buttons[1].state == Button::State::Focused)
                        {
                            map.reset();
                            dijkstra_done = false;
                        }
                    }
                    if (menu.buttons[0].state == Button::State::Focused)
                    {
                        if (!dijkstra_running and !dijkstra_done)
                        {
                            thread.push_back(std::thread(&Map::dijkstra_anim, std::ref(map), std::ref(dijkstra_running), std::ref(dijkstra_done)));
                        }
                    }


                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Tile::source_catched) Tile::source_catched = false;
                    if (Tile::target_catched) Tile::target_catched = false;
                    if (Tile::wall_print)
                    {
                        if (dijkstra_done)
                        {
                            map.unvisite_all();
                            map.dijkstra();
                        }
                        Tile::wall_print = false;
                        map.clear_adjacency();
                        map.generate_adjacency();
                    }
                }
            }

        }

        window.clear(sf::Color::White);
        window.draw(map);
        window.draw(menu);
        window.display();
    }

    return 0;
}