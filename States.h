//
// Created by Adam G.
//

#ifndef STATES_H
#define STATES_H

#include <map>
#include "StatesENUM.h"

class States {
private:
    std::map<StatesENUM, bool> states;
public:
    virtual void onStateChange(StatesENUM state);
    bool isEnabled(StatesENUM state) const;
    void enableState(StatesENUM state);
    void disableState(StatesENUM state);
};


#endif //STATES_H
