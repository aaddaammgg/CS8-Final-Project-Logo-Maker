//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_HISTORY_H
#define CS008_SFML_TYPING_HISTORY_H

#include <stack>
#include "GUIComponent.h"
#include "Snapshot.h"
#include "HistoryNode.h"

class History {
private:
    std::stack<HistoryNode> undoStack;
    std::stack<HistoryNode> redoStack;
    bool init = false;
public:
    bool getInit();
    void setInit(bool b);

    void undoPush(const HistoryNode& snapshot);
    HistoryNode& getUndoTop();
    int getUndoSize();
    void undoPop();

    void redoPush(const HistoryNode& snapshot);
    HistoryNode& getRedoTop();
    int getRedoSize();
    void redoPop();

    void addEventHandler(sf::RenderWindow& window, sf::Event event);
};


#endif //CS008_SFML_TYPING_HISTORY_H
