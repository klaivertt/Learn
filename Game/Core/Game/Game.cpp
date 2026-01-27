#include "Game.h"
#include "../../Tools/GameData.h"
#include "../../Tools/Debug/DebugViewer.h"
#include "../../Tools/Debug/Logger.h"
#include "../../Tools/Debug/SFMLDebugDraw.h"
#include "../../Core/Menu/Menu.h"


Game::Game()
{
	Load();
}

Game::~Game()
{
	// cleanup
	background.getTexture()->~Texture();
	bridgePlankSprite.getTexture()->~Texture();
	groundSprite.getTexture()->~Texture();

	delete player;
	gameOverSprite.getTexture()->~Texture();

	bridgePlanks.clear();
	bridgePlanks2.clear();
	groundSegments.clear();

	b2DestroyWorld(world);
	data->logger->Info("Game Scene Unloaded.", false);
}

void Game::Load()
{
	// Game Data singleton
	data = GameData::GetInstance();

	//Sprites
	background = LoadSprite("Assets/background.png", { 0.0f, 0.0f });
	groundSprite = LoadSprite("Assets/ground.png", { 0.5f, 0.5f });
	bridgePlankSprite = LoadSprite("Assets/planche.png", { 0.5f, 0.5f });
	gameOverSprite = LoadSprite("Assets/gameover.png", { 0.5f, 0.5f });
	gameOverSprite.setPosition(data->screen.width / 2.f, data->screen.height / 2.f);

	sf::Texture* groundtext = const_cast<sf::Texture*>(groundSprite.getTexture());
	groundtext->setRepeated(true);

	//World
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, -10.0f };
	world = b2CreateWorld(&worldDef);

	b2World_EnableSleeping(world, false);

	b2BodyDef groundDef = b2DefaultBodyDef();
	groundDef.type = b2_staticBody;
	groundID = b2CreateBody(world, &groundDef);

	b2Body_SetTransform(groundID, { 0,-23 }, b2MakeRot(0));

	b2ShapeDef groundShapeDef = b2DefaultShapeDef();
	groundShapeDef.enableContactEvents = true;
	b2Polygon groundPolygon = b2MakeBox(50, 5);
	b2ShapeId groundShapeId = b2CreatePolygonShape(groundID, &groundShapeDef, &groundPolygon);

	//Game Over Text
	gameOverText = CreateText("Use 'Space' for reload the Level", data->font, 18, Anchor::CENTER, sf::Vector2f(0, 100));

	// Motorbike Load
	LoadMotorBike();

	// Map Load
	LoadGround();
	LoadFirstBridge();
	LoadBridge();

	data->logger->Success("Game Scene Loaded.", true);
}

void Game::Update(float _dt, sf::RenderWindow& _window)
{
	// Update Game Logic
	if (isGameOver)
	{
		// if dead, countdown to stop physics update, like "ragdoll" effect
		isDeadTimer -= _dt;
		if (isDeadTimer <= 0.f)
		{
			isDeadTimer = 0.f;
		}
	}
	if (isDeadTimer > 0.f)
	{
		if (!isGameOver)
		{
			InputRealTime(_dt);
		}
		UpdateMotorWeelSpeed(_dt);
		data->debugViewer->Update(_dt);
		b2World_Step(world, _dt, PHYSISCS_PRECSION);
		MoveCamera(_dt);
		if (!isGameOver)
		{
			ContactEvent();
		}
	}

	b2Vec2 playerWorldPos = b2Body_GetPosition(motorbikeData.frameId);
	if (playerWorldPos.y < DEAD_Y)
	{
		isGameOver = true;
	}
	//data->logger->Log(LogLevel::WARNING, data->logger->Vec2(playerWorldPos, "player pos"), false);
}

