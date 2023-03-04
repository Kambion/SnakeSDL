#include <iostream>
#include "SDLgraphics.hpp"
#include <list>

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Point {
	int x;
	int y;
};


class Snake {
public:
	Snake(int startX, int startY, int boardSizeX, int boardSizeY);
	void draw(SDLWindow& window);
	void move();
	void setDirection(Direction dir);
private:
	Direction heading;
	std::list<Point> body;
	int boardX;
	int boardY;
	Point headPos;
};

class Game {
private:
	static constexpr int WIDTH = 1000;
	static constexpr int HEIGHT = 1000;
	int boardX = 50;
	int boardY = 50;
	bool active = true;
	SDLWindow window{ WIDTH, HEIGHT, "Snake" };
	Snake snake{ 0,0, boardX, boardY };
public:
	void run();
private:
	void mainLoop();
	void event();
};

