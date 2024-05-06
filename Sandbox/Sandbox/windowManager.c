#include "windowManager.h"
#include "box.h"

sfSprite* windowSprite;
sfTexture* windowTexture;

Window* windowSetup()
{
	Window* window = malloc(sizeof(Window));
	sfVideoMode mode = { WINDOW_LENGTH, WINDOW_HEIGHT, 32 };
	window->renderWindow = sfRenderWindow_create(mode, "Sandbox", sfDefaultStyle, NULL);
	window->renderTexture = sfRenderTexture_create(WINDOW_LENGTH, WINDOW_HEIGHT, sfFalse);
	window->isDone = sfFalse;

	return window;
}

void initWindow()
{
	windowSprite = sfSprite_create();
	windowTexture = sfTexture_create(WINDOW_LENGTH, WINDOW_HEIGHT);

	initTools();

	initBox();
}

void updateWindow(Window* _window)
{
	restartClock();

	sfEvent event;

	while (sfRenderWindow_pollEvent(_window->renderWindow, &event))
	{
		if (event.type == sfEvtClosed || event.mouseButton.button == sfMouseMiddle)
			_window->isDone = sfTrue;
	}

	updateBox(_window);
}

void displayWindow(Window* _window)
{
	sfRenderWindow_clear(_window->renderWindow, sfBlack);
	sfRenderTexture_clear(_window->renderTexture, sfBlack);

	displayBox(_window);

	sfRenderTexture_display(_window->renderTexture);
	sfSprite_setTexture(windowSprite, sfRenderTexture_getTexture(_window->renderTexture), sfTrue);
	sfRenderWindow_drawSprite(_window->renderWindow, windowSprite, NULL);

	sfRenderWindow_display(_window->renderWindow);
}

sfBool isDone(Window* _window)
{
	return _window->isDone;
}
