#pragma once

namespace tictactoe {
    struct point{
        int x, y;
    };

    enum cellstate_t : char {
        empty = ' ',
        player_1 = 'X',
        player_2 = 'O',
        tie
    };

    struct board {
        // the board, made of cells
        cellstate_t cells[9] {
            empty, empty, empty,
            empty, empty, empty,
            empty, empty, empty 
        };
        // current player (current turn)
        cellstate_t player = player_1;
        // if winner == empty the game is in progress
        cellstate_t winner = empty;

        // this can't be changed without adding a \x1b[%d;%dH to every line and adding the appropriate 
        // format parameter
        constexpr static auto offset = point{1, 20};

        // draws the board to the screen
        void print();
        // resets the board for a new game
        void reset();
        // check for a winner, sets winner if someone won
        void did_win();
        // handle a touch
        bool touch(int x, int y);
    };
}