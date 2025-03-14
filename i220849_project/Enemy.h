#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Bomb.h"
#include "Beam.h"
#include "DragonFire.h"
using namespace std;
using namespace sf;

class Enemy
{
public:
    Sprite sprite; // Enemy sprite
    Texture texture; // Texture of the enemy sprite
    int lives; // Number of lives the enemy has
    int points; // Number of points awarded for destroying the enemy
    float speed; // Enemy's movement speed
    bool isMovingLeft; // Flag indicating if the enemy is moving left
    bool collided1;
    bool collided2; bool collided3;
    int x, y;
    Bomb* bombs;
    Clock bombTimer;
    int bombCounter, dragcount;
    float bombInterval; // Time interval between each bomb spawn
    Clock beamTimer;
    float beamInterval;
    int beamCounter;
    bool isFiringBeam;
    bool mscore;
    Beam* beam;
    DragonFire* dfire1; DragonFire* dfire2; DragonFire* dfire3;
    
    // Add any other necessary attributes and methods

    Enemy(string filename)
    {
    	bombs = new Bomb("img/laserRed08.png", 1000 , 1000);
    	beam = new Beam("img/laserRed04.png");
    	dfire1 = new DragonFire("img/enemy_laser.png", 1000, 1000);//380, 350
    	dfire2 = new DragonFire("img/enemy_laser.png", 1000, 1000);
    	dfire3 = new DragonFire("img/enemy_laser.png", 1000, 1000);//220, 250
        texture.loadFromFile(filename);
        sprite.setTexture(texture);
        x=100; y=100;
        sprite.setPosition(x, y);
        sprite.setScale(0.75,0.75);
        lives = 3; dragcount=0;
        points = 100;
        speed = 0.1;
        isMovingLeft = true;
        collided1=false; collided2=false; collided3=false;
        bombCounter = 0;
        bombInterval = 3.0; // Set the bomb interval to 2 seconds
        bombTimer.restart(); // Start the bomb timer
        beamInterval=2.0;
        beamCounter=0;
        isFiringBeam=false;
        mscore=true;
        beamTimer.restart();
    }
    
    virtual ~Enemy()
    {
        delete bombs;
//        delete beam;
//        delete dfire1;
//        delete dfire2;
//        delete dfire3;
    }


    virtual void move() {
        if (isMovingLeft) {
            sprite.move(-speed, 0);
            if (sprite.getPosition().x <= 0) {
                isMovingLeft = false;
            }
        } else {
            sprite.move(speed, 0);
            if ((sprite.getPosition().x >= 740) && (sprite.getPosition().x <= 800) ) {
                isMovingLeft = true;
            }
        }
    }

    
	
    virtual void spawnBomb()
    {
        // Spawn a bomb at regular intervals
        if (bombTimer.getElapsedTime().asSeconds() >= bombInterval && !(bombs->sprite.getPosition().x==1100) ) {
            bombs->sprite.setPosition(sprite.getPosition().x + 40, sprite.getPosition().y + 50);
            bombCounter++;
            bombTimer.restart();
        }
    }



	virtual void CheckCollision(Player& player, Bullet &bu)//bullet hit enemy
	{
		if (((bu.sprite.getPosition().x)>=(sprite.getPosition().x) && ((bu.sprite.getPosition().x)<=(sprite.getPosition().x)+100) &&
		  ((bu.sprite.getPosition().y)>=(sprite.getPosition().y)+50)))//collided
		{
			if(!collided1)
			{
			player.hitTarget();//bullet resets
			collided1=true;
			}
			
			if (collided1){
				decreaseLife();//enemy loses a hp
				player.score+=20;
				collided1=false;
			}
		}
	}


	void CheckCollision(Player& player)//bomb hit player
	{
		if (((bombs->sprite.getPosition().x)>=(player.sprite.getPosition().x-10) && ((bombs->sprite.getPosition().x)<=(player.sprite.getPosition().x)+90) &&
		 ((bombs->sprite.getPosition().y)>=(player.sprite.getPosition().y)-10) && ((bombs->sprite.getPosition().y)<=(player.sprite.getPosition().y)) ))//collided
		{
			if(!collided2)
			{
		//	bomb disappears if it comes in contact with Player
			bombs->sprite.setPosition(sprite.getPosition().x+30, sprite.getPosition().y+40); // reset bomb
			collided2=true;
			cout<<"ouch ";
			player.lives-=1;
			}
			
			if (collided2){
			//	cout<<"ouch ";
			//	player.lives-=1;
				collided2=false;
			}
		}
	}

//checks if enemy needs to be destroyed
void decreaseLife() {
	if (lives > 0){
    lives--;
 //   cout<<" ouch";
 	}
    if (lives == 0) {
        // Enemy
        sprite.setPosition(1000, 1000); // Move the enemy sprite out of the screen
        bombs->sprite.setPosition(1100, 1100);//move bombs out of the screen
    }
}

