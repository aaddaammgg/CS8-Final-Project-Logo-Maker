//
// Created by Adam G.
//

#ifndef CS008_SFML_TYPING_SNAPSHOT_H
#define CS008_SFML_TYPING_SNAPSHOT_H

#include <string>
#include "MultiText.h"

class Snapshot {
private:
    MultiText data;
public:
    Snapshot();

    MultiText getData() const;
    void setData(MultiText mt);
};

#endif //CS008_SFML_TYPING_SNAPSHOT_H
