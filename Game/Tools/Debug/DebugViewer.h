#ifndef DEBUG_VIEWER_H
#define DEBUG_VIEWER_H

#include "../Common.h"

#define CLEAR_FPS_TIME 10.f
// Classe d'utilitaires de debug (affichage FPS, logs, print d'objets simples, timers)
class DebugViewer
{
	// SFML texts / background
	sf::Text fps;
	sf::Text maxFps;
	sf::Text avgFps;
	sf::Text minFps;
	sf::RectangleShape fpsBackground;

	sf::Text nbOfParticles;

	// toggles
	bool isFps = false;
	bool isFpsDetails = false;

	// fps stats
	int maxFpsValue = 0;
	int minFpsValue = 0;
	float totalFps = 0.f;
	int avgFpsValue = 0;
	int frameCount = 0;
	float clearTime = 0.f;

public:
	// Initialisation, update and draw (noms raccourcis)
	void Init(sf::Font& font);
	void Update(float dt);
	void Draw(sf::RenderWindow& window, sf::Shader& shader);	
	void Draw(sf::RenderWindow& window);	

	// FPS
	void ToggleFPS(); // bascule l'affichage FPS
	//void UpdateNbParticle(int _nb);
private:
	void UpdateFPS(float _dt);
	void ClearData();
	void UpdateSizeOfFpsBackground();
};
#endif // DEBUG_VIEWER_H

////////////////////////////////////////////////////
/// Developped by Alexandre Bosio //////////////////
////////////////////////////////////////////////////