	void CheckCollision3(Player& player)//beam hit player
	{
		if (((beam->sprite.getPosition().x)>=(player.sprite.getPosition().x-50) && ((beam->sprite.getPosition().x)<=(player.sprite.getPosition().x)+50) &&
		 ((beam->sprite.getPosition().y)>=(player.sprite.getPosition().y)+50)))//collided
		{
			if(!collided3)
			{
		//	beam disappears if it comes in contact with Player
			beam->sprite.setPosition(sprite.getPosition().x+40, sprite.getPosition().y); // reset beam
			collided3=true;
			}
			
			if (collided3){
				player.lives-=1;
				cout<<"ouch";
				collided3=false;
			}
		}
	}
	
	void CheckCollision5(Player& player)//dragon fire hit player
	{
		if (((dfire1->sprite.getPosition().x-10)>=(sprite.getPosition().x-50) && ((dfire1->sprite.getPosition().x+10)<=(player.sprite.getPosition().x)+50) &&
		 ((dfire1->sprite.getPosition().y)>=(player.sprite.getPosition().y)-10)))//collided
		{
			if(!collided1)
			{
		//	Dfire1 disappears if it comes in contact with Player
			dfire1->sprite.setPosition(380, 350); // reset dfire1
			collided1=true;
			}
			
			if (collided1){
				player.lives-=1;
				cout<<"ouch";
				collided1=false;
			}
		}
	}
	
	void CheckCollision6(Player& player)//dragon fire hit player
	{
		if (((dfire2->sprite.getPosition().x-10)>=(player.sprite.getPosition().x-50) && ((dfire2->sprite.getPosition().x+10)<=(player.sprite.getPosition().x)+50) &&
		 ((dfire2->sprite.getPosition().y)>=(player.sprite.getPosition().y)-10)))//collided
		{
			if(!collided1)
			{
		//	Dfire2 disappears if it comes in contact with Player
			dfire2->sprite.setPosition(380, 350); // reset dfire1
			collided1=true;
			}
			
			if (collided1){
				player.lives-=1;
				cout<<"ouch";
				collided1=false;
			}
		}
	}

	void CheckCollision7(Player& player)//dragon fire hit player
	{
		if (((dfire3->sprite.getPosition().x-10)>=(player.sprite.getPosition().x-50) && ((dfire3->sprite.getPosition().x+10)<=(player.sprite.getPosition().x)+50) &&
		 ((dfire3->sprite.getPosition().y)>=(player.sprite.getPosition().y)-10)))//collided
		{
			if(!collided1)
			{
		//	Dfire3 disappears if it comes in contact with Player
			dfire3->sprite.setPosition(380, 350); // reset dfire1
			collided1=true;
			}
			
			if (collided1){
				player.lives-=1;
				cout<<"ouch";
				collided1=false;
			}
		}
	}
	
	virtual void fireEne(Player &player){
	if (((player.bfire->sprite.getPosition().x)>=(sprite.getPosition().x) && ((player.bfire->sprite.getPosition().x)<=(sprite.getPosition().x)+100) &&
		  ((player.bfire->sprite.getPosition().y)>=(sprite.getPosition().y)+50)))//collided
		{
			if(!collided1)
			{
			player.bfire->sprite.setPosition(player.sprite.getPosition().x+40, player.sprite.getPosition().y);//bfire resets
			collided1=true;
			}
			
			if (collided1){
				decreaseLife();//enemy loses a hp
				player.score+=20;
				collided1=false;
			}
		}
	}

	int CheckBoundaryd1(){//checks if the beam/bomb/fire hit screen boundary
	// dragcount=0;
		if (dfire1->sprite.getPosition().x>= 780 || dfire1->sprite.getPosition().x <= 0 || dfire1->sprite.getPosition().y >= 780){
        	dfire1->sprite.setPosition(380,350);//set it back to the vals set when calling const
        	dragcount++;
        	//dfire1->move(0 , 1);
       	}	
       	return dragcount;
	}
	
	void CheckBoundaryd2(){//checks if the beam/bomb/fire hit screen boundary
		if (dfire2->sprite.getPosition().x>= 780 || dfire2->sprite.getPosition().x <= 0 || dfire2->sprite.getPosition().y >= 780){
        	dfire2->sprite.setPosition(520,250);//set it back to the vals set when calling const
        	//dfire2->move(0 , 1);
       	}	
	}
	
	void CheckBoundaryd3(){//checks if the beam/bomb/fire hit screen boundary
		if (dfire3->sprite.getPosition().x>= 780 || dfire3->sprite.getPosition().x <= 0 || dfire3->sprite.getPosition().y >= 780){
        	dfire3->sprite.setPosition(220,250);//set it back to the vals set when calling const
        	//dfire3->move(0 , 1);
       	}	
	}