void Game::KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window)
{
	if (_key.code == sf::Keyboard::F1)
	{
		data->debugViewer->ToggleFPS();
		data->screen.isDebugMode = !data->screen.isDebugMode;
	}

	if (_key.code == sf::Keyboard::Escape)
	{
		data->currentScene = new Menu(); 
		delete this;
	}

	if (_key.code == sf::Keyboard::Space)
	{
		if (isGameOver)
		{
			data->currentScene = new Game();
			delete this;
		}
	}
}

void Game::MousePressed(sf::Event::MouseButtonEvent _mouse, sf::RenderWindow& _window)
{
}

void Game::MouseMoved(sf::Event::MouseMoveEvent _mouse, sf::RenderWindow& _window)
{
}

void Game::Draw(sf::RenderWindow& _window)
{
	//Draw Ground
	_window.draw(background);

	DrawGround(_window);
	DrawBridge(_window);
	DrawMotorbike(_window);

	if (isGameOver)
	{
		_window.draw(gameOverSprite);
		_window.draw(gameOverText);
	}

	if (data->screen.isDebugMode)
	{
		b2World_Draw(world, &data->debugDraw);
	}

	data->debugViewer->Draw(_window);
}

void Game::InputRealTime(float _dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !motorbikeData.isBraking)
	{
		b2WheelJoint_EnableMotor(motorbikeData.wheelJoints[0], true);
		motorbikeData.motorAccelerating = true;
	}
	else
	{
		b2WheelJoint_EnableMotor(motorbikeData.wheelJoints[0], false);
		motorbikeData.motorAccelerating = false;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		b2Body_ApplyTorque(motorbikeData.frameId, -10.f, true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		b2Body_ApplyTorque(motorbikeData.frameId, 10.f, true);
	}

	bool braking = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

	if (braking)
	{
		// Poids vers l'arrière
		ChangeFrameGravityPoint(-1);

		// Blocage roue arrière
		b2WheelJoint_EnableMotor(motorbikeData.wheelJoints[1], true);
		b2WheelJoint_SetMotorSpeed(motorbikeData.wheelJoints[1], 0.f);

		motorbikeData.isBraking = true;
	}
	else
	{
		// Retour position normale
		ChangeFrameGravityPoint(1);

		// Déblocage roue arrière si pas d'accélération
		if (!motorbikeData.motorAccelerating)
		{
			b2WheelJoint_EnableMotor(motorbikeData.wheelJoints[1], false);
		}

		motorbikeData.isBraking = false;
	}


}

