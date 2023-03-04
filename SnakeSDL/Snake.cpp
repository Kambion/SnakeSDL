#include "Snake.hpp"


void Timer::tick() {
	t2 = SDL_GetTicks();
	delta = (1. * t2 - t1) * 0.001;
	t1 = t2;

	worldTime += delta;

	fpsTimer += delta;
	if (fpsTimer > 0.5) {
		fps = frames * 2.;
		frames = 0;
		fpsTimer -= 0.5;
	}
	frames++;
}

void Snake::init(int startX, int startY, int boardSizeX, int boardSizeY, Timer& timer, bool **board) {
	this->timer = timer;
	boardX = boardSizeX;
	boardY = boardSizeY;
	this->board = board;
	body.push_front({ startX-2, startY });
	body.push_front({ startX-1, startY });
	body.push_front({ startX, startY });
	headPos = { startX, startY };
	for (Point part : body) {
		board[part.x][part.y] = true;
	}
	heading = Direction::RIGHT;
}

void Snake::draw(SDLWindow& window) {
	for (Point part : body)
		window.drawRectangle({ part.x * 10 + 50, part.y * 10 + 50, 10, 10 }, window.mapColor(0xFF0000));
}

void Snake::increaseLength() {
	Point temp = body.back();
	body.push_back(temp);
}


void Snake::move() {
	if (timer.worldTime - moveTime >= speed) {
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
		Point removed = body.back();
		board[removed.x][removed.y] = false;
		body.pop_back();
		if (board[headPos.x][headPos.y])
			lost = true;
		body.push_front(headPos);
		moveTime = timer.worldTime;
		for (Point part : body) {
			board[part.x][part.y] = true;
		}
	}
}

void Snake::setDirection(Direction dir) {
	heading = dir;
}