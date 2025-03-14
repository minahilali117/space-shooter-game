#include <SFML/Graphics.hpp>
#include<string.h>
#include "Bullet.h"
#include "AddOns.h"
using namespace sf;
class Player{
public:
Texture tex;
Sprite sprite;
float speed=0.2;
int x,y; int fix, fiy;
Bullet* b;
AddOns* liv;
AddOns* dan;
AddOns* pfire;
fireBeam* bfire;
bool isRotated=false;
int lives;
int score;
int xl;
Clock fTimer;
float fInterval;
int fCounter; 
bool firing; bool timetofire;
Player(std::string png_path)
{
srand(time(NULL));
xl = rand() % 761 + 10; // 761 = 770 - 10 + 1
b = new Bullet("img/laserBlue01.png");
liv =new Lives("img/heart.png", xl , 10);
dan = new Danger ("img/fire2.png", (rand() % 761 + 10), 5 );
pfire = new Fire ("img/fire.png", (rand() % 761 + 10), 3 );
bfire = new fireBeam ("img/fire.png", 0, 700);

tex.loadFromFile(png_path);
sprite.setTexture(tex);
x=340;y=700; fix=0, fiy=0;
sprite.setPosition(x,y);
sprite.setScale(0.75,0.75);
isRotated=false;
lives=3;
score=0;
fInterval=5;
fCounter=0;
firing = false; timetofire=false;
fTimer.restart();

}
/*
~Player(){
	//delete b;
	//delete liv;
}
*/
//wrap around
void wrapAround()
{
if (sprite.getPosition().x<= 0)
	sprite.setPosition(770, sprite.getPosition().y);
	//sprite.setPosition(0, 0);
if (sprite.getPosition().x>= 780)
	sprite.setPosition(0, sprite.getPosition().y);
if (sprite.getPosition().y<= 0)
	sprite.setPosition(sprite.getPosition().x, 770); 
if (sprite.getPosition().y>= 780)
	sprite.setPosition(sprite.getPosition().x, 0);
}

// Fire a bullet
void fire(Bullet& bullet) 
{
    if (!bullet.active) // Check if there is an active bullet already
    {
        bullet.sprite.setPosition(sprite.getPosition().x , sprite.getPosition().y );
        bullet.setActive(true); // Set the active flag to true
    }
    bullet.setActive(false);
}

//detect when to respawn a new bullet
bool hitBoundary(Bullet & bullet)
{
	if (!bullet.hitBound){
    if (sprite.getPosition().y<= 0){
   // cout<<"p";
   		bullet.hitBound=true;
		bullet.sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	}
	bullet.hitBound=false;
	}
	return bullet.hitBound;
}


//move the player spaceship
void move(std::string s){
float delta_x=0,delta_y=0;
if(s=="l")
	//move the player left
	delta_x=-1;
else if(s=="r")
	//move the player right
	delta_x=1;
if(s=="u")
	delta_y=-1;
else if(s=="d")
	delta_y=1;

delta_x*=speed;
delta_y*=speed;

sprite.move(delta_x, delta_y);

// Reset rotation if both up and right buttons are released
if (s != "r" && s != "u") {
    rotate("", true);
}

if (s != "l" && s != "u") {
    rotate("", true);
}

}


void powerUp() {

}

bool catchFire() {
	bool bog=false;
	pfire->move();
	if ((pfire->sprite.getPosition().x)>=(sprite.getPosition().x-10) && ((pfire->sprite.getPosition().x)<=(sprite.getPosition().x)+90) &&
		 ((pfire->sprite.getPosition().y)>=(sprite.getPosition().y)-10) && ((pfire->sprite.getPosition().y)<=(sprite.getPosition().y)) ){//fire hit player
		timetofire=true;
		 pfire->sprite.setPosition(rand() % 761 + 10, 3);
		 bog= true;// player caught the addon
		 
	}
		 
	else if (pfire->sprite.getPosition().y>=780){pfire->sprite.setPosition((rand() % 761 + 10), 3); }
	return timetofire;
}

void firep()
{
    if (fTimer.getElapsedTime().asSeconds() >= fInterval && timetofire) {
        firing = true;
        fCounter++;
        fTimer.restart();
        timetofire = false; // Stop firing until the next fire addon is caught
    }

    if (firing && fTimer.getElapsedTime().asSeconds() < 5) {
       bfire->move();
    }
    else {
        firing = false; // Stop firing after 5 seconds
        bfire->sprite.setPosition(1000,1000);
    }
}



void dodgeDanger() {

	dan->move();
	bool acq=false;
	if ((dan->sprite.getPosition().x)>=(sprite.getPosition().x-10) && ((dan->sprite.getPosition().x)<=(sprite.getPosition().x)+90) &&
		 ((dan->sprite.getPosition().y)>=(sprite.getPosition().y)-10) && ((dan->sprite.getPosition().y)<=(sprite.getPosition().y)) ){
		lives--;
		acq=true;
		dan->sprite.setPosition((rand() % 761 + 10), 5);
	}
	
	else if (dan->sprite.getPosition().y>=780){dan->sprite.setPosition((rand() % 761 + 10), 5); if(acq==false){score+=5;}}

}

void incrementLives() {
	liv->move();
	if ((liv->sprite.getPosition().x)>=(sprite.getPosition().x-10) && ((liv->sprite.getPosition().x)<=(sprite.getPosition().x)+90) &&
		 ((liv->sprite.getPosition().y)>=(sprite.getPosition().y)-10) && ((liv->sprite.getPosition().y)<=(sprite.getPosition().y)) ){
		lives++;
		liv->sprite.setPosition(1000, 1000);
	}
	
	else if (liv->sprite.getPosition().y>=780){liv->sprite.setPosition((rand() % 761 + 10), 10);}
}

void destroyPlayer() {
	if(lives<=0);//destroy player
	
}


void rotate(std::string dir, bool reset_rotation = false) {
	float angle = sprite.getRotation();
	if (dir == "l") {
		angle = -5;
    }
    else if (dir == "r") {
    	angle = 5;
    }
    sprite.setRotation(angle);
    if (reset_rotation) {
		sprite.setRotation(0);
    }
}

    void hitTarget() {//enemy hit, reset bullet
		b->sprite.setPosition(sprite.getPosition().x+40, sprite.getPosition().y);
    }


};