void Game::LoadMotorBike(void)
{
	for (int i = 0; i < TYPE_OF_BIKER; i++)
	{
		motorbikeData.texture[i].loadFromFile("Assets/bikeman_" + std::to_string(i) + ".png");
	}
	motorbikeData.bike = LoadSprite(motorbikeData.texture[0], { 0.5f, 0.5f });

	motorbikeData.wheel = LoadSprite("Assets/wheel.png", { 0.5f, 0.5f });

	// Frame
	b2BodyDef frameDef = b2DefaultBodyDef();
	frameDef.type = b2_dynamicBody;
	motorbikeData.frameId = b2CreateBody(world, &frameDef);

	// center to the middle of motorbike
	b2Body_SetTransform(motorbikeData.frameId, { MOTO_STARTX, MOTO_STARTY }, b2MakeRot(0));

	b2ShapeDef frameShapeDef = b2DefaultShapeDef();
	frameShapeDef.userData = (void*)"MOTO_BODY";
	b2Circle frameCircle;
	frameCircle.center = { 0, 0 };
	frameCircle.radius = FRAME_RADIUS;

	b2ShapeId boxCircleId = b2CreateCircleShape(motorbikeData.frameId, &frameShapeDef, &frameCircle);
	b2Shape_SetDensity(boxCircleId, 3, true);


	// Wheel loading
	b2BodyDef wheelDef = b2DefaultBodyDef();
	wheelDef.type = b2_dynamicBody;
	for (int i = 0; i < 2; i++)
	{
		motorbikeData.wheelsId[i] = b2CreateBody(world, &wheelDef);
	}
	b2Body_SetTransform(motorbikeData.wheelsId[0], { MOTO_STARTX - 1, MOTO_STARTY - 0.969f }, b2MakeRot(0));
	b2Body_SetTransform(motorbikeData.wheelsId[1], { MOTO_STARTX + 1, MOTO_STARTY - 0.969f }, b2MakeRot(0));
	b2ShapeDef wheelShapeDef = b2DefaultShapeDef();
	b2Circle wheelCircle;
	wheelCircle.center = { 0, 0 };
	wheelCircle.radius = 0.406f;

	b2ShapeId lWheelId = b2CreateCircleShape(motorbikeData.wheelsId[0], &wheelShapeDef, &wheelCircle);
	b2ShapeId rWheelId = b2CreateCircleShape(motorbikeData.wheelsId[1], &wheelShapeDef, &wheelCircle);
	b2Shape_SetDensity(lWheelId, 3, true);
	b2Shape_SetDensity(rWheelId, 3, true);
	//set Friction
	b2Shape_SetFriction(lWheelId, 15);
	b2Shape_SetFriction(rWheelId, 15);

	// Joints

	b2WheelJointDef leftWheelJointDef = b2DefaultWheelJointDef();
	leftWheelJointDef.bodyIdA = motorbikeData.frameId;
	leftWheelJointDef.bodyIdB = motorbikeData.wheelsId[0];
	leftWheelJointDef.localAnchorA = { -1, -0.969f };
	leftWheelJointDef.localAnchorB = { 0, 0 };

	leftWheelJointDef.motorSpeed = 0.f;
	leftWheelJointDef.maxMotorTorque = 1000.f;
	leftWheelJointDef.enableMotor = false;
	leftWheelJointDef.hertz = 10.f;
	leftWheelJointDef.dampingRatio = 2.5f;

	motorbikeData.wheelJoints[0] = b2CreateWheelJoint(world, &leftWheelJointDef);

	b2WheelJointDef rightWheelJointDef = b2DefaultWheelJointDef();
	rightWheelJointDef.bodyIdA = motorbikeData.frameId;
	rightWheelJointDef.bodyIdB = motorbikeData.wheelsId[1];
	rightWheelJointDef.localAnchorA = { 1, -0.969f };
	rightWheelJointDef.localAnchorB = { 0, 0 };
	rightWheelJointDef.motorSpeed = 0.f;
	rightWheelJointDef.maxMotorTorque = 1000.f;
	rightWheelJointDef.enableMotor = false;
	rightWheelJointDef.hertz = 10.f;
	rightWheelJointDef.dampingRatio = 2.5f;

	motorbikeData.wheelJoints[1] = b2CreateWheelJoint(world, &rightWheelJointDef);
	ChangeFrameGravityPoint(0);
}

void Game::DrawMotorbike(sf::RenderWindow& _window)
{
	//draw wheels
	for (int i = 0; i < 2; i++)
	{
		b2Vec2 wheelPos = b2Body_GetPosition(motorbikeData.wheelsId[i]);
		float wheelAngle = b2Rot_GetAngle(b2Body_GetRotation(motorbikeData.wheelsId[i]));
		motorbikeData.wheel.setPosition(World2Screen(wheelPos, data->cam));
		motorbikeData.wheel.setRotation(-wheelAngle * 180.0f / 3.14159265359f);
		_window.draw(motorbikeData.wheel);
	}

	//draw frame
	b2Vec2 pos = b2Body_GetPosition(motorbikeData.frameId);
	float angle = b2Rot_GetAngle(b2Body_GetRotation(motorbikeData.frameId));
	motorbikeData.bike.setPosition(World2Screen(pos, data->cam));
	motorbikeData.bike.setRotation(-angle * 180.0f / 3.14159265359f);

	if (motorbikeData.isBraking)
	{
		motorbikeData.bike.setTexture(motorbikeData.texture[1]);
	}
	else
	{
		motorbikeData.bike.setTexture(motorbikeData.texture[0]);
	}

	_window.draw(motorbikeData.bike);
}

