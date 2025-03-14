#include <SFML/Graphics.hpp>
#include <string.h>
using namespace sf;

class Beam {
public:
    Texture tex;
    Sprite sprite;
    float speed = 5;
    int x, y;
    bool active = false; // flag to check if the bullet is active or not
    bool hitBound= false;

    Beam(std::string png_path) {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 50;
        y = 200;
        sprite.setPosition(x, y);
        sprite.setScale(4, 7);
    }

    void move() {
        float delta_x = 0, delta_y = 0;
        delta_y = 1;
        delta_y *= speed;
        sprite.move(delta_x, delta_y);
    }

    
};


