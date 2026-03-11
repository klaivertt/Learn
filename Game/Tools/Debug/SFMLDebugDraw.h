// Debug draw for Box2D 2.2.1 - 2.3.0 for SFML 2.0 - SFMLDebugDraw.h
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

//https://github.com/MrPlow442/Box2D-SFML2-Debug-Draw


#ifndef SFMLDEBUGDRAW_H
#define SFMLDEBUGDRAW_H

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

void PassRenderingInfo(sf::RenderWindow* _window, sf::Vector2f _cam);

	///  Draw point
void DebugDrawPoint(b2Vec2 p1, float size, b2HexColor color, void* _context);

/// Draw a closed polygon provided in CCW order.
void DebugDrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* _context);

/// Draw a solid closed polygon provided in CCW order.
void DebugDrawSolidPolygon(b2Transform _transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* _context);

/// Draw a circle.
void DebugDrawCircle(b2Vec2 center, float radius, b2HexColor color, void* _context);

/// Draw a solid circle.
void DebugDrawSolidCircle(b2Transform _transform, float radius,  b2HexColor color, void* _context);

/// Draw a line segment.
void DebugDrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* _context);

/// Draw a transform. Choose your own length scale.
void DebugDrawTransform(b2Transform _transform, void* _context);

//Draw a string
void DebugDrawString(b2Vec2 p1, const char* string, b2HexColor color, void* _context);

#endif