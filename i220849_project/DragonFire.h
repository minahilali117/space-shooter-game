#include <SFML/Graphics.hpp>
#include <string.h>
using namespace sf;

class DragonFire {
public:
    Texture tex;
    Sprite sprite;
    float speed = 0.5;
    int x, y;
    bool hitBound= false;

    DragonFire(std::string png_path, int x, int y) {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        sprite.setPosition(x, y);
        sprite.setScale(2, 3);
    }

    void move(float x, float y) {
    	float temp;
    	//if (x==y){ temp = y; y = x; x = y; y+=1, x+=1;}
    	//cout<<"move";
        y *= speed; x*= speed;
        sprite.move(x , y);
        
    }



    
};

