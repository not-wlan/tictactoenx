#include "include/tictactoe.hpp"

#include <cstdio>
#include <algorithm>
#include <iterator>

namespace tictactoe {

    static constexpr auto font_size = 16;


    void board::print() {
        std::printf(
            "\x1b[%d;%dH"           \
            "/---|---|---\\     \n" \
            "|   |   |   |      \n" \
            "| %c | %c | %c |   \n" \
            "|   |   |   |      \n" \
            "|---|---|---|      \n" \
            "|   |   |   |      \n" \
            "| %c | %c | %c |   \n" \
            "|   |   |   |      \n" \
            "|---|---|---|      \n" \
            "|   |   |   |      \n" \
            "| %c | %c | %c |   \n" \
            "|   |   |   |      \n" \
            "\\---|---|---/     \n",
            offset.y, offset.x, cells[0],cells[1],cells[2],cells[3],cells[4],cells[5],cells[6],cells[7],cells[8]
        );
    }

    void board::reset() {
            // std::fill made my switch crash...
            for(int i = 0; i < 9; i++) {
                cells[i] = empty;
            }

            player = player_1;
            winner = empty;
    }

    void board::did_win() {
        // Check for horizontal win
        for(int i = 0; i < 9; i+=3) {
            if(cells[i] != empty && cells[i] == cells[i+1] && cells[i] == cells[i+2]) {
                winner = cells[i];
                return;
            }
        }

        // Check for vertical win
        for(int i = 0; i < 3; i++) {
            if(cells[i] != empty && cells[i] == cells[i+3] && cells[i] == cells[i+6]) {
                winner = cells[i];
                return;
            }
        }

        // Check for diagonal wins
        if(cells[0] != empty && cells[0] == cells[4] && cells[0] == cells[8]) {
            winner = cells[0];
            return; 
        }

        if(cells[2] != empty && cells[2] == cells[4] && cells[2] == cells[6]) {
            winner = cells[2];
            return; 
        }

        // check for tie
        if(std::count(std::begin(cells), std::end(cells), empty) == 0) {
            winner = tie;
        }
    }

    bool board::touch(int x, int y) {
        // "window" min and max points
        constexpr auto min = point{16 * offset.x, 16 * offset.y};
        constexpr auto max = point{16 * (offset.x + 13), 16 * (offset.y + 13)};

        if(winner != empty) {
            return false;
        }

        if( x > min.x && x < max.x && y > min.y && y < max.y ) {
            // relative distance in the "window"
            const auto relative = point{x - min.x, y - min.y};
            
            // calculate the cell in the displayed 2d array
            const auto cell_x = (relative.x / (4 * font_size)) % 3;
            const auto cell_y = (relative.y / (4 * font_size)) % 3;

            // calculate the index in the 1d array
            const auto index = (cell_y * 3) + cell_x;

            // set the field to the player if it's empty and change players
            if( cells[index] == empty ) {
                cells[index] = player;
                player = (player == player_1) ? player_2 : player_1;
            } else {
                return false;
            }
            
            return true;
        } 
        return false;
    }
}