#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "SFML/Graphics.h"
#include <time.h>

#define WINDOW_LENGTH 800
#define WINDOW_HEIGHT 600

sfVector2f vector2f(float _x, float _y);
void initTools();
void restartClock();
float getDeltaTime();
