#include "tools.h"

sfTime sftime;
sfClock* sfclock;

sfVector2f vector2f(float _x, float _y)
{
	sfVector2f v = { _x, _y };
	return v;
}

void initTools()
{
	sfclock = sfClock_create();
	srand(time(NULL));
}

void restartClock()
{
	sftime = sfClock_restart(sfclock);
}

float getDeltaTime()
{
	float dt = sfTime_asSeconds(sftime);
	if (dt > 0.1f)
		return 0.1f;

	return dt;
}