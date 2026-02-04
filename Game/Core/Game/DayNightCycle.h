#pragma once

#include "../../Tools/Common.h"

#define DAY_DURATION 20.f

class DayNightCycle
{
	private:
	float dayTimer = 0.f;
	sf::RectangleShape nightOverlay;
	int dayCount = 0;
	bool isNewDay = false;
	GameData* data = nullptr;
	void DayCountUpdate();
public:
	DayNightCycle(int _w, int _h);
	void Update(float _dt);
	void Draw(sf::RenderWindow& _render);
	bool GetIsNewDay(void);
	int GetDayCount();
};