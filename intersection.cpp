#include "intersection.hpp"
namespace itrsn
{
    class Road;
}

namespace i_fun{
    int has_priority(itrsn::Road a, itrsn::Road b);
}

namespace i_random{
    int r_num(int num = 0, bool biased = false);
}



//"Intersection"
namespace itrsn
{
    float res{600.f};
    float road_thickness{170.f};
    float road_length{res/2};
    float sign_size{50};
    std::vector<sf::Texture> sign_textures;
    std::vector<float> sign_scales;
    sf::Texture texture;

            namespace color
    {
            sf::Color grass{64, 200, 0};
            sf::Color road{121, 121, 121};
    }

    sf::Texture car_texture_top;
    sf::Texture car_texture_bot;
    sf::Texture arrow;
    
    // where should the roads be drawn
    // x, y
    std::vector<std::vector<float>> road_positions
    {
        {res / 2 - road_thickness / 2, res-road_length},
        {res, res / 2 - road_thickness/2, 90},
        {res / 2 - road_thickness / 2, 0},
        {res / 2, res / 2 - road_thickness/2, 90}
    };


    // where should the car spawn when placed on a given road, and its rotation
    // x, y, rotation(optional)
    std::vector<std::vector<float>> starting_positions
    {
        {res / 2, res / 2 + road_thickness / 2},
        {res / 2 + road_thickness/2, res / 2, 270},
        {res / 2 , res / 2 - road_thickness / 2, 180},
        {res / 2 - road_thickness/2, res / 2 , 90}
    };

    namespace sign
    {
        //all "high" signs grant priority over "low" ones
        //lights take priority above all signs
        std::vector<int> high_priority_lights{4,5};
        std::vector<int> high_priority_signs{1};

        //unused for now
        //std::vector<int> low_priority_lights{6,7};
        std::vector<int> low_priority_signs{2,3}; 
        
        
    }

    


