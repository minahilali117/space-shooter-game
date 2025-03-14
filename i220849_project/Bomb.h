#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

class Bomb {
public:
    Sprite sprite;
    Texture texture;
    float speed;
    bool collided;
    int x, y;
    bool isActive; // add isActive data member

    Bomb(string filename, int x, int y) {
        texture.loadFromFile(filename);
        sprite.setTexture(texture);
        sprite.setScale(0.5, 0.5);
        sprite.setPosition(x, y);
        speed = 0.4;
        collided = false;
        isActive = true; // set isActive to true by default
    }

    void move(std::string s) {
        float delta_x = 0, delta_y = 0;
        delta_y = +1;
        delta_y *= speed;
        sprite.move(delta_x, delta_y);
    }


    
    

};

