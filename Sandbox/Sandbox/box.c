#include "box.h"

typedef struct {
	sfVector2f pos;
	Types type;
	float moveTimer;
}Block;
Block b[BLOCK_Y_RATIO][BLOCK_X_RATIO];

typedef enum {
	GO_BOTTOM_LEFT,
	GO_BOTTOM_RIGHT,
}Go;

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
	static float dropTimer = 0.f;
	float dt = getDeltaTime();
	dropTimer += dt;

	if (dropTimer > -0.2f && sfRenderWindow_hasFocus(_window->renderWindow) && sfMouse_isButtonPressed(sfMouseLeft))
	{
		dropTimer = 0.f;
		sfVector2f mousePos = getfMousePos(_window->renderWindow);
		mousePos = MultiplyVector2f(mousePos, 1.f / BLOCK_SCALE);
		sfVector2i iMousePos = V2fToV2i(mousePos);
		if (isInBounds(iMousePos)) {
			b[iMousePos.y][iMousePos.x].type = SAND;
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
					if (!isSolid(j + 1, i)) {
						b[j][i].moveTimer += dt;
						if (b[j][i].moveTimer > 0.1f) {
							changeBlock(NO_TYPE, j, i);
							changeBlock(SAND, j + 1, i);
						}
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

sfBool isInBounds(sfVector2i _v)
{
	if (_v.x < 0 || _v.y < 0 || _v.x >= BLOCK_X_RATIO || _v.y >= BLOCK_Y_RATIO)
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
