#include "box.h"

typedef struct {
	sfVector2f pos;
	Types type;
	float moveTimer;
}Block;
Block b[BLOCK_Y_RATIO][BLOCK_X_RATIO];

typedef enum {
	DIR_NO_DIR,
	DIR_BOTTOM,
	DIR_BOTTOM_LEFT,
	DIR_BOTTOM_RIGHT
}Direction;

sfRectangleShape* boxRectangle;

void initBox()
{
	for (int j = 0; j < BLOCK_Y_RATIO; j++)
	{
		for (int i = 0; i < BLOCK_X_RATIO; i++)
		{
			b[j][i].pos = vector2f((float)i * BLOCK_SCALE, (float)j * BLOCK_SCALE);
			b[j][i].type = NO_TYPE;
			b[j][i].moveTimer = 0.f;
		}
	}

	boxRectangle = sfRectangleShape_create();
	sfRectangleShape_setSize(boxRectangle, vector2f(BLOCK_SCALE, BLOCK_SCALE));
	sfRectangleShape_setOrigin(boxRectangle, vector2f(0.f, 0.f));
}

void updateBox(Window* _window)
{
	float dt = getDeltaTime();

	if (sfRenderWindow_hasFocus(_window->renderWindow) && sfMouse_isButtonPressed(sfMouseLeft))
	{
		sfVector2f mousePos = getfMousePos(_window->renderWindow);
		mousePos = MultiplyVector2f(mousePos, 1.f / BLOCK_SCALE);
		sfVector2i iMousePos = V2fToV2i(mousePos);
		if (isInBounds(iMousePos.y, iMousePos.x)) {
			if (b[iMousePos.y][iMousePos.x].type == NO_TYPE) {
				b[iMousePos.y][iMousePos.x].type = SAND;
			}
		}
	}

	for (int j = 0; j < BLOCK_Y_RATIO; j++)
	{
		for (int i = 0; i < BLOCK_X_RATIO; i++)
		{
			switch (b[j][i].type)
			{
			case SAND:
				if (j + 1 < BLOCK_Y_RATIO) {
					Direction sandDir = DIR_NO_DIR;
					sfVector2i target = vector2i(i, j);
					if (!isSolid(j + 1, i)) {
						sandDir = DIR_BOTTOM;
						target = vector2i(i, j + 1);

					}
					if (b[j + 1][i].type == SAND && isInBounds(j + 1, i - 1)) {
						if (!isSolid(j + 1, i - 1)) {
							sandDir = DIR_BOTTOM_LEFT;
							target = vector2i(i - 1, j + 1);
						}
					}
					if (b[j + 1][i].type == SAND && isInBounds(j + 1, i + 1)) {
						if (!isSolid(j + 1, i + 1)) {
							if (sandDir == DIR_BOTTOM_LEFT) {
								int sandRandom = rand() % 2;
								if (sandRandom == 0) {
									sandDir = DIR_BOTTOM_RIGHT;
									target = vector2i(i + 1, j + 1);
								}
							}
							else {
								target = vector2i(i + 1, j + 1);
								sandDir = DIR_BOTTOM_RIGHT;
							}
						}
					}

					b[j][i].moveTimer += dt;
					if (b[j][i].moveTimer > 0.02f) {
						changeBlock(NO_TYPE, j, i);
						changeBlock(SAND, target.y, target.x);
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void displayBox(Window* _window)
{
	for (int j = 0; j < BLOCK_Y_RATIO; j++)
	{
		for (int i = 0; i < BLOCK_X_RATIO; i++)
		{
			switch (b[j][i].type)
			{
			case NO_TYPE: sfRectangleShape_setFillColor(boxRectangle, sfBlack); break;
			case SAND: sfRectangleShape_setFillColor(boxRectangle, sfYellow); break;
			default:
				sfRectangleShape_setFillColor(boxRectangle, sfBlack);
				break;
			}
			sfRectangleShape_setPosition(boxRectangle, b[j][i].pos);
			sfRenderTexture_drawRectangleShape(_window->renderTexture, boxRectangle, NULL);
		}
	}

	sfRectangleShape_setFillColor(boxRectangle, sfYellow);
	sfVector2f mousePos = getfMousePos(_window->renderWindow);
	mousePos = MultiplyVector2f(mousePos, 1.f / BLOCK_SCALE);
	mousePos = V2iToV2f(MultiplyVector2i(V2fToV2i(mousePos), BLOCK_SCALE));
	sfRectangleShape_setPosition(boxRectangle, mousePos);
	sfRenderTexture_drawRectangleShape(_window->renderTexture, boxRectangle, NULL);
}

sfBool isInBounds(int _j, int _i)
{
	if (_i < 0 || _j < 0 || _i >= BLOCK_X_RATIO || _j >= BLOCK_Y_RATIO)
		return sfFalse;

	return sfTrue;
}

sfBool isSolid(int _j, int _i)
{
	switch (b[_j][_i].type)
	{
	case NO_TYPE:
		return sfFalse;
	case SAND:
		return sfTrue;
	default:
		break;
	}
	return sfFalse;
}

void changeBlock(Types _type, int _j, int _i)
{
	b[_j][_i].type = _type;
	b[_j][_i].moveTimer = 0.f;
}
