#pragma once
#include <iostream>
#include "Snake.hpp"

static constexpr int WIDTH = 1000;
static constexpr int HEIGHT = 1000;


class Game {
public:
	Game();
	~Game();
private:
	int boardX = (WIDTH-100)/squereSize;
	int boardY = (HEIGHT-100)/squereSize;
	int score = 0;
	Point bonus{ 0,0 };
	bool active = true;
	bool menu = true;
	SDLWindow window{ WIDTH, HEIGHT, "Snake" };
	Snake snake{ timer };
public:
	Timer timer;
	bool** board;
public:
	void run();
private:
	void initGame();
	void handleBonus();
	void spawnBonus();
	void mainLoop();
	void menuLoop();
	void event();
};

