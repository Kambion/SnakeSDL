#pragma once
#include "SDLgraphics.hpp"
#include <list>

static constexpr int WIDTH = 1000;
static constexpr int HEIGHT = 1000;

struct Timer {
	int t1, t2 = 0, frames = 0, lastState = 0;
	double delta = 0, worldTime = 0, fpsTimer = 0, fps = 0;

	Timer() : t1(SDL_GetTicks()) {}

	void tick();
};

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Point {
	int x;
	int y;
	bool operator == (Point& other) {
		return (x == other.x && y == other.y);
	}
};



class Snake {
public:
	Snake(Timer& timer) : timer(timer) {}
	void init(int startX, int startY, int boardSizeX, int boardSizeY, Timer& timer, bool** board);
	void draw(SDLWindow& window);
	void move();
	void setDirection(Direction dir);
	Point& getHeadPosition() { return headPos; }
	void increaseLength();
	bool lost = false;
private:
	double speed = 0.3;
	double moveTime = 0;
	Timer& timer;
	bool** board;
	Direction heading;
	std::list<Point> body;
	int boardX;
	int boardY;
	Point headPos;
};