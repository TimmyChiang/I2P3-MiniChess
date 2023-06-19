#pragma once
#include "../state/state.hpp"
#include <vector>
#include <map>


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Minimax{
public:
  static Move get_move(State *state, int depth, bool maximizingPlayer, std::vector< std::map<Point, int> > &v);
};