#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
const int Max_main_menu =4;
class MainMenu;//Forward Declaration
class Paddles;


class MainMenu 
{
private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
public:
    MainMenu(float width, float height);
    MainMenu();
    void draw(RenderWindow& window);
    void moveup();
    void movedown();
    int MainMenuPressed() {
        return MainMenuSelected;
    }
    ~MainMenu();
};

class Game
{

public:
    virtual void upDate() = 0; // Absteact Classes
    virtual float getX() = 0;
    virtual float getY() = 0;
    virtual float getLeft() = 0;
    virtual float getRight() = 0;
    virtual float getTop() = 0;
    virtual float getBottom() = 0;
};

class Paddles:public Game
{
public:
    RectangleShape shape;
    Vector2f velocity{ 0,5 };
    float speedIncrease = 0.5f;        // Increase speed by this amount every minute
    Clock clock;                       // Clock to keep track of time

    Paddles(float x, float y);
    float getX();
    float getY();
    float getLeft();
    float getRight();
    float getTop();
    float getBottom();
    void upDate();
    void resetSize();
};

class Ball:public Game
{
    int radius = 10;

public:
    CircleShape shape;
    Vector2f velocity{ 10.f, 4.f };
    float speedIncrease = 0.5f;        // Increase speed by this amount every minute
    Clock clock;                       // Clock to keep track of time

    Ball(float x, float y);
    float getX();
    float getY();
    float getLeft();
    float getRight();
    float getTop();
    float getBottom();
    void upDate();
};

class PowerUp
{
public:
    CircleShape shape;
    Vector2f velocity{ 3.f, 0.f };
    int direct;                    // direction either for player 1 or for player 2 for larger paddle

    PowerUp();
    void update();
    bool collidesWithPaddle(FloatRect paddleBounds);
}; 