void Game::MoveCamera(float _dt)
{
	b2Vec2 playerWorldPos = b2Body_GetPosition(motorbikeData.frameId);

	float pixelsToMeters = 1.f / ZOOM;

	float targetX = playerWorldPos.x - (data->screen.width * 0.5f) * pixelsToMeters;
	float targetY = playerWorldPos.y + (data->screen.height * 0.75f) * pixelsToMeters;

	data->cam.x += (targetX - data->cam.x);
	data->cam.y += (targetY - data->cam.y);
}

void Game::ChangeFrameGravityPoint(int direction)
{
	// direction =  1 -> avant
	// direction = -1 -> arrière

	b2ShapeId frameShape;
	b2Body_GetShapes(motorbikeData.frameId, &frameShape, 1);

	b2Circle circle;
	circle.radius = FRAME_RADIUS;

	if (direction == -1)
	{
		// frein
		circle.center = { -0.396f, -0.264f };
	}
	else
	{
		// normal
		circle.center = { 0.396f, -0.264f };
	}

	b2Shape_SetCircle(frameShape, &circle);
	b2Body_ApplyMassFromShapes(motorbikeData.frameId);
}

void Game::UpdateMotorWeelSpeed(float _dt)
{
	motorbikeData.currentSpeed /= (1.0f + _dt);

	if (motorbikeData.motorAccelerating)
	{
		motorbikeData.currentSpeed += MOTO_MAXSPEED * _dt;
		data->logger->Log(LogLevel::DEBUG, "Motor Speed: " + std::to_string(motorbikeData.currentSpeed), false);
	}

	b2WheelJoint_SetMotorSpeed(motorbikeData.wheelJoints[0], -motorbikeData.currentSpeed);
}

