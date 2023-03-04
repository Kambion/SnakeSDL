#include "Game.hpp"

Snake::Snake(int startX, int startY, int boardSizeX, int boardSizeY) {
	body.push_front({ startX, startY });
	headPos = { startX, startY };
	boardX = boardSizeX;
	boardY = boardSizeY;
	heading = Direction::RIGHT;
}

void Snake::draw(SDLWindow &window) {
	for(Point part : body)
		window.drawRectangle({ part.x*10 + 250, part.y*10 + 250, 10, 10 }, window.mapColor(0xFF0000));
}

void Snake::move() {
	switch (heading)
	{
	case Direction::UP:
		headPos.y = (headPos.y - 1) % boardY;
		if (headPos.y < 0) headPos.y = boardY - 1;
		break;
	case Direction::DOWN:
		headPos.y = (headPos.y + 1) % boardY;
		if (headPos.y >= boardY) headPos.y = 0;
		break;
	case Direction::LEFT:
		headPos.x = (headPos.x - 1) % boardX;
		if (headPos.x < 0) headPos.x = boardX - 1;
		break;
	case Direction::RIGHT:
		headPos.x = (headPos.x + 1) % boardX;
		if (headPos.x >= boardX) headPos.x = 0;
		break;
	}
	body.pop_back();
	body.push_front(headPos);
}

void Game::run() {
	window.drawRectangle({ 0, 0, WIDTH, HEIGHT }, window.mapColor(0x666666));
	mainLoop();
}

void Game::mainLoop() {
	while (active)
	{
		window.drawRectangle({ 0, 0, WIDTH, HEIGHT }, window.mapColor(0x666666));
		event();
		snake.move();
		snake.draw(window);
		window.update();
	}
}

void Snake::setDirection(Direction dir) {
	heading = dir;
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