#include "gba.h"
#include "logic.h"
#include "draw.h"
// TA-TODO: Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
#include "images/spaceship.h" // start screen image
#include "images/gameover.h" // gameover image

//Author: Jared Raiola
//GTID: 903293358

#include <stdio.h>
#include <stdlib.h>

// AppState enum definition
typedef enum {
    // TA-TODO: Add any additional states you need for your app.
    START,
    START_NODRAW,
    APP_INIT,
    APP,
    APP_EXIT,
    APP_EXIT_NODRAW,
} GBAState;

int main(void) {
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    GBAState state = START;

    // We store the "previous" and "current" states.
    AppState currentAppState, nextAppState;

    // We store the current and previous values of the button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    while (1) {
        // Load the current state of the buttons
        currentButtons = BUTTONS;

        // TA-TODO: Manipulate the state machine below as needed.
        switch(state) {
            case START:
                // Wait for VBlank
                waitForVBlank();

                // TA-TODO: Draw the start state here.
                drawFullScreenImageDMA(spaceship);
                drawString(WIDTH / 3, 15, "ALIEN DEFENSE", RED);
                drawString(WIDTH / 4 - 5, 140, "PRESS ANY KEY TO BEGIN", RED);

                state = START_NODRAW;
                break;
            case START_NODRAW:
                if (KEY_JUST_PRESSED(0x1FF, currentButtons, previousButtons) && 
                    !KEY_DOWN(BUTTON_SELECT, currentButtons)) {
                    state = APP_INIT;
                }

                break;
            case APP_INIT:
                // Initialize the app. Switch to the APP state.
                initializeAppState(&currentAppState);

                // Draw the initial state of the app
                fullDrawAppState(&currentAppState);

                state = APP;
                break;
            case APP:
                // Process the app for one frame, store the next state
                nextAppState = processAppState(&currentAppState, previousButtons, currentButtons);

                // Wait for VBlank before we do any drawing.
                waitForVBlank();

                // Undraw the previous state
                undrawAppState(&currentAppState);

                // Draw the current state
                drawAppState(&nextAppState);

                // Now set the current state as the next state for the next iter.
                currentAppState = nextAppState;
                if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
                    state = START;
                }


                // Check if the app is exiting. If it is, then go to the exit state.
                if (nextAppState.gameOver == 1) {
                    state = APP_EXIT;
                }

                break;
            case APP_EXIT:
                // Wait for VBlank
                waitForVBlank();

                // TA-TODO: Draw the exit / gameover screen
                drawFullScreenImageDMA(gameover);
                char finalScore[40];
                sprintf(finalScore, "FINAL SCORE: %d", currentAppState.gameScore);
                drawString(WIDTH / 3 - 8, 135, finalScore, WHITE);
                drawString(WIDTH / 3 + 10, 145, "CONTINUE?", WHITE);
                state = APP_EXIT_NODRAW;
                break;
            case APP_EXIT_NODRAW:
                // TA-TODO: Check for a button press here to go back to the start screen
                if (KEY_JUST_PRESSED(0x1FF, currentButtons, previousButtons)) {
                    state = START;
                }
                break;
        }

        // Store the current state of the buttons
        previousButtons = currentButtons;
    }

    return 0;
}