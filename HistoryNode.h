//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_HISTORYNODE_H
#define CS008_SFML_TYPING_HISTORYNODE_H

#include "GUIComponent.h"
#include "Snapshot.h"

struct HistoryNode {
    Snapshot snapshot;
    GUIComponent* component;
};

#endif //CS008_SFML_TYPING_HISTORYNODE_H
