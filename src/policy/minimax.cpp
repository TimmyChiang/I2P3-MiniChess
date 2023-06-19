#include <iostream>
#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

const int INF = 2e9;

/**
 * @brief Get a legal action with minimax
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int getKey(const int &depth, const Point &from) {
    return depth * 36 + from.first * 6 + from.second;
}

// default: state = root, depth = 5, maximizingPlayer = 1(true)
Move Minimax::get_move(State *state, int depth, bool maximizingPlayer, std::vector< std::map<Point, int> > &v){
    std::cout << "cur depth = " << depth << "\n";
    if (!state->legal_actions.size())
        state->get_legal_actions();
    
    std::vector<Move> actions = state->legal_actions;
    for (auto mv: actions) std::cout << "(" << mv.first.first << ", " << mv.first.second << ") -> (" << mv.second.first << ", " << mv.second.second << ")\n";

    if (actions.size() == 0) { // 沒有任何合法路徑可走

    }

    Move return_move = actions[0]; // default return move

    int value;

    if (depth == 1) { // 目前預測的最底層
        // call evaluate to record the total score of the currenct state
        if (maximizingPlayer) {
            value = -INF;
            for (Move mv: actions) {
                Point from = mv.first, to = mv.second;
                int key = getKey(depth, from);
                State newState(state -> next_state(mv) -> board, false);
                v[key][to] = newState.evaluate(false);
                // value = max(value, get_move(newstate, depth-1, false));
                if (v[key][to] >= value) {  
                    value = v[key][to];
                    return_move = mv;
                }
            }
        } else {
            value = INF;
            for (Move mv: actions) {
                Point from = mv.first, to = mv.second;
                int key = getKey(depth, from);
                State newState(state -> next_state(mv) -> board, true);
                // value = min(value, get_move(newstate, depth-1, true));
                if (v[key][to] <= value) {  
                    value = v[key][to];
                    return_move = mv;
                }
            }
        }
        std::cout << "depth " << depth << "'s return move: (" << return_move.first.first << ", " << return_move.first.second << ") -> (" << return_move.second.first << ", " << return_move.second.second << ")\n";
        std::cout << "value = " << value << "\n";
        return return_move;
    }
    
    if (maximizingPlayer) { // 如果現在是自己的話
        value = -INF;
        for (Move mv: actions) {
            Point from = mv.first, to = mv.second;
            int key = getKey(depth, from);
            Move curMove = get_move(state -> next_state(mv), depth - 1, false, v);
            // value = max(value, get_move(newstate, depth-1, false));
            if (v[key][to] >= value) {  
                value = v[key][to];
                return_move = mv;
            }
        }
    } else { // 如果現在是敵人的話
        value = INF;
        for (Move mv: actions) {
            Point from = mv.first, to = mv.second;
            int key = getKey(depth, from);
            Move curMove = get_move(state -> next_state(mv), depth - 1, true, v);
            // value = min(value, get_move(newstate, depth-1, true));
            if (v[key][to] <= value) {  
                value = v[key][to];
                return_move = mv;
            }
        }
    }
    std::cout << "depth " << depth << "'s return move: (" << return_move.first.first << ", " << return_move.first.second << ") -> (" << return_move.second.first << ", " << return_move.second.second << ")\n";
    std::cout << "value = " << value << "\n";
    return return_move;
}