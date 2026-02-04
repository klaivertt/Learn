#include "DayNightCycle.h"
#include "../../Tools/GameData.h"
#include "../../Tools/Debug/Logger.h"

void DayNightCycle::DayCountUpdate()
{
	dayCount++;
	isNewDay = true;
}

DayNightCycle::DayNightCycle(int _w, int _h)
{
	nightOverlay.setSize(sf::Vector2f(_w, _h));
	//data = GameData::GetInstance();
}

void DayNightCycle::Update(float _dt)
{
	if (isNewDay)
	{
		isNewDay = false;
	}
	dayTimer += _dt;
	//data->logger->Warning("day time : " + std::to_string(dayTimer), false);

	if (dayTimer > DAY_DURATION)
	{
		dayTimer -= DAY_DURATION;
		DayCountUpdate();
	}
	
	int opacity = static_cast<int>((cos(dayTimer * (2 * M_PI / DAY_DURATION)) + 1) * 75);
	nightOverlay.setFillColor(sf::Color(0, 0, 50, opacity));
}
void DayNightCycle::Draw(sf::RenderWindow& _render)
{
	_render.draw(nightOverlay);
}

bool DayNightCycle::GetIsNewDay(void)
{
	return isNewDay;
}

int DayNightCycle::GetDayCount()
{
	return dayCount;
}
