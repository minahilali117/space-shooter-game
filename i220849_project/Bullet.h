#include <SFML/Graphics.hpp>
#include <string.h>
using namespace sf;

class Bullet {
public:
    Texture tex;
    Sprite sprite;
    float speed = 0.3;
    int x, y;
    bool active = false; // flag to check if the bullet is active or not
    bool hitBound= false;

    Bullet(std::string png_path) {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 340;
        y = 700;
        sprite.setPosition(x, y);
        sprite.setScale(0.5, 0.5);
    }

    void move(std::string s) {
        float delta_x = 0, delta_y = 0;
        delta_y = -1;
        delta_y *= speed;
        sprite.move(delta_x, delta_y);
    }

    bool isActive() { // function to check if the bullet is active or not
        return active;
    }

    void setActive(bool flag) { // function to set the active flag
        active = flag;
    }
    
};

class fireBeam {
public:
    Texture tex;
    Sprite sprite;
    float speed = 5;
    int x, y;

    fireBeam(std::string png_path, int x, int y) {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        sprite.setPosition(x, y);
        sprite.setScale(1, 1.5);
    }

    void move() {
        float delta_x = 0, delta_y = 0;
        delta_y = -1;
        delta_y *= speed;
        sprite.move(delta_x, delta_y);
    }

    
};
