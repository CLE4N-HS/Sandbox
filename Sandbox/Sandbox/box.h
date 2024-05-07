#pragma once
#include "tools.h"
#include "windowManager.h"

#define BLOCK_SCALE 5

#define BLOCK_X_RATIO (WINDOW_LENGTH / BLOCK_SCALE)
#define BLOCK_Y_RATIO (WINDOW_HEIGHT / BLOCK_SCALE)

typedef enum {
	NO_TYPE,
	SAND,
	WATER
}Types;

void initBox();
void updateBox(Window* _window);
void displayBox(Window* _window);
sfBool isInBounds(int _j, int _i);
sfBool isSolid(int _j, int _i);
void changeBlock(Types _type, int _j, int _i);