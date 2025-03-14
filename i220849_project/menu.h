#include <fstream>
#include "game.h"
class Menu{
public:

//add menu attributes here
std::fstream highScoresFile;
Game g;

Menu()
{
highScoresFile.open("high_scores.txt", std::ios::app);
//constructors body
}

void saveScore()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    // Open the high scores file in read mode to read the existing scores
    std::ifstream highScoresFile("high_scores.txt");
    const int MAX_SCORES = 10;
    std::string names[MAX_SCORES];
    int scores[MAX_SCORES];
    int numScores = 0;

    if (highScoresFile.is_open()) {
        while (numScores < MAX_SCORES && highScoresFile >> names[numScores] >> scores[numScores]) {
            numScores++;
        }
        highScoresFile.close();
    }

    // Insert the new score into the scores array at the correct position
    int insertIndex = numScores;
    for (int i = 0; i < numScores; i++) {
        if (g.p->score > scores[i]) {
            insertIndex = i;
            break;
        }
    }

    // Shift the existing scores to make room for the new score
    for (int i = numScores - 1; i > insertIndex; i--) {
        scores[i] = scores[i - 1];
        names[i] = names[i - 1];
    }

    // Insert the new score
    scores[insertIndex] = g.p->score;
    names[insertIndex] = name;

    // Open the high scores file in write mode to update the scores
    std::ofstream highScoresFileWrite("high_scores.txt");
    if (highScoresFileWrite.is_open()) {
        for (int i = 0; i < numScores + 1; i++) {
            highScoresFileWrite << names[i] << " " << scores[i] << std::endl;
        }
        highScoresFileWrite.close();
    }
}



void display_high_scores()
{
    const int MAX_SCORES = 10;
    std::string names[MAX_SCORES];
    int scores[MAX_SCORES];

    // Read the scores from the file and store them in the arrays
    std::ifstream highScoresFile("high_scores.txt");
    if (highScoresFile.is_open()) {
        int numScores = 0;
        while (numScores < MAX_SCORES && highScoresFile >> names[numScores] >> scores[numScores]) {
            numScores++;
        }
        highScoresFile.close();

        // Sort the scores and names in descending order
        for (int i = 0; i < numScores - 1; i++) {
            for (int j = i + 1; j < numScores; j++) {
                if (scores[i] < scores[j]) {
                    // Swap the scores and names
                    int tempScore = scores[i];
                    scores[i] = scores[j];
                    scores[j] = tempScore;
                    std::string tempName = names[i];
                    names[i] = names[j];
                    names[j] = tempName;
                }
            }
        }

        // Load the font and create the high scores text object
        sf::Font font;
        if (!font.loadFromFile("img/Tetris.ttf")) {
            std::cerr << "Error loading font." << std::endl;
            return;
        }
        sf::Text highScoreText("High Scores", font, 36);
        highScoreText.setPosition(300, 100);

        // Load the badge textures and create the badge sprites
        sf::Texture goldBadgeTexture, silverBadgeTexture, bronzeBadgeTexture;
        if (!goldBadgeTexture.loadFromFile("img/gold_badge.png")) {
            std::cerr << "Error loading gold badge texture." << std::endl;
            return;
        }
        sf::Sprite goldBadge(goldBadgeTexture);
        if (!silverBadgeTexture.loadFromFile("img/silver_badge.png")) {
            std::cerr << "Error loading silver badge texture." << std::endl;
            return;
        }
        sf::Sprite silverBadge(silverBadgeTexture);
        if (!bronzeBadgeTexture.loadFromFile("img/bronze_badge.png")) {
            std::cerr << "Error loading bronze badge texture." << std::endl;
            return;
        }
        sf::Sprite bronzeBadge(bronzeBadgeTexture);

        // Create the window and set its title
        sf::RenderWindow window(sf::VideoMode(800, 600), "High Scores");

        // Display the scores and badges
        int y = 200;
        for (int i = 0; i < numScores; i++) {
            sf::Text scoreText(names[i] + " - " + std::to_string(scores[i]), font, 24);
            scoreText.setPosition(300, y);
            window.draw(scoreText);

            if (i == 0) {
                goldBadge.setPosition(200, y - 5);
                window.draw(goldBadge);
            } else if (i == 1) {
                silverBadge.setPosition(200, y - 5);
                window.draw(silverBadge);
            } else if (i == 2) {
                bronzeBadge.setPosition(200, y - 5);
                window.draw(bronzeBadge);
            }

            y += 40;
        }


        // Draw the high scores text and display the window
        window.draw(highScoreText);
        window.display();

        // Wait for the window to close
        sf::Event event;
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.key.code == Keyboard::Escape)     //Check if the other key pressed is S key
			window.close(); 
                
            }
        }

        highScoresFile.close();
    }
}


void display_menu()

{

//display menu screen here

    Texture menuPic, helpPic, pausePic, overPic;
    menuPic.loadFromFile("img/menu.jpg");
    helpPic.loadFromFile("img/instructions.jpg");
    pausePic.loadFromFile("img/paused.jpg");
    overPic.loadFromFile("img/over.jpg");
    
    Sprite Menu(menuPic), Help(helpPic), Paused(pausePic), Over(overPic);
    //Game g; 
    
    RenderWindow windowMenu(VideoMode(590, 780), "Menu");	//calling the menu window
    while (windowMenu.isOpen())
    {
    	Event e;
    	while (windowMenu.pollEvent(e))
    	{
    		if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
			{windowMenu.close(); }                          //Opened window disposes
		if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
			if (e.key.code == Keyboard::Escape)            //when esc pressed, window closes
				{windowMenu.close(); }                     
			else if (e.key.code == Keyboard::S)     //Check if the other key pressed is S key
				windowMenu.close(); 
			else if (e.key.code == Keyboard::H)	
				display_high_scores();
				                        //close menu, start new game
			else if (e.key.code == Keyboard::I)   //Check if the other key pressed is RIGHT key
			{
				RenderWindow windowHelp(VideoMode(590, 780), "Instructions");                          //renders a new help window
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
							else if (e.key.code == Keyboard::P)
							{
								windowHelp.close();
								windowMenu.close();
							}
						}
					}
				windowHelp.draw(Help);
				windowHelp.display();
				}
			}
			else if (e.key.code == Keyboard::P) windowMenu.close(); 
		}
		
    	}
    	windowMenu.draw(Menu);	//the menu img
    	windowMenu.display();	
    	
    	
	
    }

// add functionality of all the menu options here

//if Start game option is chosen 
    
    g.start_game();
	if (g.p->lives <= 0)
	{
	
  	  saveScore();
  	  RenderWindow windowOver(VideoMode(590, 780), "Over");                          //renders a new help window
				while (windowOver.isOpen())
				{
					Event e;
					while (windowOver.pollEvent(e))
					{
						if (e.type == Event::Closed)
							windowOver.close();
						if (e.type == Event::KeyPressed) 
						{
							if (e.key.code == Keyboard::Escape)
								windowOver.close();
							else if (e.key.code == Keyboard::P)
							{
								windowOver.close();
							}
						}
					}
  	  windowOver.draw(Over);
   		windowOver.display();
				}
 	  highScoresFile.close();
	}


}


};
