

class Invader : public Enemy {
public:

//    Sprite sprite; // Invader sprite
//    Texture texture; // Texture of the Invader sprite
    Invader(string filenameI, int x, int y, int level, int type) : Enemy(filenameI) {
 //       texture.loadFromFile(filenameI);
 //       sprite.setTexture(texture);
        sprite.setPosition(x, y);
        sprite.setScale(0.75, 0.75);
        switch (type) {
            case 0: // Alpha invader
                bombInterval = 5.0;
                
                break;
            case 1: // Beta invader
                bombInterval = 3.0;
                //Beta(x, y, level);//make new beta of type invader
                break;
            case 2: // Gamma invader
                bombInterval = 2.0;
                break;
            default:
                break;
        }
        sprite.setPosition(x, y);
    }
};

class Alpha : public Invader {
public:
    Alpha(string filenameI , int x, int y, int level) : Invader(filenameI, x, y, level, 0) {
        bombs->speed = 0.1 + level * 0.1;
    }
    
	void CheckCollision(Player& player, Bullet &bu) override //bullet hit enemy
	{
		if (((bu.sprite.getPosition().x)>=(sprite.getPosition().x) && ((bu.sprite.getPosition().x)<=(sprite.getPosition().x)+100) &&
		 ((bu.sprite.getPosition().y)<=(sprite.getPosition().y)+50) && ((bu.sprite.getPosition().y)>=(sprite.getPosition().y)) ))//collided
		{
			if(!collided1)
			{
			player.hitTarget();//bullet resets
			collided1=true;
			}
			
			if (collided1){
				decreaseLife();//enemy loses a hp
				player.score+=10;
				collided1=false;
			}
		}
	}
	
	
	void fireEne(Player &player) override {
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
				player.score+=10;
				collided1=false;
			}
		}
	}
};

class Beta : public Invader {
public:
    Beta(string filenameI ,int x, int y, int level) : Invader(filenameI, x, y, level, 1) {
        bombs->speed = 0.2 + level * 0.1;
    }
    
    void CheckCollision(Player& player, Bullet &bu) override //bullet hit enemy
	{
		if (((bu.sprite.getPosition().x)>=(sprite.getPosition().x) && ((bu.sprite.getPosition().x)<=(sprite.getPosition().x)+100) &&
		 ((bu.sprite.getPosition().y)<=(sprite.getPosition().y)+50) && ((bu.sprite.getPosition().y)>=(sprite.getPosition().y)) ))//collided
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
	
	void fireEne(Player &player) override {
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
    
};

class Gamma : public Invader {
public:
    Gamma(string filenameI ,int x, int y, int level) : Invader(filenameI, x, y, level, 2) {
        bombs->speed = 0.3 + level * 0.1;
    }
    
    void move() override {
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
    
    void CheckCollision(Player& player, Bullet &bu) override //bullet hit enemy
	{
		if (((bu.sprite.getPosition().x)>=(sprite.getPosition().x) && ((bu.sprite.getPosition().x)<=(sprite.getPosition().x)+100) &&
		 ((bu.sprite.getPosition().y)<=(sprite.getPosition().y)+50) && ((bu.sprite.getPosition().y)>=(sprite.getPosition().y)) ))//collided
		{
			if(!collided1)
			{
			player.hitTarget();//bullet resets
			collided1=true;
			}
			
			if (collided1){
				decreaseLife();//enemy loses a hp
				player.score+=30;
				collided1=false;
			}
		}
	}
	
	void fireEne(Player &player) override {
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
				player.score+=30;
				collided1=false;
			}
		}
	}
    
};


