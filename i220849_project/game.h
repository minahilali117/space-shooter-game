
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
#include "player.h"
#include "Enemy.h"
#include "Monster.h"
#include "Dragon.h"
#include "Invader.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
Font font;
Text score; Text updatedScore; Text live; Text lives;
Sprite background;// Help(helpPic), Paused(pausePic); //Game background sprite 
Texture bg_texture;// helpPic, pausePic;
Player* p; //player 
int numBombs;
Enemy* en; // Array of enemies
Enemy* monster;
Enemy* drag;
Enemy* inv2; Enemy* inv3; Enemy* inv4; Enemy* inv5; Enemy* inv6;
//std::fstream highScoresFile;

Game()
{
p=new Player("img/playerShip2_blue.png");
en = new Alpha("img/enemy_1.png", 150, 300, 1);//treating enemy as invader for now
drag = new Dragon("img/dragon.png");
monster = new Monster("img/monster.png");
inv2 = new Alpha ("img/enemy_1.png", 350, 300, 1);
inv3 = new Alpha ("img/enemy_1.png", 550, 300, 1);
inv4 = new Beta ("img/enemy_2.png", 250, 100, 2);
inv5 = new Beta ("img/enemy_2.png", 450, 100, 2);
inv6 = new Gamma ("img/enemy_3.png", 650, 100, 3);
bg_texture.loadFromFile("img/background4.jpg");
//helpPic.loadFromFile("img/help.jpg");
//pausePic.loadFromFile("img/paused.jpg");
font.loadFromFile("img/Tetris.ttf");
background.setTexture(bg_texture);
background.setScale(0.7, 0.9);
background.setPosition(0, 0);

score.setFont(font);
score.setString("Score: ");
score.setCharacterSize(24);
score.setPosition(10, 10);

updatedScore.setFont(font);
updatedScore.setString(" 0 ");
updatedScore.setCharacterSize(24);
updatedScore.setPosition(100, 10);


live.setFont(font);
live.setString("lives: ");
live.setCharacterSize(24);
live.setPosition(10, 50);

lives.setFont(font);
lives.setString(" 3 ");
lives.setCharacterSize(24);
lives.setPosition(100, 50);

//highScoresFile.open("high_scores.txt", std::ios::out);

}

~Game() {
	delete en;
	delete p;
	delete monster;
	delete drag;
	delete inv2;
	delete inv3;
	delete inv4;
	delete inv5;
	delete inv6;
	//highScoresFile.close();
}

