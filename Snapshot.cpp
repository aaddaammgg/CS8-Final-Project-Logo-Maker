//
// Created by Adam G.
//
#ifndef CS008_SFML_TYPING_SNAPSHOT_CPP
#define CS008_SFML_TYPING_SNAPSHOT_CPP

#include "Snapshot.h"

Snapshot::Snapshot() {

}

MultiText Snapshot::getData() const {
    return data;
}

void Snapshot::setData(MultiText mt) {
    this->data = mt;
}

#endif //CS008_SFML_TYPING_SNAPSHOT_CPP