#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>

#include <cctype>
#include <random>

#include "intersection.hpp"
#include "intersection_random.hpp"
#include "intersection_functions.hpp"


int main()
{
    int score{0};

    //load car textures
    if (!itrsn::car_texture_top.loadFromFile("media/car_top.png"))
        {std::cout << "failed while loading media files";
            return -1;
        }
    if (!itrsn::car_texture_bot.loadFromFile("media/car_bottom.png"))
        {std::cout << "failed while loading media files";
            return -1;
        }

    //load arrow texture
    if (!itrsn::arrow.loadFromFile("media/arrow.png"))
        {std::cout << "failed while loading media files";
            return -1;
        }

    //load sign textures
    
    if (!itrsn::texture.loadFromFile("media/EMPTY.png"))
        {std::cout << "failed while loading media files";
            return -1;
        }
    itrsn::sign_textures.push_back(itrsn::texture);
    itrsn::sign_scales.push_back(0.0f);

    if (!itrsn::texture.loadFromFile("media/PRIO.png"))
        {std::cout << "failed while loading media files";
            return -1;
        }
    itrsn::sign_textures.push_back(itrsn::texture);
    itrsn::sign_scales.push_back(.17f);

    if (!itrsn::texture.loadFromFile("media/NO_PRIO.png"))
        {std::cout << "failed while loading media files";
            return -1;
        }
    itrsn::sign_textures.push_back(itrsn::texture);
    itrsn::sign_scales.push_back(.05f);

    if (!itrsn::texture.loadFromFile("media/STOP.png"))
        {std::cout << "failed while loading media files";
            return -1;
        }
    itrsn::sign_textures.push_back(itrsn::texture);
    itrsn::sign_scales.push_back(.165f);

    //font
    sf::Font font;
    if (!font.loadFromFile("media/arial.ttf"))
        {std::cout << "failed while loading media files";
            return -1;
        }
    sf::Text text;
    // select the font
    text.setFont(font); 
    text.setString("Score: 0");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::RenderWindow window(sf::VideoMode(itrsn::res, itrsn::res), "crossroads");


    //intersection
    itrsn::Intersection itr = itrsn::generate_situation();
    // std::cout << i_fun::has_priority(itr.roads_list[0], itr.roads_list[3]);
    //signs

    //main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                // key pressed
                case sf::Event::KeyPressed:
                    if      (event.key.code == sf::Keyboard::Right)
                    {
                        if (itrsn::handle_input(1, itr))
                        {
                            score++;
                        }
                        else
                        {
                            //PRINT you lost, final score
                            score = 0;
                            
                        }
                        text.setString("Score: "+std::to_string(score));
                        itr = itrsn::generate_situation();
                        break;
                    }
                    else if (event.key.code == sf::Keyboard::Up)
                    {
                        if (itrsn::handle_input(2, itr))
                        {
                            score++;
                        }
                        else
                        {
                            //PRINT you lost, final score
                            score = 0;
                            
                        }
                        text.setString("Score: "+std::to_string(score));
                        itr = itrsn::generate_situation();
                        break;
                    }
                    else if (event.key.code == sf::Keyboard::Left)
                    {
                        if (itrsn::handle_input(3, itr))
                        {
                            score++;
                        }
                        else
                        {
                            //PRINT you lost, final score
                            score = 0;
                            
                        }
                        text.setString("Score: "+std::to_string(score));
                        itr = itrsn::generate_situation();
                        break;
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        itr = itrsn::generate_situation();

                        break;
                    }
                        
                default:
                    break;
            }
        }
        //draw constant stuff
        window.clear(itrsn::color::grass);
        //draw text
        window.draw(text);
        //draw the intersection
        window.draw(itr);

        window.display();
    }
}