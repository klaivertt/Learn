#include "Rabbit.h"
#include "Food.h"

void Rabbit::UpdateDisplayBar()
{
	sf::Vector2f pos = shape.getPosition();

	pos.y -= 35.f;

	backDisplayBar.setPosition(pos);
	displayBar.setPosition(pos);

	float width = backDisplayBar.getLocalBounds().width * (energy / MAX_ENERGY);

	displayBar.setSize({ width, backDisplayBar.getLocalBounds().height });
}

void Rabbit::FindClosestFood(void)
{
	foodFinded = true;
	if (food->size() <= 0)
	{
		foodFinded = false;
	}
	else
	{
		sf::Vector2f nearestPos = sf::Vector2f(99999.f, 99999.f);
		for (size_t i = 0; i < food->size(); i++)
		{
			sf::Vector2f grassPos = (*food)[i]->GetPos();
			sf::Vector2f rabbitPos = this->shape.getPosition();
			float distNearestGrass = (std::pow((grassPos.x - rabbitPos.x), 2) + std::pow((grassPos.y - rabbitPos.y), 2));
			float distLastGrass = (std::pow((nearestPos.x - rabbitPos.x), 2) + std::pow((nearestPos.y - rabbitPos.y), 2));
			if (distNearestGrass < distLastGrass)
			{
				nearestPos = grassPos;
			}

		}
		foodPos = nearestPos;
	}
}

void Rabbit::FoodDirection(void)
{
	velocity = Normalize(foodPos - shape.getPosition());
}

void Rabbit::NewWanderingDirection(void)
{
	velocity = sf::Vector2f(RandF(-1, 1), RandF(-1, 1));
	speed = RandF(50.f, 100.f);
	wanderTime = RandF(1.f, 10.f);
}

void Rabbit::TryReproduce(void)
{
	for (size_t i = 0; i < rabits->size(); i++)
	{
		Rabbit* potentialPartner = (*rabits)[i];

		if (potentialPartner != this)
		{
			sf::FloatRect rabbitBound = shape.getGlobalBounds();
			sf::FloatRect rabbit2Bound = potentialPartner->GetBound();


			if (rabbitBound.intersects(rabbit2Bound))
			{
				if (breedable && (*rabits)[i]->GetIsBreadable())
				{
					breedable = false;
					potentialPartner->SetBreadable(false);
					SetEnergie(-BREADABLE_COST);
					potentialPartner->SetEnergie(-BREADABLE_COST);
					rabits->push_back(new Rabbit(shape.getPosition(), food, rabits, MAX_ENERGY * 0.8f));
				}
			}
		}
	}
}

void Rabbit::FindClosestBreadableRabbit(void)
{
	rabbitFind = false;
	sf::Vector2f nearestPos = sf::Vector2f(99999.f, 99999.f);
	for (size_t i = 0; i < rabits->size(); i++)
	{
		Rabbit* potentialPartner = (*rabits)[i];

		if (potentialPartner != this)
		{
			sf::Vector2f rabbitsBreadPos = potentialPartner->GetPos();
			sf::Vector2f rabbitPos = this->shape.getPosition();
			float distNearestRabbit = (std::pow((rabbitsBreadPos.x - rabbitPos.x), 2) + std::pow((rabbitsBreadPos.y - rabbitPos.y), 2));
			float distLastRabbit = (std::pow((nearestPos.x - rabbitPos.x), 2) + std::pow((nearestPos.y - rabbitPos.y), 2));
			if (distNearestRabbit < distLastRabbit && potentialPartner->GetIsBreadable())
			{
				nearestPos = rabbitsBreadPos;
				rabbitFind = true;
			}
		}
	}

	if (rabits->size() <= 0)
	{
		nearestPos =  sf::Vector2f(0, 0);
		rabbitFind = false;
	}
	rabbitPos = nearestPos;
}

void Rabbit::RabbitDirection(void)
{
	velocity = Normalize(rabbitPos - shape.getPosition());
}

Rabbit::Rabbit(sf::Vector2f _startPos, std::vector<Food*>* _food, std::vector<Rabbit*>* _rabits, float _energy)
	: food(_food), rabits(_rabits)
{
	shape.setRadius(20.f);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(_startPos);
	shape.setOrigin({ 20,20 });
	energy = 100.f;
	velocity = sf::Vector2f(RandF(-1, 1), RandF(-1, 1));
	speed = RandF(MAX_SPEED / 2, MAX_SPEED);


	sf::Vector2f size = sf::Vector2f(50, 10);
	backDisplayBar.setSize(size);
	backDisplayBar.setOrigin({ size.x / 2, size.y / 2 });
	backDisplayBar.setFillColor(sf::Color(50, 50, 50));

	displayBar.setSize(size);
	displayBar.setOrigin({ size.x / 2, size.y / 2 });
	displayBar.setFillColor(sf::Color(170, 200, 50));

	energy = _energy;
}

Rabbit::~Rabbit()
{
}

void Rabbit::Update(float _dt)
{
	UpdateState();

	if (energy < MAX_ENERGY/2)
	{
		breedable = false;
	}

	if (state == HUNGRY)
	{
		FindClosestFood();
		if (foodFinded)
		{
			FoodDirection();
		}
		else
		{
			state = WANDER;
		}
		hungry = true;
	}
	else if (state == WANDER)
	{
		wanderTime -= _dt;
		if (wanderTime < 0.f)
		{
			NewWanderingDirection();
		}
		hungry = false;
	}
	else if (state == BREEDABLE)
	{
		FindClosestBreadableRabbit();
		if (rabbitFind)
		{
			RabbitDirection();
			TryReproduce();
		}
	}

	if (energy < 30.f)
	{
		speed = MAX_SPEED * 0.7f;
	}
	else
	{
		speed = MAX_SPEED;
	}

	sf::Vector2f move = velocity * speed * _dt;
	shape.move(move);
	energy -= ENERGY_REMOVE * _dt;

	UpdateDisplayBar();
}

void Rabbit::Draw(sf::RenderWindow& _render)
{
	_render.draw(shape);

	_render.draw(backDisplayBar);
	_render.draw(displayBar);
}

bool Rabbit::IsDead(void)
{
	return energy <= 0;
}

void Rabbit::SetVelocity(sf::Vector2f _velocity)
{
	velocity = _velocity;
}

void Rabbit::SetEnergie(float _amount)
{
	energy += _amount;
	if (energy >= MAX_ENERGY)
	{
		energy = MAX_ENERGY;
	}

	if (energy < 0)
	{
		energy = 0.f;
	}
}

void Rabbit::UpdateState(void)
{
	if (energy > MAX_ENERGY *0.6f && breedable)
	{
		state = BREEDABLE;
	}
	else if (!breedable && energy > MAX_ENERGY * 0.8f)
	{
		state = WANDER;
	}
	else
	{
		state = HUNGRY;
	}
}

void Rabbit::ResetBreadable(void)
{
	breedable = true;
}

bool Rabbit::GetIsBreadable(void)
{
	return breedable;
}

void Rabbit::SetBreadable(bool _bool)
{
	breedable = _bool;
}

sf::Vector2f Rabbit::GetVelocity(void)
{
	return velocity;
}

bool Rabbit::GetHungry(void)
{
	return hungry;
}

sf::Vector2f Rabbit::GetPos(void)
{
	return shape.getPosition();
}

sf::FloatRect Rabbit::GetBound(void)
{
	return shape.getGlobalBounds();
}