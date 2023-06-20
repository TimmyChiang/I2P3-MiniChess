#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <vector>
#include <utility>

#include "../state/state.hpp"
#include "./submission.hpp"

const int INF = 2e9;

/**
 * @brief Get a legal action with minimax
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int Submission::get_value(State *state, int depth, bool maximizingPlayer, Move move) {
    if (depth == 0)
        return state -> next_state(move) -> evaluate(maximizingPlayer);

    int value;
    
    // All the actions are in state -> legal_actions
    if (!state -> legal_actions.size())
        state -> get_legal_actions();

    if (maximizingPlayer) {
        value = -INF;
        for (Move nextmove: state -> legal_actions)
            value = std::max(value, get_value(state -> next_state(move), depth - 1, 1 - maximizingPlayer, nextmove));
    } else {
        value = INF;
        for (Move nextmove: state -> legal_actions)
            value = std::min(value, get_value(state -> next_state(move), depth - 1, 1 - maximizingPlayer, nextmove));
    }
    return value;
}

Move Submission::get_move(State *state, int depth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    std::vector<Move> actions = state->legal_actions;

    std::vector< std::pair<Move, int> > valid_moves;

    int value = -INF, curval;
    for (Move mv: actions) {
        curval = get_value(state, depth, 1, mv);
        valid_moves.emplace_back(mv, curval);
        value = std::max(value, curval);
    }

    std::vector<Move> target_moves;

    for (std::pair<Move, int> pp: valid_moves) {
        if (pp.second == value)
            target_moves.emplace_back(pp.first);
    }

    // Assume actions.size() > 0
    Move return_move = target_moves[target_moves.size() / 3];
    
    std::cout << "final move: (" << return_move.first.first << \
                            ", " << return_move.first.second << \
                            ") -> (" << return_move.second.first << \
                            ", " << return_move.second.second << \
                            "), value = " << value << "\n";

    return return_move;
}