	void CheckCollision4(Player& player, Bullet &bu, Enemy& mon)//bullet hit monster
	{
		if (((bu.sprite.getPosition().x)>=(mon.sprite.getPosition().x-50) && ((bu.sprite.getPosition().x)<=(mon.sprite.getPosition().x)+200) &&
		 ((bu.sprite.getPosition().y)<=(mon.sprite.getPosition().y)+50)))//collided
		{
		//	cout<<"hitting moster";
			if(!collided1)
			{
			player.hitTarget();//bullet resets
			collided1=true;
			}
			
			if (collided1){
				collided1=false;
			}
		}
	}
	

	void CheckCollision8(Player& player, Bullet &bu, Enemy& dr)//bullet hit dragon (150, 10)
	{
		if (((bu.sprite.getPosition().x)>=(dr.sprite.getPosition().x) && ((bu.sprite.getPosition().x)<=(dr.sprite.getPosition().x)+530) &&
		 ((bu.sprite.getPosition().y)<=(dr.sprite.getPosition().y)+250)))//collided
		{
		//	cout<<"hitting dragon";
			if(!collided1)
			{
			player.hitTarget();//bullet resets
			collided1=true;
			}
			
			if (collided1){
				collided1=false;
			}
		}
	}

    virtual void fireBeam()//fire continuously after 2 seconds
     {
        // Check if it's time to fire another beam
        if (beamTimer.getElapsedTime().asSeconds() >= beamInterval) {
            isFiringBeam = !isFiringBeam;
            ++beamCounter;
          //  cout<<beamCounter<<" ";
            beamTimer.restart();
        }
        // Fire the beam
        if (isFiringBeam) {
            // code to fire the beam of continuous lightning goes here
            beam->sprite.setPosition(sprite.getPosition().x+100, sprite.getPosition().y+70);//moving the beam
            // for example, you can set a flag to indicate that the beam is active
            // and update the position of the beam sprite in the game loop
        }
    }
    
    
    void touchedEnemy(Enemy& imd, Player& player, RenderWindow& window)
    {
        if ( ((player.sprite.getPosition().x)>=(imd.sprite.getPosition().x) ) && ((player.sprite.getPosition().x)<=(imd.sprite.getPosition().x)+90) &&
		 ((player.sprite.getPosition().y)<=(imd.sprite.getPosition().y)+40) && ((player.sprite.getPosition().y)>=(imd.sprite.getPosition().y)-20)) // player touches enemy
		 {
			player.lives-=1;
		 	cout<<"touched enemy ;(\n";
		 	cout<<(player.sprite.getPosition().x)<<"	"<<(imd.sprite.getPosition().x)<<endl;
		 	cout<<(player.sprite.getPosition().y)<<"	"<<(imd.sprite.getPosition().y)<<endl;
    		//window.close(); //player died
    	}
    }
    
    void touchedEnemy2(Enemy& imd, Player& player, RenderWindow& window)
    {
        if ( ((player.sprite.getPosition().x)>=(imd.sprite.getPosition().x-10) ) && ((player.sprite.getPosition().x)<=(imd.sprite.getPosition().x)+200) &&
		 ((player.sprite.getPosition().y)<=(imd.sprite.getPosition().y)+100) ) // player touches monster
		 {
		 	player.lives-=1;
		 	cout<<"touched Monster ;(\n";
		 	cout<<(player.sprite.getPosition().x)<<"	"<<(imd.sprite.getPosition().x)<<endl;
		 	cout<<(player.sprite.getPosition().y)<<"	"<<(imd.sprite.getPosition().y)<<endl;
    		//window.close(); //player died
    	}
    
    }
    
    void touchedEnemy3(Enemy& dr, Player& player, RenderWindow& window)
    {
        if ( ((player.sprite.getPosition().x)>=(dr.sprite.getPosition().x-100) ) && ((player.sprite.getPosition().x)<=(dr.sprite.getPosition().x)+400) &&
		 ((player.sprite.getPosition().y)<=(dr.sprite.getPosition().y)+300) && ((player.sprite.getPosition().y)>=(dr.sprite.getPosition().y)+40) ) // player touches enemy
		 {
		 	player.lives-=1;
		 	cout<<"touched Dragon ;(\n";
		 	cout<<(player.sprite.getPosition().x)<<"	"<<(dr.sprite.getPosition().x)<<endl;
		 	cout<<(player.sprite.getPosition().y)<<"	"<<(dr.sprite.getPosition().y)<<endl;
    		//window.close(); //player died
    	}
    
    }

    // Add any other necessary methods
};

