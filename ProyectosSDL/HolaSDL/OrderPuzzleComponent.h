#pragma once
#include "Component.h"
#include <vector>
#include "Texture.h"
#include "ResourceManager.h"
#include "Game.h"
#include "checkML.h"


class OrderPuzzleController;

class OrderPuzzleComponent : public Component
{
private:

	enum clickState {normalMode, clickMode};

	struct coord {
		int x;
		int y;
	};

	struct piece {
		int currentPos;
		int correctPos;
		string text;
	};

	piece puzzle[5];
	SDL_Renderer* pRenderer = nullptr;
	ResourceManager* resource = nullptr;

	clickState state = clickState::normalMode;

	int pulsedPiece1, pulsedPiece2;

	void switchPiece(int p1, int p2);
	bool compruebaVictoria();
	void desordena();

	int markSlot = 0;
	OrderPuzzleController* pc = nullptr;
	void renderMark(SDL_Rect DestRect);

	bool WinSound = false;
	bool desordenaSound = false;

	coord PosPieces[5]{ { 200,200 },{ 400,200 },{ 600,200 },{ 800,200 },{ 1000,200 } };

	Entity* puzzleEntity_;

public:
	OrderPuzzleComponent(Entity* puzzleEntity);
	~OrderPuzzleComponent();

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);

	void moveMarkSlot(int a);
	void clickMark();
};