        Road::Road
        ( 
              short a_id
            , short a_vehicle_id
            , short a_sign_id  
            , short a_road_type 
        )
            : id(a_id)
            , vehicle_id(a_vehicle_id)
            , sign(a_sign_id) 
            , road_type(a_road_type) 
        {
            road_shape.setFillColor(color::road);
            road_shape.setPosition(sf::Vector2f(road_positions[a_id][0], road_positions[a_id][1]));
            if (road_positions[id].size()==3)
                road_shape.setRotation(road_positions[a_id][2]);
            if (sign==-1)//If a_sign_id is not specified, randomize it
                sign = i_random::r_num(3);
            

        };
        
    };

    void itrsn::Car::set_pos(float a, float b, float rot)
    {
        sprite_bot.setPosition(sf::Vector2f(a, b));
        sprite_top.setPosition(sf::Vector2f(a, b));
        sprite_bot.setRotation(rot);
        sprite_top.setRotation(rot);
    }
    //virtual
    void itrsn::Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite_bot);
        target.draw(sprite_top);
    }
    void itrsn::Car::set_color_RGB(int r, int g, int b)
    {
        car_color = sf::Color(r, g, b);
        sprite_bot.setColor(car_color);
    }
    void itrsn::Car::set_color(sf::Color color)
    {
        car_color = color;
        sprite_bot.setColor(car_color);
    }
    void itrsn::Car::setup_car(short road_id)
    {
        //set textures
        //TODO : Add different car textures?
        sprite_top.setTexture(itrsn::car_texture_top);
        sprite_bot.setTexture(itrsn::car_texture_bot);
        //set scale
        sprite_top.setScale(sf::Vector2f(4.f, 4.f)); 
        sprite_bot.setScale(sf::Vector2f(4.f, 4.f)); 
        //set position
        std::vector<float> positions{itrsn::starting_positions[road_id]};
        set_pos(positions[0], positions[1],positions[2]);
    }
    itrsn::Car::Car(short a_car_id, short a_road_id, int r, int g, int b) : id(a_car_id), road_id(a_road_id)
    {
    //do necessary stuff
    itrsn::Car::setup_car(road_id);

    //set color
    itrsn::Car::set_color_RGB(r, g, b);;
    }

    //Constructor for built-in colors
    itrsn::Car::Car(short a_car_id, short a_road_id, sf::Color color) : id(a_car_id), road_id(a_road_id)
    {
    //do necessary stuff
    itrsn::Car::setup_car(road_id);

    //set color
    itrsn::Car::set_color(color);
    }

    // class Car : public sf::Drawable
    // {
    // private:

    // public:

    //     short id;
    //     short road_id;
    //     sf::Sprite sprite_top;
    //     sf::Sprite sprite_bot;
    //     sf::Color car_color;

    //     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    //     {
    //         target.draw(sprite_bot);
    //         target.draw(sprite_top);
    //     }
    //     //road id - which road the car is coming from, 0-3
    //     //r,g,b   - car's color 
    //     void set_color_RGB(int r, int g, int b)
    //     {
    //         car_color = sf::Color(r, g, b);
    //         sprite_bot.setColor(car_color);
    //     }
    //     void set_color(sf::Color color)
    //     {
    //         car_color = color;
    //         sprite_bot.setColor(car_color);
    //     }

        

    //     void setup_car(short road_id)
    //     {
    //         //set textures
    //         //TODO : Add different car textures?
    //         sprite_top.setTexture(itrsn::car_texture_top);
    //         sprite_bot.setTexture(itrsn::car_texture_bot);
    //         //set scale
    //         sprite_top.setScale(sf::Vector2f(4.f, 4.f)); 
    //         sprite_bot.setScale(sf::Vector2f(4.f, 4.f)); 
    //         //set position
    //         std::vector<float> positions{itrsn::starting_positions[road_id]};
    //         set_pos(positions[0], positions[1],positions[2]);
    //     }

    //     //Constructor for RGB colors
    //     Car(short a_car_id, short a_road_id, int r, int g, int b) : id(a_car_id), road_id(a_road_id)
    //     {
    //     //do necessary stuff
    //     setup_car(road_id);

    //     //set color
    //     set_color_RGB(r, g, b);;
    //     }

    //     //Constructor for built-in colors
    //     Car(short a_car_id, short a_road_id, sf::Color color) : id(a_car_id), road_id(a_road_id)
    //     {
    //     //do necessary stuff
    //     setup_car(road_id);

    //     //set color
    //     set_color(color);
    //     }
    // };

    //Check where the car is going
    //0 - right
    //1 - forward
    //2 - left
    short itrsn::car_destination(itrsn::Road a)
    {
        itrsn::Road* target{a.destination};
        short id{a.id};
        short t_id{target->id};
        
        //Is it going right?
        if ( id == t_id-1 || (id==3 && t_id==0) )
            return 0;
        //Is it going forward?
        if ((id==0 && t_id == 2) || (id==1 && t_id == 3))
            return 1;
        //Then it's going left
        return 2; 
    }

    void itrsn::Intersection::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        
        for (Road R : roads_list)
            target.draw(R.road_shape);
        for (Car R : cars_list)
            target.draw(R);

        //std::cout << "DRAW";

        //draw roads
        target.draw(center_square);
        for (Road R : roads_list)
            target.draw(R.road_shape);
        
        sf::Sprite front_arrow_body{};
        sf::Sprite left_arrow_body{};
        sf::Sprite right_arrow_body{};
        front_arrow_body.setTexture(arrow);
        left_arrow_body.setTexture(arrow);
        right_arrow_body.setTexture(arrow);

        //draw everything else
        for (Road R : roads_list)
        {

            
            //draw a sign
            std::vector<float> s_coor{starting_positions[R.id]};                    

            sf::Sprite sign{};
            sign.setTexture(sign_textures[R.sign]);
            sign.setScale(sf::Vector2f(sign_scales[R.sign], sign_scales[R.sign]));

            sf::RectangleShape pole{sf::Vector2f(sign_size / 5, sign_size)};
            if (R.sign!=0)
                pole.setFillColor(itrsn::color::road);
            else
                pole.setFillColor(sf::Color::Transparent);
            
            //destination arrows
            front_arrow_body.setRotation(s_coor[2]+180);
            left_arrow_body.setRotation(s_coor[2]+90);
            right_arrow_body.setRotation(s_coor[2]-90);

            //set positions of signs
            switch (R.id)
            {
                case 0:
                    sign.setPosition(sf::Vector2f(s_coor[0]+road_thickness/2, s_coor[1]));
                    pole.setPosition(sf::Vector2f(s_coor[0]+road_thickness/2+sign_size/2.5, s_coor[1]+sign_size*0.8));
                    front_arrow_body.setPosition(sf::Vector2f(s_coor[0]+sign_size/1.5, s_coor[1]));
                    right_arrow_body.setPosition(sf::Vector2f(s_coor[0]+sign_size/2, s_coor[1]-road_thickness/11));
                    left_arrow_body.setPosition(sf::Vector2f(s_coor[0]+sign_size/2, s_coor[1]-road_thickness*0.8));
                    break;
                case 1:
                    sign.setPosition(sf::Vector2f(s_coor[0], s_coor[1]-road_thickness/2));
                    pole.setPosition(sf::Vector2f(s_coor[0]+sign_size*0.8, s_coor[1]-road_thickness/2-sign_size/2.5));
                    front_arrow_body.setPosition(sf::Vector2f(s_coor[0], s_coor[1]-sign_size/1.5));
                    right_arrow_body.setPosition(sf::Vector2f(s_coor[0]-road_thickness/11, s_coor[1]-sign_size/2));
                    left_arrow_body.setPosition(sf::Vector2f(s_coor[0]-road_thickness*0.8, s_coor[1]-sign_size/2));
                    break;
                case 2:
                    sign.setPosition(sf::Vector2f(s_coor[0]-road_thickness/2, s_coor[1]));
                    pole.setPosition(sf::Vector2f(s_coor[0]-road_thickness/2-sign_size/2.5, s_coor[1]-sign_size*0.8));
                    front_arrow_body.setPosition(sf::Vector2f(s_coor[0]-sign_size/1.5, s_coor[1]));
                    right_arrow_body.setPosition(sf::Vector2f(s_coor[0]-sign_size/2, s_coor[1]+road_thickness/11));
                    left_arrow_body.setPosition(sf::Vector2f(s_coor[0]-sign_size/2, s_coor[1]+road_thickness*0.8));
                    break;
                case 3:
                    sign.setPosition(sf::Vector2f(s_coor[0], s_coor[1]+road_thickness/2));
                    pole.setPosition(sf::Vector2f(s_coor[0]-sign_size*0.8, s_coor[1]+road_thickness/2+sign_size/2.5));
                    front_arrow_body.setPosition(sf::Vector2f(s_coor[0], s_coor[1]+sign_size/1.5));
                    right_arrow_body.setPosition(sf::Vector2f(s_coor[0]+road_thickness/11, s_coor[1]+sign_size/2));
                    left_arrow_body.setPosition(sf::Vector2f(s_coor[0]+road_thickness*0.8, s_coor[1]+sign_size/2));

                    break;
            }
            sign.setRotation(s_coor[2]);
            pole.setRotation(s_coor[2]);

            target.draw(pole);
            target.draw(sign);

            if (R.vehicle_id>0)
            {
                short destination{car_destination(R)};
                //std::cout << R.vehicle_id << " " << destination << "\n";
                if (destination == 0)
                {
                    //right_arrow_body.setColor(sf::Color::Magenta);
                    right_arrow_body.setColor(cars_list[R.vehicle_id].car_color);
                    target.draw(right_arrow_body);
                }
                else if (destination==1)
                {
                    front_arrow_body.setColor(cars_list[R.vehicle_id].car_color);
                    target.draw(front_arrow_body);
                }
                else
                {
                    left_arrow_body.setColor(cars_list[R.vehicle_id].car_color);
                    target.draw(left_arrow_body);
                }
            }

        }
    //draw cars
    for (Car C : cars_list)
        target.draw(C);
    }

    itrsn::Intersection::Intersection(short num_of_roads,bool keep_signs)
    {
        
        center_square.setFillColor(itrsn::color::road);
        center_square.setPosition(sf::Vector2f(itrsn::res / 2 - itrsn::road_thickness/2, itrsn::res / 2 - itrsn::road_thickness/2));

        for (short i{0}; i < num_of_roads; i++)
            roads_list.push_back(itrsn::Road{i, false});
    };
    //itrsn::Intersection::~Intersection(){};

    //check if the player colides with anyone's path
    //for each collision, check who has priority
    //return false if player tries to enforce priority, return true otherwise.
    bool itrsn::handle_input(short input, itrsn::Intersection& itr)
    {
        //std::cout << input << "\n";
        if (input == 1)
        {
            //check if opposing vehicle can collide
            if (itr.roads_list[2].vehicle_id!=-1)
            {
                if (itr.roads_list[2].destination->id==1)
                    if (!i_fun::has_priority(itr.roads_list[input], itr.roads_list[2]))
                        return false;
                        }
            //check if left vehicle can collide
            if (itr.roads_list[3].vehicle_id!=-1)
            {
                if (itr.roads_list[3].destination->id==1 
                    ||
                    itr.roads_list[3].destination->id==2 
                    )
                    if (!i_fun::has_priority(itr.roads_list[input], itr.roads_list[3]))
                        return false;
            }
        }
        else if (input==2)
        {
            if (itr.roads_list[1].vehicle_id!=-1)
                if (!i_fun::has_priority(itr.roads_list[input], itr.roads_list[1]))
                    return false;

            if (itr.roads_list[3].vehicle_id!=-1)        
                if (itr.roads_list[3].destination->id==0)
                    if (!i_fun::has_priority(itr.roads_list[input], itr.roads_list[3]))
                        return false;
        }
        else
        {
            if (itr.roads_list[1].vehicle_id!=-1)
                if (!i_fun::has_priority(itr.roads_list[input], itr.roads_list[1]))
                    return false;
            if (itr.roads_list[2].vehicle_id!=-1)
                if (!i_fun::has_priority(itr.roads_list[input], itr.roads_list[2]))
                    return false;
        }
        return true;
    }

    itrsn::Intersection itrsn::generate_situation(short roads, sf::Color player_color)
    {   
        //generate an intersaction
        itrsn::Intersection itr{roads};

        //add cars

        itr.cars_list.push_back(itrsn::Car{0, 0, player_color});
        itr.roads_list[0].vehicle_id = 0;
        for (short i{1}; i < roads;i++)
        {
            //generate a car
            if (i_random::r_num(4))//high chance to populate the road with a car
            {    
                itr.cars_list.push_back(itrsn::Car{i, i, i_random::r_num(255), i_random::r_num(255), i_random::r_num(255)});
                itr.roads_list[i].vehicle_id = i;
            }

            //TODO : add "zig-zag" priority

            //Make sure that both roads have different sign
            while ((itr.roads_list[0].sign == itr.roads_list[1].sign)
                || (itr.roads_list[0].sign==2 && itr.roads_list[1].sign==3)
                || (itr.roads_list[0].sign==3 && itr.roads_list[1].sign==2))
            {
                itr.roads_list[0].sign = i_random::r_num(3);
                itr.roads_list[1].sign = i_random::r_num(3);
            }

        // copy signs of opposing roads
        if (i==2 || i==3)
            itr.roads_list[i].sign = itr.roads_list[i - 2].sign;
        
        }

        //add destinations to all non-playable cars
        for (short i{1}; i < roads;i++)
        {
            if (itr.roads_list[i].vehicle_id > 0)
                itr.roads_list[i].destination = &itr.roads_list[i_random::r_num(roads)];
                
        }
        return itr;
    }

void regenerate(itrsn::Intersection& itr)
{
    for (short i{1}; i < itr.roads_list.size();i++)
    {
        //generate a car
        
        itr.cars_list[i]= itrsn::Car{i, i, i_random::r_num(255), i_random::r_num(255), i_random::r_num(255)};

        int des{i_random::r_num(i_random::r_num(3))};
        while (des==i)
            des = i_random::r_num(i_random::r_num(3));
        
        itr.roads_list[i].destination = &itr.roads_list[des];
        
    }
}

