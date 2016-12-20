//  Copyright © 2016 Oh Jun Kwon. All rights reserved.

#include "OthelloAI.hpp"

namespace kwonoj
{
    class UniqueAI : public OthelloAI
    {
    public:
        virtual std::pair<int,int> chooseMove(const OthelloGameState& state);

        virtual int search(const OthelloGameState& state, int depth, bool playerisblack);

    };
}
