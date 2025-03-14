#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Dragon : public Enemy {
public:

	 Clock dTimer;
    float dInterval;
    int dCounter;
    bool dscore;

    Dragon(string filenameD) : Enemy(filenameD) {
        sprite.setScale(2.2, 2);
        // Set the fixed  position of the dragon
        y = 10; x=150; //90, 220
        sprite.setPosition(x, y);
        dInterval=5.0;
        dCounter=0;
        dscore=true;
        dTimer.restart();
    }

	void destroyDrag()
	{
		if (dTimer.getElapsedTime().asSeconds() >= dInterval){
			sprite.setPosition(1000, 1000);
			dTimer.restart();
		}
	}

	~Dragon (){
	}

    
    



};

