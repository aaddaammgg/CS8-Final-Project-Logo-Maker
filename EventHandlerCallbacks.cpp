//
// Created by Adam G.
//

#include "EventHandlerCallbacks.h"

sf::Clock EventHandlerCallbacks::clock;
int EventHandlerCallbacks::clicks = 0;
GUIComponent* EventHandlerCallbacks::focusedComponent = nullptr;

void EventHandlerCallbacks::addEventHandler(sf::RenderWindow &window, sf::Event event) {
    switch (event.type) {
        case sf::Event::MouseMoved:
            onMouseMoved(getMousePos(window));
            break;
        case sf::Event::MouseButtonPressed:
            onMousePressed(event.mouseButton.button, getMousePos(window));
            break;
        case sf::Event::MouseButtonReleased: {
            countClicks();
            onMouseReleased(event.mouseButton.button, getMousePos(window));
            break;
        }
        case sf::Event::MouseWheelScrolled:
            onMouseWheelScrolled(event.mouseWheelScroll.wheel, event.mouseWheelScroll.delta, getMousePos(window));
            break;
        case sf::Event::KeyPressed:
            onKeyPressed(event.key);
            break;
        case sf::Event::KeyReleased:
            onKeyReleased(event.key);
            break;
        case sf::Event::TextEntered:
            onTextEntered(event.text.unicode);
            break;
        default:
            break;
    }
}

void EventHandlerCallbacks::countClicks() {
    clicks++;

    if (clock.getElapsedTime() >= sf::milliseconds(500)) {
        clock.restart();
        clicks = 1;
    }
}

bool EventHandlerCallbacks::didMouseDoubleClick() {
    return clicks == 2;
}

bool EventHandlerCallbacks::didMouseTripleClick() {
    return clicks == 3;
}

sf::Vector2f EventHandlerCallbacks::getMousePos(sf::RenderWindow &window) {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}