#include "box.h"

typedef enum {
	NO_TYPE,
	SAND,
	WATER
}Types;

typedef struct {
	sfVector2f pos;
	Types type;
}Box;
Box b[WINDOW_LENGTH][WINDOW_HEIGHT];

sfRectangleShape* boxRectangle;

void initBox()
{
	for (int j = 0; j < WINDOW_HEIGHT; j++)
	{
		for (int i = 0; i < WINDOW_LENGTH; i++)
		{
			b[j][i].pos = vector2f((float)i, (float)j);
			b[j][i].type = NO_TYPE;
		}
	}

	boxRectangle = sfRectangleShape_create();
	sfRectangleShape_setSize(boxRectangle, vector2f(1.f, 1.f));
	sfRectangleShape_setOrigin(boxRectangle, vector2f(0.f, 0.f));
}

void updateBox(Window* _window)
{
	static float dropTimer = 0.f;
	float dt = getDeltaTime();
	dropTimer += dt;

	if (dropTimer > 0.2f && sfMouse_isButtonPressed(sfMouseLeft))
	{
		dropTimer = 0.f;
		sfVector2i iPos = sfMouse_getPositionRenderWindow(_window->renderWindow);
		b[iPos.y][iPos.x].type = SAND;
	}

	for (int j = 0; j < WINDOW_HEIGHT; j++)
	{
		for (int i = 0; i < WINDOW_LENGTH; i++)
		{

		}
	}
}

void displayBox(Window* _window)
{
	for (int j = 0; j < WINDOW_HEIGHT; j++)
	{
		for (int i = 0; i < WINDOW_LENGTH; i++)
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
}
