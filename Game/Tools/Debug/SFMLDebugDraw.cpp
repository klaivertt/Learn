// Debug draw for Box2D 2.2.1 - 2.3.0 for SFML 2.0 - SFMLDebugDraw.cpp
// Copyright (C) 2013  Matija Lovrekovic
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "SFMLDebugDraw.h"
#include "Common.hpp"
#include "Tools/GameData.hpp"



void DebugDrawPoint(b2Vec2 p1, float size, b2HexColor color, void* _context)
{
	sf::Vertex point = sf::Vertex(World2Screen(p1, ((GameData*)_context)->cam), sf::Color((color << 8) | 255));
	
	sf::RectangleShape rectangle({ size,size });
	rectangle.setPosition(World2Screen(p1, ((GameData*)_context)->cam) - sf::Vector2f(size / 2, size / 2));
	rectangle.setFillColor(sf::Color((color << 8) | 255));
	((GameData*)_context)->window.draw(rectangle);
	
}

void DebugDrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* _context)
{
	sf::ConvexShape polygon(vertexCount);
	sf::Vector2f center;
	for(int i = 0; i < vertexCount; i++)
	{
		sf::Vector2f transformedVec =World2Screen(vertices[i], ((GameData*)_context)->cam);
		polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
	}																								   // they still show up though.. but less frequently
	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineColor(sf::Color((color << 8) | 255));

	((GameData*)_context)->window.draw(polygon);
}
void DebugDrawSolidPolygon(b2Transform _transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* _context)
{

	sf::ConvexShape polygon(vertexCount);
	for(int i = 0; i < vertexCount; i++)
	{
		sf::Vector2f transformedVec = World2Screen(vertices[i], {0,0});
		polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
	}																								   // they still show up though.. but less frequently
	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(sf::Color((color << 8) | 60));
	polygon.setOutlineColor(sf::Color((color << 8) | 255));
	polygon.setPosition(World2Screen(_transform.p, ((GameData*)_context)->cam));
	polygon.setRotation(-b2Rot_GetAngle(_transform.q)*180 / 3.1415926535f);


	((GameData*)_context)->window.draw(polygon);
}
void DebugDrawCircle(b2Vec2 center, float radius, b2HexColor color, void* _context)
{
	sf::CircleShape circle(radius * ZOOM);
	circle.setOrigin(radius * ZOOM, radius * ZOOM);
	circle.setPosition(World2Screen(center, ((GameData*)_context)->cam));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(-1.f);
	circle.setOutlineColor(sf::Color((color << 8) | 255));

	((GameData*)_context)->window.draw(circle);
}
void DebugDrawSolidCircle(b2Transform _transform, float radius, b2HexColor color, void* _context)
{
	sf::CircleShape circle(radius * ZOOM);
	circle.setOrigin(radius * ZOOM, radius * ZOOM);
	circle.setPosition(World2Screen(_transform.p, ((GameData*)_context)->cam));
	circle.setFillColor(sf::Color((color << 8) | 60));
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(sf::Color((color << 8) | 255));

	b2Vec2 endPoint = _transform.p + b2Vec2{radius, 0};// +radius * b2Tr _transform.q;
	sf::Vertex line[2] = 
	{
		sf::Vertex(World2Screen(_transform.p, ((GameData*)_context)->cam), sf::Color((color << 8) | 255)),
		sf::Vertex(World2Screen(endPoint, ((GameData*)_context)->cam), sf::Color((color << 8) | 255)),
	};

	((GameData*)_context)->window.draw(circle);
	((GameData*)_context)->window.draw(line, 2, sf::Lines);
}
void DebugDrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* _context)
{
	sf::Vertex line[] =
	{
		sf::Vertex(World2Screen(p1,((GameData*)_context)->cam), sf::Color((color << 8) | 255)),
		sf::Vertex(World2Screen(p2,((GameData*)_context)->cam), sf::Color((color << 8) | 255))
	};

	((GameData*)_context)->window.draw(line, 2, sf::Lines);
}
void DebugDrawTransform(b2Transform _transform, void* _context)
{
	float lineLength = 0.4;

	b2Vec2 xAxis = _transform.p + lineLength * b2Rot_GetXAxis(_transform.q);
	sf::Vertex redLine[] = 
	{
		sf::Vertex(World2Screen(_transform.p,((GameData*)_context)->cam), sf::Color::Red),
		sf::Vertex(World2Screen(xAxis,((GameData*)_context)->cam), sf::Color::Red)
	};


	// You might notice that the ordinate(Y axis) points downward unlike the one in Box2D testbed
	// That's because the ordinate in SFML coordinate system points downward while the OpenGL(testbed) points upward
	b2Vec2 yAxis = _transform.p + lineLength * b2Rot_GetYAxis (_transform.q);
	sf::Vertex greenLine[] = 
	{
		sf::Vertex(World2Screen(_transform.p,((GameData*)_context)->cam), sf::Color::Green),
		sf::Vertex(World2Screen(yAxis,((GameData*)_context)->cam), sf::Color::Green)
	};

	((GameData*)_context)->window.draw(redLine, 2, sf::Lines);
	((GameData*)_context)->window.draw(greenLine, 2, sf::Lines);
}

void DebugDrawString(b2Vec2 p1, const char* _text, b2HexColor _color, void* _context) {}