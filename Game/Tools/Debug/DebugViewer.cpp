#include "DebugViewer.h"
void DebugViewer::Init(sf::Font& _font)
{

	fps = CreateText("Fps : 0", _font, 22, TOP_LEFT, sf::Vector2f(0, 0));
	maxFps = CreateText("Max Fps : 0", _font, 16, TOP_LEFT, sf::Vector2f(0, 28));
	avgFps = CreateText("Avg Fps : 0", _font, 16, TOP_LEFT, sf::Vector2f(0, 45));
	minFps = CreateText("Min Fps : 0", _font, 16,TOP_LEFT, sf::Vector2f(0, 65));

	fps.setCharacterSize(20);
	maxFps.setCharacterSize(14);
	avgFps.setCharacterSize(14);
	minFps.setCharacterSize(14);

	isFps = false;
	isFpsDetails = false;

	fpsBackground.setFillColor(sf::Color(0, 0, 0, 100));
	UpdateSizeOfFpsBackground();
}

void DebugViewer::Update(float _dt)
{
	UpdateFPS(_dt);
	clearTime += _dt;
	if (clearTime > CLEAR_FPS_TIME)
	{
		ClearData();
	}
}

void DebugViewer::Draw(sf::RenderWindow& _window, sf::Shader& shader)
{
	if (isFps)
	{
		_window.draw(fpsBackground, &shader);
		_window.draw(fps, &shader);
	}
	if (isFpsDetails)
	{
		_window.draw(maxFps, &shader);
		_window.draw(avgFps, &shader);
		_window.draw(minFps, &shader);
	}
}

void DebugViewer::Draw(sf::RenderWindow& _window)
{
	if (isFps)
	{
		_window.draw(fpsBackground);
		_window.draw(fps);
	}
	if (isFpsDetails)
	{
		_window.draw(maxFps);
		_window.draw(avgFps);
		_window.draw(minFps);
	}
}

void DebugViewer::ToggleFPS(void)
{
	if (!isFps && !isFpsDetails)
	{
		isFps = true;
	}
	else if (isFps && !isFpsDetails)
	{
		isFpsDetails = true;
	}
	else
	{
		isFps = false;
		isFpsDetails = false;
	}

	UpdateSizeOfFpsBackground();
}

void DebugViewer::UpdateFPS(float _dt)
{
	if (isFps)
	{
		int currentFps = static_cast<int>(1.f / _dt);
		SetText(fps, "Fps : " + std::to_string(currentFps));

		// Update max fps
		if (currentFps > maxFpsValue)
		{
			maxFpsValue = currentFps;
			SetText(maxFps, "Max Fps : " + std::to_string(maxFpsValue));
		}

		// Update min fps
		if (minFpsValue == 0 || currentFps < minFpsValue)
		{
			minFpsValue = currentFps;
			SetText(minFps, "Min Fps : " + std::to_string(minFpsValue));
		}

		// Update average fps
		totalFps += currentFps;
		frameCount++;
		avgFpsValue = static_cast<int>(totalFps / frameCount);
		SetText(avgFps, "Avg Fps : " + std::to_string(avgFpsValue));
	}
}

void DebugViewer::ClearData()
{
	clearTime = 0.f;
	totalFps = 0.f;
	frameCount = 0;
	maxFpsValue = 0;
	minFpsValue = 0;
}

void DebugViewer::UpdateSizeOfFpsBackground()
{
	if (isFpsDetails)
	{
		fpsBackground.setSize(sf::Vector2f(150.f, 95.f));
	}
	else
	{
		fpsBackground.setSize(sf::Vector2f(150.f, 34.f));
	}

	fpsBackground.setPosition(12.f, 17.f);
}

//void Debug::StartTimer(const std::string& id)
//{
//	timers[id] = std::chrono::high_resolution_clock::now();
//}
//
//double Debug::StopTimer(const std::string& id)
//{
//	auto it = timers.find(id);
//	if (it == timers.end())
//	{
//		return -1.0;
//	}
//	auto startTime = it->second;
//	auto endTime = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double, std::milli> duration = endTime - startTime;
//	timers.erase(it);
//	return duration.count();
//}