void start_game()
{
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), title);
    Clock clock;
   // Clock MonsterTimer;
    float timer=0;
    Texture helpPic, pausePic, overPic, menuPic;
    helpPic.loadFromFile("img/instructions.jpg");
    pausePic.loadFromFile("img/paused.jpg");
    menuPic.loadFromFile("img/menu.jpg");
    overPic.loadFromFile("img/over.jpg");
    Sprite Menu(menuPic), Help(helpPic), Paused(pausePic), Over(overPic);
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time;  
        //cout<<timer<<"	";
 	Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
          
	if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
            p->move("l");    // Player will move to left
	if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            p->move("r");  //player will move to right
	if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
            p->move("u");    //playet will move upwards
	if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            p->move("d");  //player will move downwards
    if (Keyboard::isKeyPressed(Keyboard::Space))
	    p->fire(*p->b);  // Fire a bullet
	if (Keyboard::isKeyPressed(Keyboard::Right)){
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			p->rotate("r");  // Rotate player to the right
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)){
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			p->rotate("l");  // Rotate player to the right
		}
	}
	
	if (e.key.code == Keyboard::P){
	RenderWindow windowPause(VideoMode(590, 780), "Paused");
    	while (windowPause.isOpen())
        {
        	Event e;
			while (windowPause.pollEvent(e))
			{
				if (e.type == Event::Closed)
					windowPause.close();
					
				if (e.type == Event::KeyPressed) 
				{
					if (e.key.code == Keyboard::P)
						windowPause.close();
						else if (e.key.code == Keyboard::E)//END GAME
						{
							windowPause.close();
							window.close();
						}
						else if (e.key.code == Keyboard::I)
						{
							RenderWindow windowHelp(VideoMode(590, 780), "instructions");                          //renders a new help window
							while (windowHelp.isOpen())
							{
							Event e;
							while (windowHelp.pollEvent(e))
							{
								if (e.type == Event::Closed)
									windowHelp.close();
								if (e.type == Event::KeyPressed) 
								{
									if (e.key.code == Keyboard::Escape)
										windowHelp.close();
									else if (e.key.code == Keyboard::S)
									{
										windowHelp.close();
										//windowMenu.close();
									}
								}
							
							}
							
							windowHelp.draw(Help);
							windowHelp.display();
							}
							
						} 
						else if (e.key.code == Keyboard::R)
						{
							delete p;
							delete en;
							delete monster;
							delete drag;
							delete inv2;
							delete inv3;
							delete inv4;
							delete inv5;
							delete inv6;

							p = new Player("img/playerShip2_blue.png");
							en = new Alpha("img/enemy_1.png", 150, 300, 1);
							drag = new Dragon("img/dragon.png");
							monster = new Monster("img/monster.png");
							inv2 = new Alpha("img/enemy_1.png", 350, 300, 1);
							inv3 = new Alpha("img/enemy_1.png", 550, 300, 1);
							inv4 = new Beta("img/enemy_2.png", 250, 100, 2);
							inv5 = new Beta("img/enemy_2.png", 450, 100, 2);
							inv6 = new Gamma("img/enemy_3.png", 650, 100, 3);

							p->score = 0;
							p->lives = 3;
							windowPause.close();
						}

					}
					
				}
				windowPause.draw(Paused);
				windowPause.display(); 
                }
	}
                

	if (p->b->sprite.getPosition().y < 0)
	    p->b->sprite.setPosition(1000, 1000);  // Move the bullet off screen if it goes too high
	else
	{
		p->incrementLives();
		p->dodgeDanger();
		bool pfa= p->catchFire();p->firep();
	    p->b->move("u");  // Move the bullet upwards
	    en->CheckCollision(*p, *p->b);
	    en->fireEne(*p);
	    en->touchedEnemy(*en, *p, window);
	    inv2->CheckCollision(*p, *p->b);
	    inv2->fireEne(*p);
	    inv2->touchedEnemy(*inv2, *p, window);
	    inv3->CheckCollision(*p, *p->b);
	    inv3->fireEne(*p);
	    inv3->touchedEnemy(*inv3, *p, window);
	    inv4->CheckCollision(*p, *p->b);
	    inv4->fireEne(*p);
	    inv4->touchedEnemy(*inv4, *p, window);
	    inv5->CheckCollision(*p, *p->b);
	    inv5->fireEne(*p);
	    inv5->touchedEnemy(*inv5, *p, window);
	    inv6->CheckCollision(*p, *p->b);
	    inv6->fireEne(*p);
	    inv6->touchedEnemy(*inv6, *p, window);
	    inv6->move();
	}	
	   if (en->sprite.getPosition().x >= 999 && inv2->sprite.getPosition().x >= 999 && inv3->sprite.getPosition().x >= 999 && inv4->sprite.getPosition().x >= 999 && inv6->sprite.getPosition().x >= 999 && inv5->sprite.getPosition().x >= 999){// enemy died
	  	monster->beam->move();  // Move the beam downwards
	 // 	monster->spawnBomb();
	  	monster->move();
	    monster->CheckCollision3(*p);  
	    monster->CheckCollision4(*p,*p->b, *monster) ;
	   
	   	if (monster->beam->sprite.getPosition().y>= 780 && en->sprite.getPosition().x >= 999)
		{
			//cout<<"firing";
			monster->fireBeam();
		}
		if ((monster->beamCounter) >=6)//monster goes away when time since the game started>=10
		{
		//	cout<<"timer\n";
			monster->sprite.setPosition(1000, 1000);//set monster off screen
			monster->beam->sprite.setPosition(1000, 1000);//set monster beam off screen
		}
		
		monster->touchedEnemy2(*monster,*p , window);
		
		if(monster->sprite.getPosition().x >= 999)//monster died 
		{
		//p->score+=40;
		if(monster->mscore==true){p->score+=40; monster->mscore=false;}
		drag->touchedEnemy3(*drag,*p , window);
		drag->CheckCollision8(*p,*p->b, *drag) ;
		if(p->sprite.getPosition().x<= 380 && p->sprite.getPosition().y>= 350)//player is around x<= 380, y>=350 engage dfire1, dfire3
		{
			drag->dfire2->sprite.setPosition(1000,1000);
		
			drag->dfire1->move(0 , 1);//380, 350
			drag->CheckBoundaryd1();
			drag->dfire3->move(-1 , 1);//220, 250
			drag->CheckBoundaryd3();
			drag->CheckCollision5(*p);
			drag->CheckCollision7(*p);
		}
		
		else if(p->sprite.getPosition().x>= 380 && p->sprite.getPosition().y>= 350)//player is around x>= 380, y>=350 engage dfire1, dfire2
		{
			drag->dfire3->sprite.setPosition(1000,1000);
			
			drag->dfire2->move(1, 1);//520, 250
			drag->CheckBoundaryd2();
			drag->dfire1->move(0 , 1);//380, 350
			int pepper= drag->CheckBoundaryd1();
			drag->CheckCollision5(*p);
			drag->CheckCollision6(*p);
		}	
		
		if(p->sprite.getPosition().y<= 350){
			drag->dfire1->sprite.setPosition(1000,1000);
			drag->dfire2->sprite.setPosition(1000,1000);
			drag->dfire3->sprite.setPosition(1000,1000);
		}
		
		}
			if(drag->dragcount>=5)//dragon died
			{
				p->score+=50;
				window.close();
				p->lives=0;
			}
		 
		}
           
     
      
	////////////////////////////////////////////////
	/////     Call your functions here          ////
	
    if (p->sprite.getPosition().x<= 0 || p->sprite.getPosition().x>= 780 || p->sprite.getPosition().y>= 780 || p->sprite.getPosition().y<= 0)
		p->wrapAround();
		
	if (p->b->sprite.getPosition().y<= 0 && p->catchFire()==false)
	{
		p->b->sprite.setPosition(p->sprite.getPosition().x+40, p->sprite.getPosition().y);
		//p->b->hitBound=p->hitBoundary(*p->b);
	}
	

	
	if (p->bfire->sprite.getPosition().y<= 0 /*&& p->catchFire()==true*/)
	{
		p->bfire->sprite.setPosition(p->sprite.getPosition().x, p->sprite.getPosition().y);
		//p->b->hitBound=p->hitBoundary(*p->b);
	}
	
	
    if (en->bombs->sprite.getPosition().y >= 780)
	    en->bombs->sprite.setPosition(1000, 1000);  // Move the bomb off screen if it goes too low
	else
	{
	en->bombs->move("d");
	en->CheckCollision(*p);
    }   
    
    if (en->bombTimer.getElapsedTime().asSeconds() > en->bombInterval){
    	en->spawnBomb();
    }
    
    if (inv2->bombs->sprite.getPosition().y >= 780)
	    inv2->bombs->sprite.setPosition(1000, 1000);  // Move the bomb off screen if it goes too low
	else
	{
	inv2->bombs->move("d");
	inv2->CheckCollision(*p);//bomb hit player
    }   
    
    if (inv2->bombTimer.getElapsedTime().asSeconds() > inv2->bombInterval){
    	inv2->spawnBomb();
    }
    
    if (inv3->bombs->sprite.getPosition().y >= 780)
	    inv3->bombs->sprite.setPosition(1000, 1000);  // Move the bomb off screen if it goes too low
	else
	{
	inv3->bombs->move("d");
	inv3->CheckCollision(*p);//bomb hit player
    }   
    
    if (inv3->bombTimer.getElapsedTime().asSeconds() > inv3->bombInterval){
    	inv3->spawnBomb();
    }
    
    if (inv4->bombs->sprite.getPosition().y >= 780)
	    inv4->bombs->sprite.setPosition(1000, 1000);  // Move the bomb off screen if it goes too low
	else
	{
	inv4->bombs->move("d");
	inv4->CheckCollision(*p);//bomb hit player
    }   
    
    if (inv4->bombTimer.getElapsedTime().asSeconds() > inv4->bombInterval){
    	inv4->spawnBomb();
    }
    
    if (inv5->bombs->sprite.getPosition().y >= 780)
	    inv5->bombs->sprite.setPosition(1000, 1000);  // Move the bomb off screen if it goes too low
	else
	{
	inv5->bombs->move("d");
	inv5->CheckCollision(*p);//bomb hit player
    }   
    
    if (inv5->bombTimer.getElapsedTime().asSeconds() > inv5->bombInterval){
    	inv5->spawnBomb();
    }
    
    if (inv6->bombs->sprite.getPosition().y >= 780)
	    inv6->bombs->sprite.setPosition(1000, 1000);  // Move the bomb off screen if it goes too low
	else
	{
	inv6->bombs->move("d");
	inv6->CheckCollision(*p);//bomb hit player
    }   
    
    if (inv6->bombTimer.getElapsedTime().asSeconds() > inv6->bombInterval){
    	inv6->spawnBomb();
    }
    
    
    if (p->lives<=0)
    	window.close(); //close the game 
    	
    	
    	

    
	//////////////////////////////////////////////


	window.clear(Color::Black); //clears the screen
	window.draw(background);  // setting background
	window.draw(p->sprite);   // setting player on screen
	window.draw(p->b->sprite); // drawing bullet
	window.draw(inv2->sprite);
	window.draw(en->sprite); // dreawing enemy
	window.draw(en->bombs->sprite);
	window.draw(inv2->bombs->sprite);
	window.draw(inv3->sprite);
	window.draw(inv3->bombs->sprite);
	window.draw(inv4->sprite);
	window.draw(inv4->bombs->sprite);
	window.draw(inv5->sprite);
	window.draw(inv5->bombs->sprite);
	window.draw(inv6->sprite);
	window.draw(inv6->bombs->sprite);
	window.draw(score);
	updatedScore.setString(std::__cxx11::to_string(p->score));
	window.draw(updatedScore);
	window.draw(live);
	lives.setString(std::__cxx11::to_string(p->lives));
	window.draw(lives);
	window.draw(p->liv->sprite);
	window.draw(p->dan->sprite);
	window.draw(p->pfire->sprite);
	window.draw(p->bfire->sprite);
	//score.setString("Score: ");
	
	if (en->sprite.getPosition().x>=800 && inv2->sprite.getPosition().x >= 800 && inv3->sprite.getPosition().x >= 800  && inv4->sprite.getPosition().x >= 800 && inv5->sprite.getPosition().x >= 800 && inv6->sprite.getPosition().x >=800){
		window.draw(monster->sprite);
		window.draw(monster->beam->sprite);
		if (monster->sprite.getPosition().x>=999){
			window.draw(drag->dfire1->sprite);
			window.draw(drag->dfire2->sprite);
			window.draw(drag->dfire3->sprite);
			window.draw(drag->sprite);
		}
	}
	window.display();  //Displying all the sprites
    }
    


}




};

