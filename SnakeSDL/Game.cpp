#include "Game.hpp"
#include <string>

Game::Game() {
	board = new bool* [boardX];
	for (int i = 0; i < boardX; i++) {
		board[i] = new bool[boardY];
	}
}

Game::~Game() {
	for (int i = 0; i < boardX; i++) {
		delete[] board[i];
	}
	delete[] board;
}


void Game::run() {
	window.drawRectangle({ 0, 0, WIDTH, HEIGHT }, window.mapColor(0x666666));
	while (active) {
		menuLoop();
		initGame();
		mainLoop();
	}
}

void Game::mainLoop() {
	while (active && !snake.lost)
	{
		timer.tick();
		window.drawRectangle({ 0, 0, WIDTH, HEIGHT }, window.mapColor(0x666666));
		window.drawRectangle({ 40, 40, WIDTH-80, HEIGHT-80 }, 10, window.mapColor(0x0), window.mapColor(0x666666));
		event();
		snake.move();
		Point pos = snake.getHeadPosition();
		handleBonus();
		snake.draw(window);
		window.drawString(0, 0, std::to_string(uint64_t(timer.fps)), 10, Fonts::ARIAL, { 0, 255, 0, 255 });
		window.drawString(800, 10, "Score: " + std::to_string(score), 20, Fonts::ARIAL, {0, 255, 0, 255});
		window.update();
	}
	window.drawString(200, 450, "GAME OVER", 100, Fonts::ARIAL, { 0, 0, 0, 255 });
	window.update();
	menu = true;
	while (active && menu) {
		event();
	}
}
void Game::initGame() {
	score = 0;
	timer.worldTime = 0;
	for (int i = 0; i < boardX; i++) {
		for (int j = 0; j < boardY; j++) {
			board[i][j] = false;
		}
	}
	snake.init(boardX/2, boardY/2, boardX, boardY, timer, board);
	spawnBonus();
}

void Game::menuLoop() {
	menu = true;
	window.drawRectangle({ 0, 0, WIDTH, HEIGHT }, window.mapColor(0x666666));
	while (active && menu) {
		window.drawString(300, 100, "SNAKE", 100, Fonts::ARIAL, { 0, 255, 0, 255 });
		window.update();
		event();
	}

}

void Game::handleBonus() {
	if (snake.getHeadPosition() == bonus) {
		snake.increaseLength();
		score++;
		spawnBonus();
	}
	window.drawRectangle({ bonus.x * squereSize + 50, bonus.y * squereSize + 50, squereSize, squereSize }, window.mapColor(0x0000FF));
}

void Game::spawnBonus() {
	int counter = 0;
	for (int i = 0; i < boardX; i++) {
		for (int j = 0; j < boardY; j++) {
			if (!board[i][j]) counter++;
		}
	}
	if (counter > 0) {
		int random = rand() % counter + 1;
		for (int i = 0; i < boardX; i++) {
			for (int j = 0; j < boardY; j++) {
				if (!board[i][j]) random--;
				if (random == 0) {
					bonus = { i, j };
					return;
				}
			}
		}
	}
}

void Game::event() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				active = false;
				break;
			case SDLK_w:
			case SDLK_UP:
				snake.setDirection(Direction::UP);
				break;
			case SDLK_s:
			case SDLK_DOWN:
				snake.setDirection(Direction::DOWN);
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				snake.setDirection(Direction::RIGHT);
				break;
			case SDLK_a:
			case SDLK_LEFT:
				snake.setDirection(Direction::LEFT);
				break;
			case SDLK_SPACE:
				menu = false;
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_KEYUP:
			break;
		case SDL_QUIT:
			active = false;
			break;
		};
	};
}