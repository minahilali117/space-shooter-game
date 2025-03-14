
#include <SFML/Graphics.hpp>
#include <string.h>
using namespace sf;

class AddOns {
public:
    Texture tex;
    Sprite sprite;
    float speed = 0.25;
    int x, y;
    bool active = false; // flag to check if the bullet is active or not
    bool hitBound = false;

    AddOns(std::string png_path, int x, int y) {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        sprite.setPosition(x, y);
        sprite.setScale(0.5, 0.5);
    }

    virtual void move() {
        float delta_x = 0, delta_y = 0;
        delta_y = 1;
        delta_y *= speed;
        sprite.move(delta_x, delta_y);
        // Wrap around the screen
        if (sprite.getPosition().y >= 800) {
            active = false;
        }
    }
};

class PowrUp : public AddOns {
public:
    PowrUp(std::string png_path, int x, int y) : AddOns(png_path, x, y) {}

    void move() override {
        AddOns::move(); // Call the base class's move() method
    }

    void activate() {
        // Implement power up feature
    }
};

class Danger : public AddOns {
public:
    Danger(std::string png_path, int x, int y) : AddOns(png_path, x, y) {}

    void move() override {
    	speed = 0.3;
        float delta_x = 0, delta_y = 0;
        delta_y = 1;
        delta_y *= speed;
        sprite.move(delta_x, delta_y);
        //cout<<"ran";
    }

    void activate() {
        // Implement danger feature
    }
};

class Lives : public AddOns {
public:
    Lives(std::string png_path, int x, int y) : AddOns(png_path, x, y) {}

    void move() override {
    	speed = 0.1;
        float delta_x = 0, delta_y = 0;
        delta_y = 1;
        delta_y *= speed;
        sprite.move(delta_x, delta_y);
        //cout<<"ran";
    }

    void activate() {
        // Implement lives feature
    }
};

class Fire : public AddOns {
public:
    Fire(std::string png_path, int x, int y) : AddOns(png_path, x, y) {}

    void move() override {
    	speed = 0.25;
        float delta_x = 0, delta_y = 0;
        delta_y = 1;
        delta_y *= speed;
        sprite.move(delta_x, delta_y);
        //cout<<"ran";
    }

    void activate() {
        // Implement fire feature
    }
};

