//
// Created by Adam G.
//

#include "History.h"

bool History::getInit() {
    return init;
}

void History::setInit(bool b) {
    init = b;
}

void History::undoPush(const HistoryNode &snapshot) {
    undoStack.push(snapshot);
}

HistoryNode &History::getUndoTop() {
    return undoStack.top();
}

int History::getUndoSize() {
    return undoStack.size();
}

void History::undoPop() {
    std::cout << "undo boxSize: " << undoStack.size() << std::endl;
    if (!undoStack.empty()) {
        redoPush(getUndoTop());
        undoStack.pop();
    }
}

void History::redoPush(const HistoryNode &snapshot) {
    redoStack.push(snapshot);
}

HistoryNode &History::getRedoTop() {
    return redoStack.top();
}

int History::getRedoSize() {
    return redoStack.size();
}

void History::redoPop() {
    if (!redoStack.empty()) {
        undoPush(getRedoTop());
        redoStack.pop();
    }
}

void History::addEventHandler(sf::RenderWindow &window, sf::Event event) {

}
