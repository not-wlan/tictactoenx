#include <cstring>
#include <cstdio>

#include <switch.h>

#include "include/tictactoe.hpp"

//See also libnx hid.h.

int main(int argc, char **argv)
{
    tictactoe::board b{};

    const auto redraw = [&b]() {
        consoleClear();
        printf("\x1b[1;1HPress PLUS to exit, MINUS to reset.");
        printf("\x1b[2;1HCurrent player: %c", b.player);
        b.did_win();
        
        if(b.winner != tictactoe::empty) {
            if(b.winner == tictactoe::tie) {
                printf("\x1b[3;1HTie!");
            } else {
                printf("\x1b[3;1HWinner: %c!", b.winner);
            }
            
        }

        b.print();
    };

    consoleInit(NULL);
    // Draw the initial board
    redraw();

    // Main loop
    while(appletMainLoop())
    {
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

        // Make the game reset when - is pressed
        if (kDown & KEY_MINUS) {
            b.reset();
            redraw();
        }

        touchPosition touch;
        for(u32 i=0; i< hidTouchCount(); i++)
        {
            //Read the touch screen coordinates
            hidTouchRead(&touch, i);    
            if(b.touch(touch.px, touch.py)) {
                redraw();
            }
        }

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}