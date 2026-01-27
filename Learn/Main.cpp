#include "Common.h"
#include <vector>

// Tools
int Rand(int _min, int _max)
{
	return rand() % (_max - _min + 1) + _min;
}

float RandF(float _min, float _max)
{
	return _min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (_max - _min)));
}

struct Vec2
{
	float x = 0;
	float y = 0;
};

// Class
class Particle
{
public:
	Particle()
	{
		Reset();
	}
	~Particle()
	{
	}

	void Load(void)
	{
		// Position de départ (centre-bas)
		pos = Vec2{VIEW_GRID_X / 2.0f, VIEW_GRID_Y - 2.0f};
		
		// Vélocité initiale aléatoire
		velocity.x = RandF(-3.0f, 3.0f);
		velocity.y = RandF(-8.0f, -12.0f); // Force initiale vers le haut
		
		// Propriétés physiques
		gravity = RandF(0.3f, 0.5f);
		drag = RandF(0.96f, 0.99f);
		lifetime = Rand(30, 60);
		age = 0;
		
		// Apparence
		char particles[] = {'*', '+', 'o', '.', '~', '^'};
		symbol = particles[rand() % 6];
	}

	void Update(void)
	{
		// Physique
		velocity.y += gravity; // Gravité
		velocity.x *= drag;    // Friction de l'air
		velocity.y *= drag;
		
		// Déplacement
		pos.x += velocity.x * 0.1f;
		pos.y += velocity.y * 0.1f;
		
		// Rebond sur les bords latéraux
		if (pos.x < 0)
		{
			pos.x = 0;
			velocity.x = -velocity.x * 0.5f; // Perte d'énergie
		}
		if (pos.x >= VIEW_GRID_X)
		{
			pos.x = VIEW_GRID_X - 1;
			velocity.x = -velocity.x * 0.5f;
		}
		
		// Rebond sur le sol
		if (pos.y >= VIEW_GRID_Y - 1)
		{
			pos.y = VIEW_GRID_Y - 1;
			velocity.y = -velocity.y * 0.4f; // Rebond avec perte d'énergie
			
			// Si la vélocité est trop faible, la particule "meurt"
			if (abs(velocity.y) < 0.5f)
			{
				age = lifetime;
			}
		}
		
		age++;
	}

	bool IsDead(void)
	{
		return age >= lifetime || pos.y < 0;
	}

	Vec2 GetPos(void)
	{
		return pos;
	}
	
	char GetSymbol(void)
	{
		// Change de symbole selon l'âge
		if (age > lifetime * 0.75f)
			return '.';
		return symbol;
	}

	void Reset()
	{
		Load();
	}

private:
	Vec2 pos = {};
	Vec2 velocity = {};
	float gravity = 0.4f;
	float drag = 0.98f;
	int lifetime = 50;
	int age = 0;
	char symbol = '*';
};

// Emetteur de particules
class ParticleEmitter
{
public:
	ParticleEmitter(int _maxParticles) : maxParticles(_maxParticles)
	{
		particles.reserve(_maxParticles);
		for (int i = 0; i < _maxParticles; i++)
		{
			particles.push_back(Particle());
		}
	}
	
	void Update()
	{
		for (auto& p : particles)
		{
			p.Update();
			if (p.IsDead())
			{
				p.Reset();
			}
		}
	}
	
	void Draw(std::string& render)
	{
		for (auto& p : particles)
		{
			if (!p.IsDead())
			{
				Vec2 pos = p.GetPos();
				int x = static_cast<int>(pos.x);
				int y = static_cast<int>(pos.y);
				
				if (x >= 0 && x < VIEW_GRID_X && y >= 0 && y < VIEW_GRID_Y)
				{
					render[x + y * (VIEW_GRID_X + 1)] = p.GetSymbol();
				}
			}
		}
	}

private:
	std::vector<Particle> particles;
	int maxParticles;
};

// main
int main(void)
{
	srand(static_cast<unsigned int>(time(NULL)));

	ParticleEmitter fountain(200); // Plus de particules !
	
	std::string render((VIEW_GRID_X + 1) * VIEW_GRID_Y, ' ');
	
	// Dessiner le sol
	std::string ground(VIEW_GRID_X, '=');
	
	int frameCount = 0;
	
	while (true)
	{
		frameCount++;
		
		// Update
		fountain.Update();

		// Clear render
		for (int i = 0; i < VIEW_GRID_Y; i++)
		{
			int indexY = i * (VIEW_GRID_X + 1);
			for (int j = 0; j < VIEW_GRID_X; j++)
			{
				render[indexY + j] = ' '; // Espace au lieu de '.'
			}
			render[indexY + VIEW_GRID_X] = '\n';
		}
		
		// Dessiner le sol
		int groundY = (VIEW_GRID_Y - 1) * (VIEW_GRID_X + 1);
		for (int j = 0; j < VIEW_GRID_X; j++)
		{
			render[groundY + j] = '=';
		}

		// Draw particles
		fountain.Draw(render);

		// Affichage
		std::cout << render;
		std::cout << "\n Particles: 50 | Frame: " << frameCount;
		std::cout << "\n [ESC] to quit" << std::endl;

		Sleep(50); // Plus fluide
		system("cls");
	}

	return EXIT_SUCCESS;
}