void Game::LoadGround(void)
{
	// Terrain heights data
	float terrainHeights[] = {
	0.0f, 0.0f, 0.0f, 0.0f, 0.3984f, 0.9296f, 1.5936f, 1.992f, 2.1248f,
	1.992f, 1.7264f, 1.0624f, 0.2656f, 0.0f, 0.1328f, 0.0f, 0.1328f, 0.2656f,
	0.2656f, 0.1328f, 0.1328f, 0.0f, 0.1328f, 0.0f, 0.2656f, 0.664f, 1.992f,
	0.2656f, 0.2656f, 1.992f, 1.992f, 0.7968f, 0.1328f, 0.0f, 0.0f, 0.1328f,
	0.2656f, 0.1328f, 0.0f, 0.1328f, 0.0f, 0.2656f, 0.1328f, 0.0f, 0.2656f,
	1.5936f, 0.2656f, 1.8592f, 0.1328f, 0.3984f, 2.1248f, 2.656f, 0.0f,
	0.1328f, 2.3904f, 1.5936f, 0.2656f, 0.1328f, 0.3984f, 0.2656f, 0.1328f,
	0.3984f, 0.2656f, 0.3984f, 0.1328f, 0.0f, 0.1328f, 0.3984f, 1.328f,
	2.656f, 3.5856f, 5.1792f, 6.64f, 7.968f, 8.4992f, 9.1632f, 10.624f,
	11.0224f, 11.1552f, 3.984f, 4.3824f, 5.0464f, 7.304f, 7.968f, 8.1008f,
	7.968f, 6.64f, 4.648f, 1.328f, 1.0624f, 0.664f, 0.3984f, 0.0f, 0.0f,
	1.0f, 0.0f, -25.0f, -25.0f, -25.0f, -25.0f, -25.0f, -25.0f, -25.0f,
	-25.0f, -25.0f, -25.0f, -25.0f, -25.0f, -25.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

	// Create ground segments
	int groundSegmentCount = sizeof(terrainHeights) / sizeof(float);
	float blockWidth = 2.0f;
	float baseY = -50.0f;

	for (int i = 0; i < groundSegmentCount - 1; i++)
	{
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_staticBody;

		groundSegments.push_back(b2CreateBody(world, &bodyDef));
		float x = i * blockWidth;

		b2Vec2 vertices[4];
		vertices[0] = { x, baseY };
		vertices[1] = { x + blockWidth, baseY };
		vertices[2] = { x + blockWidth, terrainHeights[i + 1] };
		vertices[3] = { x, terrainHeights[i] };

		b2Hull hull = b2ComputeHull(vertices, 4);
		b2Polygon polygon = b2MakePolygon(&hull, 0.0f);

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.enableContactEvents = true;
		b2CreatePolygonShape(groundSegments[i], &shapeDef, &polygon);
	}

	terrainEndPos.x = (groundSegmentCount - 1) * blockWidth;
	terrainEndPos.y = terrainHeights[groundSegmentCount - 1];
}

void Game::LoadBridge()
{
	// Bridge Planks
	int bridgePlankCount = BRIDGE_PLANK_COUNT;
	b2BodyDef poleDef = b2DefaultBodyDef();
	poleDef.type = b2_staticBody;

	b2BodyId poteau1 = b2CreateBody(world, &poleDef);
	b2Body_SetTransform(poteau1, { terrainEndPos.x - PLANK_HALF_WIDTH, terrainEndPos.y }, b2MakeRot(0));

	b2BodyId poteau2 = b2CreateBody(world, &poleDef);
	b2Body_SetTransform(poteau2, { terrainEndPos.x + (PLANK_SPACING * (BRIDGE_PLANK_COUNT - 1) - PLANK_HALF_WIDTH), terrainEndPos.y }, b2MakeRot(0));

	b2Polygon plankPolygon = b2MakeBox(PLANK_HALF_WIDTH, PLANK_HALF_HEIGHT);

	// Create bridge planks
	for (int i = 0; i < BRIDGE_PLANK_COUNT; i++)
	{
		b2BodyDef plankDef = b2DefaultBodyDef();
		plankDef.type = b2_dynamicBody;

		bridgePlanks2.push_back(b2CreateBody(world, &plankDef));

		float x = terrainEndPos.x + i * PLANK_SPACING;
		b2Body_SetTransform(bridgePlanks2[i], { x, terrainEndPos.y }, b2MakeRot(0));

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.enableContactEvents = true;
		b2ShapeId shapeId = b2CreatePolygonShape(bridgePlanks2[i], &shapeDef, &plankPolygon);
		b2Shape_SetDensity(shapeId, 1.0f, true);

	}

	// Create joints between planks and poles

	b2RevoluteJointDef joint = b2DefaultRevoluteJointDef();
	joint.bodyIdA = poteau1;
	joint.bodyIdB = bridgePlanks2[0];
	joint.localAnchorA = { PLANK_HALF_WIDTH, 0.0f };
	joint.localAnchorB = { -PLANK_HALF_WIDTH, 0.0f };
	joint.collideConnected = false;
	b2CreateRevoluteJoint(world, &joint);

	for (int i = 0; i < BRIDGE_PLANK_COUNT - 1; i++)
	{
		b2RevoluteJointDef joint = b2DefaultRevoluteJointDef();
		joint.bodyIdA = bridgePlanks2[i];
		joint.bodyIdB = bridgePlanks2[i + 1];
		joint.localAnchorA = { PLANK_HALF_WIDTH, 0.0f };
		joint.localAnchorB = { -PLANK_HALF_WIDTH, 0.0f };
		joint.collideConnected = false;
		b2CreateRevoluteJoint(world, &joint);
	}

	joint = b2DefaultRevoluteJointDef();
	joint.bodyIdA = bridgePlanks2[BRIDGE_PLANK_COUNT - 1];
	joint.bodyIdB = poteau2;
	joint.localAnchorA = { PLANK_HALF_WIDTH, 0.0f };
	joint.localAnchorB = { -PLANK_HALF_WIDTH, 0.0f };
	joint.collideConnected = false;
	b2CreateRevoluteJoint(world, &joint);

	// Load end ground after bridge
	LoadEndGround(terrainEndPos.x + ((BRIDGE_PLANK_COUNT - 2) * PLANK_SPACING), terrainEndPos.y);
}

void Game::LoadEndGround(float startX, float startY)
{
	float blockWidth = 2.0f;
	float baseY = -50.0f;

	float heights[SEGMENT_COUNT + 1] =
	{
		startY,
		startY + 0.2f,
		startY + 0.4f,
		startY + 0.6f,
		startY + 0.6f,
		startY + 0.6f,
		startY + 0.6f
	};

	int old = groundSegments.size();
	for (int i = 0; i < SEGMENT_COUNT; i++)
	{
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_staticBody;

		groundSegments.push_back(b2CreateBody(world, &bodyDef));
		float x = startX + i * blockWidth;

		b2Vec2 vertices[4];
		vertices[0] = { x,               baseY };
		vertices[1] = { x + blockWidth, baseY };
		vertices[2] = { x + blockWidth, heights[i + 1] };
		vertices[3] = { x,               heights[i] };

		b2Hull hull = b2ComputeHull(vertices, 4);
		b2Polygon polygon = b2MakePolygon(&hull, 0.0f);

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.enableContactEvents = true;
		b2CreatePolygonShape(groundSegments[old + i], &shapeDef, &polygon);
	}
}

void Game::LoadFirstBridge(void)
{
	int bridgePlankCount = BRIDGE_PLANK_COUNT;
	b2BodyDef poleDef = b2DefaultBodyDef();
	poleDef.type = b2_staticBody;

	b2BodyId poteau1 = b2CreateBody(world, &poleDef);
	b2Body_SetTransform(poteau1, { FIRST_BRIDGE_START_X - PLANK_HALF_WIDTH, FIRST_BRIDGE_Y }, b2MakeRot(0));

	b2BodyId poteau2 = b2CreateBody(world, &poleDef);
	b2Body_SetTransform(poteau2, { FIRST_BRIDGE_END_X + (PLANK_SPACING * (BRIDGE_PLANK_COUNT - 1) - PLANK_HALF_WIDTH), FIRST_BRIDGE_Y }, b2MakeRot(0));

	b2Polygon plankPolygon = b2MakeBox(PLANK_HALF_WIDTH, PLANK_HALF_HEIGHT);

	for (int i = 0; i < BRIDGE_PLANK_COUNT; i++)
	{
		b2BodyDef plankDef = b2DefaultBodyDef();
		plankDef.type = b2_dynamicBody;

		bridgePlanks.push_back(b2CreateBody(world, &plankDef));

		float x = FIRST_BRIDGE_START_X + i * PLANK_SPACING;
		b2Body_SetTransform(bridgePlanks[i], { x, FIRST_BRIDGE_Y }, b2MakeRot(0));

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.enableContactEvents = true;
		b2ShapeId shapeId = b2CreatePolygonShape(bridgePlanks[i], &shapeDef, &plankPolygon);
		b2Shape_SetDensity(shapeId, 1.0f, true);

	}

	b2RevoluteJointDef joint = b2DefaultRevoluteJointDef();
	joint.bodyIdA = poteau1;
	joint.bodyIdB = bridgePlanks[0];
	joint.localAnchorA = { PLANK_HALF_WIDTH, 0.0f };
	joint.localAnchorB = { -PLANK_HALF_WIDTH, 0.0f };
	joint.collideConnected = false;
	b2CreateRevoluteJoint(world, &joint);

	for (int i = 0; i < BRIDGE_PLANK_COUNT - 1; i++)
	{
		b2RevoluteJointDef joint = b2DefaultRevoluteJointDef();
		joint.bodyIdA = bridgePlanks[i];
		joint.bodyIdB = bridgePlanks[i + 1];
		joint.localAnchorA = { PLANK_HALF_WIDTH, 0.0f };
		joint.localAnchorB = { -PLANK_HALF_WIDTH, 0.0f };
		joint.collideConnected = false;
		b2CreateRevoluteJoint(world, &joint);
	}

	joint = b2DefaultRevoluteJointDef();
	joint.bodyIdA = bridgePlanks[BRIDGE_PLANK_COUNT - 1];
	joint.bodyIdB = poteau2;
	joint.localAnchorA = { PLANK_HALF_WIDTH, 0.0f };
	joint.localAnchorB = { -PLANK_HALF_WIDTH, 0.0f };
	joint.collideConnected = false;
	b2CreateRevoluteJoint(world, &joint);
}

void Game::DrawBridge(sf::RenderWindow& _window)
{
	for (int i = 0; i < bridgePlanks.size(); i++)
	{
		DrawBodyWithSprite(_window, bridgePlanks[i], bridgePlankSprite);
	}
	for (int i = 0; i < bridgePlanks2.size(); i++)
	{
		DrawBodyWithSprite(_window, bridgePlanks2[i], bridgePlankSprite);
	}
}

void Game::DrawGround(sf::RenderWindow& _window)
{
	for (int i = 0; i < groundSegments.size() - 1; i++)
	{
		DrawGroundBodyWithSprite(_window, groundSegments[i], groundSprite);
	}
}

void Game::ContactEvent(void)
{
	b2ContactEvents events = b2World_GetContactEvents(world);
	for (int i = 0; i < events.beginCount; ++i)
	{
		b2ContactBeginTouchEvent* beginEvent = events.beginEvents + i;
		const char* userDataA = static_cast<const char*>(b2Shape_GetUserData(beginEvent->shapeIdA));
		const char* userDataB = static_cast<const char*>(b2Shape_GetUserData(beginEvent->shapeIdB));

		if ((userDataA && std::string(userDataA) == "MOTO_BODY") ||
			(userDataB && std::string(userDataB) == "MOTO_BODY"))
		{
			data->logger->Log(LogLevel::INFO, "Motorbike has contacted an object.", true);
			isGameOver = true;
			isDeadTimer = DEAD_TIMER;
		}
	}
}

void Game::DrawBodyWithSprite(sf::RenderWindow& _window, b2BodyId bodyId, sf::Sprite& sprite)
{
	b2Vec2 pos = b2Body_GetPosition(bodyId);
	float angle = b2Rot_GetAngle(b2Body_GetRotation(bodyId));
	sprite.setPosition(World2Screen(pos, data->cam));
	sprite.setRotation(-angle * RAD_TO_DEG);
	_window.draw(sprite);
}

void Game::DrawGroundBodyWithSprite(sf::RenderWindow& window, b2BodyId bodyId, sf::Sprite& sprite)
{
	b2ShapeId shapeId;
	int shapeCount = b2Body_GetShapes(bodyId, &shapeId, 1);
	if (shapeCount == 0)
	{
		return;
	}

	b2Polygon polygon = b2Shape_GetPolygon(shapeId);

	sf::VertexArray vertices(sf::Quads, polygon.count);

	for (int i = 0; i < polygon.count; i++)
	{
		b2Vec2 worldPos = b2Body_GetWorldPoint(bodyId, polygon.vertices[i]);
		sf::Vector2f screenPos = World2Screen(worldPos, data->cam);

		vertices[i].position = screenPos;

		vertices[i].texCoords.x = polygon.vertices[i].x * ZOOM;
		vertices[i].texCoords.y = polygon.vertices[i].y * ZOOM;
	}

	sf::RenderStates states;
	states.texture = sprite.getTexture();

	window.draw(vertices, states);
}

