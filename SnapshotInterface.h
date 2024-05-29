//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_SNAPSHOTINTERFACE_H
#define CS008_SFML_TYPING_SNAPSHOTINTERFACE_H

#include "Snapshot.h"

class SnapshotInterface {
private:
public:
    SnapshotInterface();

    virtual Snapshot getSnapshot() = 0;
    virtual void applySnapshot(const Snapshot& snapshot) = 0;
};

//#include "SnapshotInterface.cpp"

#endif //CS008_SFML_TYPING_SNAPSHOTINTERFACE_H
