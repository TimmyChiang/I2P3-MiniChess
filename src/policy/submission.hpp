#pragma once
#include "../state/state.hpp"
#include <vector>
#include <map>


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Submission{
public:
    static Move get_move(State *state, int depth);
    static int get_value(State *state, int depth, bool maximizingPlayer, Move move);
};