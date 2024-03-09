#include "Pong.h"
#include<iostream>
MainMenu::MainMenu(float width, float height)
{
    if (!font.loadFromFile("fonts/mainmenufont.otf"))
    {
        cout << "Font is not available";
    }
    //New game
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::Yellow);
    mainMenu[0].setString("Play Game");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(400, 250);
    //Load Game
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::Yellow);
    mainMenu[1].setString("Change Background");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(400, 350);
    //Change Bg
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::Yellow);
    mainMenu[2].setString("Rules");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(400, 450);
    //Quit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::Yellow);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(400, 550);

    MainMenuSelected = 0;
}
//for New game Menu
MainMenu::MainMenu()
{
    if (!font.loadFromFile("fonts/mainmenufont.otf"))
    {
        cout << "Font is not available";
    }
    //single player
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::Yellow);
    mainMenu[0].setString("Single Player");
    mainMenu[0].setCharacterSize(60);
    mainMenu[0].setPosition(550, 250);
    //Multi Player
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::Yellow);
    mainMenu[1].setString("Multiplayer");
    mainMenu[1].setCharacterSize(60);
    mainMenu[1].setPosition(550, 350);
    //Rules
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::Yellow);
    mainMenu[2].setString("Resume Game");
    mainMenu[2].setCharacterSize(60);
    mainMenu[2].setPosition(550, 450);
    //Go back
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::Yellow);
    mainMenu[3].setString("Go Back");
    mainMenu[3].setCharacterSize(60);
    mainMenu[3].setPosition(550, 550);

    MainMenuSelected = 0;
}
MainMenu::~MainMenu()
{

}
void MainMenu::draw(RenderWindow& window)
{
    for (int i = 0; i < Max_main_menu; i++)
    {
        window.draw(mainMenu[i]);
    }
}
void MainMenu::moveup()
{
    if (MainMenuSelected - 1 >= 0) {
        mainMenu[MainMenuSelected].setFillColor(Color::Yellow);
        MainMenuSelected--;
        mainMenu[MainMenuSelected].setFillColor(Color::White);
    }
}
void MainMenu::movedown() 
{
    if (MainMenuSelected + 1 < Max_main_menu) {
        mainMenu[MainMenuSelected].setFillColor(Color::Yellow);
        MainMenuSelected++;
        mainMenu[MainMenuSelected].setFillColor(Color::White);
    }
}

Paddles::Paddles(float x, float y)
{
    shape.setPosition(x, y);
    shape.setSize({ 20.f, 100.f });
    shape.setFillColor(Color::White);
    shape.setOrigin(shape.getSize() / 2.f);
}
float Paddles:: getX()
{
    return shape.getPosition().x;
}
float Paddles::getY()
{
    return shape.getPosition().y;
}
float Paddles::getLeft()
{
    return getX() - shape.getSize().x / 2.f;
}
float Paddles::getRight()
{
    return getX() + shape.getSize().x / 2.f;
}
float Paddles::getTop()
{
    return getY() - shape.getSize().y / 2.f;
}
float Paddles::getBottom()
{
    return getY() + shape.getSize().y / 2.f;
}
void Paddles::upDate()
{
    shape.move(velocity);

    if (getTop() < 0)
    {
        shape.setPosition(getX(), shape.getSize().y / 2.f);
    }
    else if (getBottom() > 800)
    {
        shape.setPosition(getX(), 800 - shape.getSize().y / 2.f);
    }

    //// Increase speed after 1 minute
    if (clock.getElapsedTime().asSeconds() > 40.f)
    {
        velocity += speedIncrease * velocity;
        clock.restart();
    }
}
void Paddles:: resetSize()
{
    shape.setSize({ 20.f, 100.f });
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setFillColor(Color::White);
}

Ball :: Ball(float x, float y)
{
    shape.setPosition(x, y);
    shape.setRadius(radius);
    shape.setFillColor(Color::Yellow);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setOutlineThickness(2);
    shape.setOutlineColor(Color::Black);
}
float Ball:: getX()
{
    return shape.getPosition().x;
}
float Ball:: getY()
{
    return shape.getPosition().y;
}
float Ball::getLeft()
{
    return getX() - shape.getRadius();
}
float Ball::getRight()
{
    return getX() + shape.getRadius();
}
float Ball::getTop()
{
    return getY() - shape.getRadius();
}
float Ball::getBottom()
{
    return getY() + shape.getRadius();
}
void  Ball::upDate()
{
    shape.move(velocity);

    // Check for collisions with the walls
    if (getLeft() < 0)
    {
        velocity.x = abs(velocity.x);
    }
    else if (getRight() > 1400)
    {
        velocity.x = -abs(velocity.x);
    }
    if (getTop() < 0)
    {
        velocity.y = abs(velocity.y);
    }
    else if (getBottom() > 800)
    {
        velocity.y = -abs(velocity.y);
    }

    // Increase speed after 1 minute
    if (clock.getElapsedTime().asSeconds() > 40.f)
    {
        velocity += speedIncrease * velocity;
        clock.restart();
    }
}

PowerUp::PowerUp()
{
    shape.setRadius(10.f);
    shape.setFillColor(Color::Green);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(700, rand() % 800 + 1);
    direct = rand() % 2 + 1;             // Randomly power-up for player 1 or player 2
}
void PowerUp:: update()
{
    shape.move(velocity);
    if (direct == 2)
    {
        velocity.x = -abs(velocity.x);
    }
}
bool PowerUp::collidesWithPaddle (FloatRect paddleBounds)
{
    return shape.getGlobalBounds().intersects(paddleBounds);
}