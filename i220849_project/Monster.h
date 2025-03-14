#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Monster : public Enemy {
public:
    Monster(string filenameM) : Enemy(filenameM) {
        sprite.setScale(0.15, 0.15);
        // Set the fixed vertical position of the monster
        y = 50; x=100;
        sprite.setPosition(x, y);
    }

	~Monster (){
		delete beam;
	}

    void move() override {
        if (isMovingLeft) {
            sprite.move(-speed, 0);
            if (sprite.getPosition().x <= 0) {

                isMovingLeft = false;
            }
        } else {
       // 	fireBeam();
            sprite.move(speed, 0);
            if ((sprite.getPosition().x >= 600) && (sprite.getPosition().x <= 800) ) {
                isMovingLeft = true;
            }
        }
    }
    

    void fireBeam() override//fire continuously after 2 seconds
     {
        if (beamTimer.getElapsedTime().asSeconds() >= beamInterval) {
            isFiringBeam = !isFiringBeam;
            ++beamCounter;
            beamTimer.restart();
        }
        if (isFiringBeam) {
            beam->sprite.setPosition(sprite.getPosition().x+100, sprite.getPosition().y+70);//moving the beam
        }
    }



};

