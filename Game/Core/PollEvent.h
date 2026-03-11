#ifndef POLL_EVENT_H
#define POLL_EVENT_H

#include "../Tools/Common.h"
#include "../Tools/Scene.h"

// Function to handle and process events from the render window
// @param _renderWindow: Pointer to the render window
// @param _data: Reference to the game data
void PollEvent(sf::RenderWindow* const _renderWindow, Scene* _scene);
#endif //!POLL_EVENT_H