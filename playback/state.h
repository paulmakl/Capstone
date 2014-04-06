#ifndef STATE_H_
#define STATE_H_
#include <vector>
#include "particle.h"

class state{
public:
    std::vector<particle> particles;
    void init(int numps);
};

#endif