#include <SFML/Graphics.hpp>  //
#include <SFML/Window.hpp>    //   SFML Libraries
#include <SFML/System.hpp>    //
#include <SFML/Audio.hpp>     // 
#include <iostream>           // input-output
#include <sstream>            // strings as input-output
#include <fstream>            // file handling
#include <chrono>             // time-related
#include <iomanip>            // precision

#include "Pong.h"             // header file

using namespace sf;
using namespace std;

int tempbg = 1;
int score_1 = 0;
int score_2 = 0;
string elapsed_time_str = "00:00";
int mins;
int secs;

void funcmainmenu(Music&);
void funcnewgamemenu(Music&);
void loadingwindow();
void maingame(bool);
void resumegame();
void rules(Music&);
void bgchange(Music&);
void gameover(bool, Font, int, int, Text, Text);
void setbg(int temp);
int getbg();

int main()
{
	loadingwindow();
}
void loadingwindow()
{
	//loading window
	// Create the loading window
	RenderWindow loadwind(VideoMode(1400, 800), "Loading...", Style::None);

	// Load the background image
	Texture Texturebg;
	Texturebg.loadFromFile("Texture/wallpaperflare.jpg");
	Sprite Spritebg(Texturebg);


	// Load the font
	Font font;
	font.loadFromFile("Fonts/PAC-FONT.ttf");

	// Background picture
	Music Musicbg;
	Musicbg.openFromFile("Audios/mainmusic.wav");
	Musicbg.play();
	Musicbg.setLoop(true);


	// Create the loading text
	Text load_text("Loading...", font, 58);
	load_text.setFillColor(Color::Yellow);
	load_text.setOutlineColor(Color::Black);
	load_text.setOutlineThickness(2.f);
	load_text.setPosition(570, 350);

	// Create the loading bar
	RectangleShape loadbar(Vector2f(500, 25));
	loadbar.setFillColor(Color(255, 255, 0, 150)); // set the color to yellow
	loadbar.setOutlineThickness(2.f);
	loadbar.setOutlineColor(Color::Black);
	loadbar.setPosition(450, 460);

	// Create the loading bar animation variables
	Clock loadclock;
	float width_bar = 0.f;
	float tot_t = 5.f; // Total time for loading bar to fill up in seconds
	bool loadfinish = false;


	// Main loading window loop
	while (loadwind.isOpen())
	{
		// Handle events
		Event event;
		while (loadwind.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				loadwind.close();
			}
		}

		// Update the loading bar animation
		if (!loadfinish)
		{
			float elapsedTime = loadclock.getElapsedTime().asSeconds();
			if (elapsedTime >= tot_t)
			{
				elapsedTime = tot_t;
				loadfinish = true;
			}
			width_bar = (elapsedTime / tot_t) * 500;
			loadbar.setSize(Vector2f(width_bar, 25));
		}

		// Draw the loading window
		loadwind.clear();
		loadwind.draw(Spritebg);
		loadwind.draw(load_text);
		loadwind.draw(loadbar);
		loadwind.display();

		// If loading is finished, close the loading window
		if (loadfinish)
		{
			loadwind.close();
		}
	}
	if (loadfinish)
	{
		loadwind.close();
		funcmainmenu(Musicbg);
	}
}
void funcmainmenu(Music& Musicbg)
{
	RenderWindow MENU(VideoMode(1400, 800), "Main Menu", Style::None);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	Texture Texturebg;
	if (!Texturebg.loadFromFile("Texture/loadbg2.jpg"))
	{
		cout << "Image not found\n";
	}
	Sprite Spritebg(Texturebg);
	Spritebg.setScale(Vector2f(.9, 1)); //for Taylor Swift picture
//	Spritebg.setScale(Vector2f(1, 1.4)); // for  main bg
	// Load the font
	Font font;
	font.loadFromFile("Fonts/PAC-FONT.ttf");

	Text credits("...Credits...", font, 30);
	credits.setFillColor(Color::Yellow);
	credits.setOutlineColor(Color::Black);
	credits.setOutlineThickness(2.f);
	credits.setPosition(1130, 690);


	Text name("Faraz AND Ahad", font, 25);
	name.setFillColor(Color::White);
	name.setOutlineColor(Color::Black);
	name.setOutlineThickness(2.f);
	name.setPosition(1065, 740);


	while (MENU.isOpen())
	{
		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
				MENU.close();
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Up:
					mainMenu.moveup();
					break;
				case Keyboard::Down:
					mainMenu.movedown();
					break;
				case Keyboard::Return:
					switch (mainMenu.MainMenuPressed())
					{
					case 0: // New Game
					{
						MENU.close();
						funcnewgamemenu(Musicbg);
						break;
					}
					case 1: // Load Game
					{
						MENU.close();
						bgchange(Musicbg);
						break;
					}
					case 2: // Change Background
					{
						MENU.close();
						rules(Musicbg);						
						break;
					}
					case 3: // Exit
						MENU.close();
						break;
					}
					break;
				}
			}
		}


		MENU.draw(Spritebg);
		mainMenu.draw(MENU);
		MENU.draw(credits);
		MENU.draw(name);

		MENU.display();
	}
	Musicbg.stop();
}
void funcnewgamemenu(Music& Musicbg)
{
	RenderWindow MENU(VideoMode(1400, 800), "Main Menu", Style::None);
	MainMenu mainMenu;

	Texture Texturebg;
	if (!Texturebg.loadFromFile("Texture/newgamemenu.jpg"))
	{
		cout << "Image not found\n";
	}

	Sprite Spritebg(Texturebg);
	Spritebg.setScale(Vector2f(0.4, 0.4));
	bool playertype;                // single or multi

	while (MENU.isOpen())
	{
		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
				MENU.close();
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Up:
					mainMenu.moveup();
					break;
				case Keyboard::Down:
					mainMenu.movedown();
					break;
				case Keyboard::Return:
					switch (mainMenu.MainMenuPressed())
					{
					case 0: // Singleplayer
					{
						playertype = false;
						Musicbg.pause();
						maingame(playertype);
						Musicbg.play();
						break;
					}
					case 1: // Multiplayer
					{
						playertype = true;
						Musicbg.pause();
						maingame(playertype);
						Musicbg.play();
						break;
					}
					case 2: // Rules
					{
						MENU.close();
						Musicbg.pause();
						resumegame();
						Musicbg.play();
						funcnewgamemenu(Musicbg);
						break;
					}
					case 3: //Go back
						MENU.close();
						funcmainmenu(Musicbg);
						break;
					}
					break;
				}
			}
		}

		//MENU.clear(Color(52, 73, 94));

		MENU.draw(Spritebg);

		mainMenu.draw(MENU);
		MENU.display();
	}
}
void resumegame()
{
	bool flag = true;

	ifstream read("savegame.txt");
	read >> score_1;
	read >> score_2;
	read >> elapsed_time_str;

	if (score_1 == 0)
	{
		flag = false;
	}

	maingame(flag);
	//cout << score1 << " " << score2 << " " << str;
}
void maingame(bool type)
{
	RenderWindow window_screen(VideoMode(1400, 800), "Game!", Style::None);// Style::Titlebar | Style::Close);
	window_screen.setFramerateLimit(60);

	Font font;
	font.loadFromFile("Fonts/arial.ttf");

	SoundBuffer bouncesound;
	bouncesound.loadFromFile("Audios/bounce2.wav");
	Sound sound(bouncesound);

	SoundBuffer bonus;
	if (!bonus.loadFromFile("Audios/longpop.wav"))
	{
		cout << "Failed to load ";
	}
	Sound sound2(bonus);

	SoundBuffer boadertouch;
	if (!boadertouch.loadFromFile("Audios/whipy.wav"))
	{
		cout << "Failed to load ";
	}
	Sound vibrate(boadertouch);


	Texture backpic;
	int temp = getbg();
	
	
	if (temp == 1)
	{
		backpic.loadFromFile("Texture/bg1.jpg");
	}
	else if (temp == 2)
	{
		backpic.loadFromFile("Texture/bg2.jpg");
	}
	else if (temp == 3)
	{
		backpic.loadFromFile("Texture/bg3.jpg");
	}
	else if (temp == 4)
	{
		backpic.loadFromFile("Texture/bg4.jpg");
	}
	else if (temp == 5)
	{
		backpic.loadFromFile("Texture/bg5.jpg");
	}
	Sprite sprite1(backpic);
	//Adjust sizes by seeing the image
	if (temp == 1)
	{
		sprite1.setScale(Vector2f(1, 1.5));
	}
	else if (temp == 2)
	{
		sprite1.setScale(Vector2f(1.98, 2));
	}
	else if (temp == 3)
	{
		sprite1.setScale(Vector2f(.8, .8));
	}
	else if (temp == 4)
	{
		sprite1.setScale(Vector2f(.7, .7));
	}
	else if (temp == 5)
	{
		sprite1.setScale(Vector2f(1, 1));
	}


	// Centre line
	RectangleShape line(Vector2f(800, .5));
	line.setFillColor(Color::White);
	line.setPosition(Vector2f(window_screen.getSize().x / 2, 0));
	line.rotate(90);

	// Circle in centre
	CircleShape circle_s;
	circle_s.setRadius(9);
	circle_s.setOrigin(circle_s.getRadius(), circle_s.getRadius());
	circle_s.setPosition(Vector2f(window_screen.getSize().x / 2, window_screen.getSize().y / 2));
	circle_s.setFillColor(Color::White);

	// Paddle objects
	Paddles pl1(12, 350);
	Paddles pl2(1388, 350);

	// Circle object
	Ball ball(window_screen.getSize().x / 2, window_screen.getSize().y / 2);

	// Score
	Text score1;
	score1.setPosition(350, 10);
	score1.setFont(font);
	score1.setString("0");
	score1.setCharacterSize(60);
	score1.setFillColor(Color::White);
	score1.setOutlineThickness(2);
	score1.setOutlineColor(Color::Black);

	Text score2;
	score2.setPosition(1050, 10);
	score2.setFont(font);
	score2.setString("0");
	score2.setCharacterSize(60);
	score2.setFillColor(Color::White);
	score2.setOutlineThickness(2);
	score2.setOutlineColor(Color::Black);

	int player_sc1 = score_1;
	ostringstream scoreStream1;
	scoreStream1 << player_sc1;
	score1.setString(scoreStream1.str());      // int into string

	int player_sc2 = score_2;
	ostringstream scoreStream2;
	scoreStream2 << player_sc2;
	score2.setString(scoreStream2.str());      // int into string


	// Create the stopwatch text
	Text stopwatchText;
	stopwatchText.setFont(font);
	stopwatchText.setCharacterSize(30);
	stopwatchText.setFillColor(Color::White);
	stopwatchText.setPosition(1300, 5);

	stringstream ss(elapsed_time_str);
	char delimiter;
	ss >> mins >> delimiter >> secs;

	// Get the start time of the stopwatch 
	auto start_time = chrono::high_resolution_clock::now() - chrono::minutes(mins) - chrono::seconds(secs);


	srand(time(NULL));
	vector<PowerUp> powerUps;           // Object Arrays of Power Ups

	Clock powerUpClock;          // Clock to track time since last power-up spawn
	Clock resetpowerUpClock;     // Clock to track time since last power-up spawn


	Game* onlyptr;


	while (window_screen.isOpen())
	{
		Event event;
		while (window_screen.pollEvent(event))
		{
			//  Closing Conditions
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window_screen.close();
			}
		}

		// Update Paddle 1
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			pl1.velocity.y = -17.0f;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			pl1.velocity.y = 17.0f;
		}
		else
		{
			pl1.velocity.y = 0.f;
		}
		// Update Paddle 2
		if (type == false)
		{
			// computer ...........
			pl2.shape.setPosition(1388, ball.getY() - 10);

		}
		else if (type == true)
		{
			// Multiplayer ...........
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				pl2.velocity.y = -17.0f;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				pl2.velocity.y = 17.0f;
			}
			else
			{
				pl2.velocity.y = 0.f;
			}
		}

		// Update Ball
		if (ball.shape.getGlobalBounds().intersects(pl1.shape.getGlobalBounds()))
		{
			sound.play();
			ball.velocity.x = abs(ball.velocity.x);
		}
		else if (ball.shape.getGlobalBounds().intersects(pl2.shape.getGlobalBounds()))
		{
			sound.play();
			ball.velocity.x = -abs(ball.velocity.x);
		}

		onlyptr = &pl1;
		onlyptr->upDate();
		onlyptr = &pl2;	
		onlyptr->upDate();
		onlyptr = &ball;	
		onlyptr->upDate();



		// update score 
		if (ball.getRight() > 1400)
		{
			vibrate.play();

			sleep(seconds(1));
			ball.shape.setPosition(window_screen.getSize().x / 2, window_screen.getSize().y / 2);
			player_sc1++;
			scoreStream1.str(""); // Clear the stringstream
			scoreStream1 << player_sc1;
			score1.setString(scoreStream1.str());
		}
		if (ball.getLeft() < 0)
		{
			vibrate.play();

			sleep(seconds(1));
			ball.shape.setPosition(window_screen.getSize().x / 2, window_screen.getSize().y / 2);
			player_sc2++;
			scoreStream2.str(""); // Clear the stringstream
			scoreStream2 << player_sc2;
			score2.setString(scoreStream2.str());
		}

		window_screen.clear(Color::Black);

		if (player_sc1 == 10 || player_sc2 == 10)
		{
			cout << "------ The End -----" << endl;
			cout << "Score of 1 " << player_sc1 << endl;
			cout << "Score of 2 " << player_sc2 << endl;

			gameover(type, font, player_sc1, player_sc2, score1, score2);
			window_screen.close();
		}


		
		// Calculate the elapsed time since the start of the stopwatch
		auto current_time = chrono::high_resolution_clock::now();
		auto elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time);

		// Format the elapsed time as a string
		stringstream stopwatch;
		stopwatch << setw(2) << setfill('0') << elapsed_time.count() / 60 << ":" << setw(2) << setfill('0') << elapsed_time.count() % 60;
		stopwatchText.setString(stopwatch.str());


		//if (stopwatch.str() == "00:03")      // update after some time (01:50)
		//{
		//    ball.velocity.x += .8;
		//    ball.velocity.y += .8;
		//    ball.velocity.x += 0.4f;
		//    ball.velocity.y += 1;
		//}


		if (powerUpClock.getElapsedTime().asSeconds() > 30.f)   // power-up every 30 seconds
		{
			powerUps.push_back(PowerUp());
			powerUpClock.restart();
		}

		if (resetpowerUpClock.getElapsedTime().asSeconds() > 10.f)  // Check if power-up has expired paddle return to orignal
		{
			pl1.resetSize();
			pl2.resetSize();
		}

		for (auto Boostball = powerUps.begin(); Boostball != powerUps.end(); )
		{
			Boostball->update();
			if (Boostball->collidesWithPaddle(pl1.shape.getGlobalBounds()))
			{
				sound2.play();
				pl1.shape.setSize(Vector2f(pl1.shape.getSize().x, pl1.shape.getSize().y * 1.5f));
				pl1.shape.setOrigin(pl1.shape.getSize() / 2.f);
				pl1.shape.setFillColor(Color::Magenta);
				Boostball = powerUps.erase(Boostball);
				resetpowerUpClock.restart();
			}
			else if (Boostball->collidesWithPaddle(pl2.shape.getGlobalBounds()))
			{
				sound2.play();
				pl2.shape.setSize(Vector2f(pl2.shape.getSize().x, pl2.shape.getSize().y * 1.5f));
				pl2.shape.setOrigin(pl2.shape.getSize() / 2.f);
				pl2.shape.setFillColor(Color::Magenta);
				Boostball = powerUps.erase(Boostball);
				resetpowerUpClock.restart();
			}
			else if (Boostball->shape.getPosition().y > window_screen.getSize().y + Boostball->shape.getRadius())
			{
				Boostball = powerUps.erase(Boostball);
			}
			else
			{
				++Boostball;
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			ofstream write("savegame.txt");
			write << player_sc1 << " " << player_sc2 << endl;
			write << stopwatch.str() << endl;

			window_screen.close();
			write.close();
		}


		// Display && Draw
		window_screen.draw(sprite1);
		window_screen.draw(score1);
		window_screen.draw(score2);
		window_screen.draw(stopwatchText);

		window_screen.draw(pl1.shape);
		window_screen.draw(pl2.shape);
		window_screen.draw(line);
		window_screen.draw(circle_s);
		window_screen.draw(ball.shape);

		for (auto Boostball = powerUps.begin(); Boostball != powerUps.end(); ++Boostball)
		{
			window_screen.draw(Boostball->shape);
		}

		window_screen.display();
	}
}
void rules(Music& Musicbg)
{
	RenderWindow window_screen(VideoMode(1400, 800), "Instructions", Style::None);
	Texture Texturebg;
	if (!Texturebg.loadFromFile("Texture/Rules.jpg"))
	{
		cout << "Failed to load image\n";
	}
	Sprite Spritebg(Texturebg);
	Spritebg.setScale(Vector2f(1.08, 1.1));


	while (window_screen.isOpen())
	{
		Event event;
		while (window_screen.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window_screen.close();
				funcmainmenu(Musicbg);

			}
		}
		window_screen.clear();
		window_screen.draw(Spritebg);
		window_screen.display();
	}
}
void bgchange(Music& Musicbg) 
{

	RenderWindow window_screen(VideoMode(1400, 800), "Change Background", Style::None);
	Texture Texturebg;
	if (!Texturebg.loadFromFile("Texture/background2.jpeg"))
	{
		cout << "Failed to load image\n";
	}
	Sprite Spritebg(Texturebg);
	Spritebg.setScale(Vector2f(1, 1));


	while (window_screen.isOpen())
	{
		Event event;
		while (window_screen.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window_screen.close();
			}
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Num1)
				{
					window_screen.close();
					setbg(1);
					funcnewgamemenu(Musicbg);
				}
				else if (event.key.code == Keyboard::Num2)
				{
					window_screen.close();
					setbg(2);
					funcnewgamemenu(Musicbg);
				}
				else if (event.key.code == Keyboard::Num3)
				{
					window_screen.close();
					setbg(3);
					funcnewgamemenu(Musicbg);
				}
				else if (event.key.code == Keyboard::Num4)
				{
					window_screen.close();
					setbg(4);
					funcnewgamemenu(Musicbg);
				}
				else if (event.key.code == Keyboard::Num5)
				{
					window_screen.close();
					setbg(5);
					funcnewgamemenu(Musicbg);
				}
				else if (event.key.code == Keyboard::Escape)
				{
					window_screen.close();
					funcmainmenu(Musicbg);
				}
			}
		}

		window_screen.clear();
		window_screen.draw(Spritebg);
		window_screen.display();
	}
}
void gameover(bool type, Font font, int player_sc1,int player_sc2,Text score1,Text score2)
{
	RenderWindow window_screen(VideoMode(1400, 800), "GameOver", Style::None);
	window_screen.setFramerateLimit(60);


	Texture backpic;
	backpic.loadFromFile("Texture/1.png");
	Sprite sprite1(backpic);
	sprite1.setScale(Vector2f(.9, .9));

	Texture scorepic;
	scorepic.loadFromFile("Texture/2.png");
	Sprite sprite2(scorepic);
	sprite2.setScale(Vector2f(.9, .9));

	SoundBuffer gameend;
	gameend.loadFromFile("Audios/gameover.wav");
	Sound gameover(gameend);
	gameover.play();



	score1.setPosition(1280, 480);
	score1.setCharacterSize(90);

	score2.setPosition(1280, 640);
	score2.setCharacterSize(90);

	ostringstream scoreStream1;
	scoreStream1 << player_sc1;
	score1.setString(scoreStream1.str());      // int into string

	ostringstream scoreStream2;
	scoreStream2 << player_sc2;
	score2.setString(scoreStream2.str());      // int into string

	Clock gamescreentime;
	gamescreentime.restart();

	while (window_screen.isOpen())
	{
		Event event;
		while (window_screen.pollEvent(event))
		{
			//  Closing Conditions
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) //||
			{
				window_screen.close();

			}
		}

		window_screen.clear(Color::Black);

		if (gamescreentime.getElapsedTime().asSeconds() > 2.f)
		{
			gameover.pause();
			window_screen.draw(sprite2);
			window_screen.draw(score1);
			window_screen.draw(score2);
		}
		else
		{
			window_screen.draw(sprite1);
		}

		window_screen.display();
	}

}
void setbg(int temp)
{
	tempbg = temp;
}
int getbg()
{
	return tempbg;
}