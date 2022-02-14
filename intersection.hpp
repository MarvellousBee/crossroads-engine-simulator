#pragma once
#include <SFML/Graphics.hpp>

//"Intersection"
namespace itrsn
{
    extern float res;
    extern float road_thickness;
    extern float road_length;
    extern float sign_size;
    extern std::vector<sf::Texture> sign_textures;
    extern std::vector<float> sign_scales;
    extern sf::Texture texture;

    namespace color
    {
        extern sf::Color grass;
        extern sf::Color road;
    }

    extern sf::Texture car_texture_top;
    extern sf::Texture car_texture_bot;
    extern sf::Texture arrow;
    
    // where should the roads be drawn
    // x, y
    extern std::vector<std::vector<float>> road_positions;

    // where should the car spawn when placed on a given road, and its rotation
    // x, y, rotation(optional)
    extern std::vector<std::vector<float>> starting_positions;

    namespace sign
    {
        //all "high" signs grant priority over "low" ones
        //lights take priority above all signs
        extern std::vector<int> high_priority_lights;
        extern std::vector<int> high_priority_signs;

        //unused for now
        //std::vector<int> low_priority_lights{6,7};
        extern std::vector<int> low_priority_signs; 
    }

    class Road
    {      
    public:

        short id{};

        //Possible vehicle codes:
        // -1  - no car
        // 0<= - car id
        short vehicle_id{};

        //Where the vehicle intends to go
        //May be left empty if vehicle==0.
        Road* destination;

        //Possible sign codes
        // TODO: add official sign codes next to descriptions and MORE SIGNS
        // 0 - No sign
        // 1 - You have priority
        // 2 - Everyone else has priority
        // 3 - STOP
        // 4 - light - green
        // 5 - light - yellow
        // 6 - light - red
        // 7 - light - red+yellow
        // 8 - light - inactive
        short sign;

        //Road type
        // 0 - equal priority
        // 1 - You have priority
        // 2 - You do not have priority
        short road_type;
        sf::RectangleShape road_shape{sf::Vector2f(road_thickness, road_length)};

        Road(short a_id, short a_vehicle_id = -1, short a_sign_id = -1, short a_road_type = 0);
    };

    class Car : public sf::Drawable
    {
    private:
    
        void set_pos(float a, float b, float rot = 0);

    public:

        short id;
        short road_id;
        sf::Sprite sprite_top;
        sf::Sprite sprite_bot;
        sf::Color car_color;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        // road id - which road the car is coming from, 0-3
        // r,g,b   - car's color
        void set_color_RGB(int r, int g, int b);
        void set_color(sf::Color color);

        void setup_car(short road_id);

        //Constructor for RGB colors
        Car(short a_car_id = 0, short a_road_id = 0, int r = 0, int g = 0, int b = 0);

        //Constructor for built-in colors
        Car(short a_car_id = 0, short a_road_id = 0, sf::Color color = {0, 0, 0});
    };

    //Check where the car is going
    //0 - right
    //1 - forward
    //2 - left
    short car_destination(itrsn::Road a);

    class Intersection : public sf::Drawable
    {
        public:

            std::vector<Road> roads_list;
            std::vector<Car> cars_list;
            sf::RectangleShape center_square;

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

            Intersection(short num_of_roads = 4, bool keep_signs = false);
            //virtual ~Intersection();
    };
    //check if the player colides with anyone's path
    //for each collision, check who has priority
    //return false if player tries to enforce priority, return true otherwise.
    bool handle_input(short input, Intersection &itr);

    Intersection generate_situation(short roads = 4, sf::Color player_color = sf::Color::Red);

    void regenerate(Intersection &itr);
}