#pragma once
#include <iostream>
#include "Snake.hpp"


class Game {
public:
	Game();
	~Game();
private:
	int boardX = 90;
	int boardY = 90;
	Point bonus{ 0,0 };
	bool active = true;
	SDLWindow window{ WIDTH, HEIGHT, "Snake" };
	Snake snake{ timer };
public:
	Timer timer;
	bool** board;
public:
	void run();
private:
	void handleBonus();
	void spawnBonus();
	void mainLoop();
	void event();
};

