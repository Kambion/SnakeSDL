#pragma once

#include "SDL_common.hpp"
#include <string_view>
#include <utility>

enum class Highlight { RED, GREEN, CIRCLE };
enum class Fonts {ARIAL, SANS, COMIC_SANS};

class SDLWindow {
private:	//niezmienne dla user(debil)
	static constexpr int pieceSize = 70;
	static constexpr int tileSize = 70;
	static constexpr int boardSize = 8;
	static constexpr char
		backgroundName[] = "background.bmp",
		charsetName[] = "cs8x8.bmp",
		piecesName[] = "pieces.bmp",
		piecesMinName[] = "pieces_min.bmp";

	int w, h;
	std::string_view title;

	SDL_Surface* screen = nullptr;
	SDL_Texture* scrtex = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr;

	struct {
		SDL_Surface
			* charset = nullptr;
	} images;
	struct {
		Uint32 white{}, light_gary{}, dark_gary{}, light_red{}, light_green{};
	} colors;
public: //user(debil) może popsuć
	SDLWindow(int width, int height, std::string_view title);

	static constexpr int pieceSizeMin = 35;

	inline int width() const { return w; } 
	inline int height() const { return h; }
	inline std::string_view windowTitle() const { return title; }

	Uint32 mapColor(int rgb) const;

	void drawPixel(int x, int y, Uint32 color);
	void drawString(int x, int y, std::string text, int fontSize, Fonts fontName, SDL_Color color);
	void drawLine(int x, int y, int l, int dx, int dy, Uint32 color);
	void drawRectangle(SDL_Rect rect, Uint32 fillColor);
	void drawRectangle(SDL_Rect rect, int thickness, Uint32 outlineColor, Uint32 fillColor);
	void drawCircle(int x, int y, int radius, int thickness, Uint32 fillColor);
	void update();

	~SDLWindow(); 
private:
	bool loadImages();
	void initColors();
};
