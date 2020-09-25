#include "logic.h"

//Author: Jared Raiola
//GTID: 903293358

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState -> gameOver = 0; // initializes the game to not be over; 0 = false, 1 = true
    appState -> life = 1; // initialize player lives to 1
    appState -> ship.xPos = (WIDTH / 2) - (SHIPWIDTH / 2); // initializes ships x position to middle x coord
    appState -> ship.yPos = HEIGHT - SHIPHEIGHT - 5; // initializes ships y position of right above the bottom screen
    appState -> adown = 0; // initializes that a isnt pressed
    appState -> ship.fire = 0; // intializes that the ship isn't firing currently
    appState -> fireball.xPos = 0; // places initial fireball offscreen 
    appState -> fireball.yPos = 180; // ""
    appState -> shotGone = 1; // initializes that the current fireball shot isn't on the screen
    appState -> alienGone = 1; // intitializes that the current alien isn't on the screen
    appState -> startGame = 0; // intializes startGame frame to 0
    appState -> alien.xPos = 0; //initializes alien x position to 0
    appState -> alien.yPos = 14; //initializes alien y pos to 14 to prevent overlap with scoreCard
    appState -> moveTimer = 0; // initializes moveTimer to 0
    appState -> gameScore = -20; // initializes gameScore to -20 to prevent 10 extra points from removing the first alien
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

void moveShip(AppState *currentAppState, AppState *nextAppState, 
    u32 keysPressedNow) { // allows 2D movement
    if (KEY_DOWN(BUTTON_RIGHT, keysPressedNow) &&
        currentAppState -> ship.xPos + SHIPWIDTH < WIDTH) {
        //move right if right is pressed
        nextAppState -> ship.xPos += 1;
    } 
    if (KEY_DOWN(BUTTON_LEFT, keysPressedNow) &&
        currentAppState -> ship.xPos > 0) {
        //move left if left is pressed
        nextAppState -> ship.xPos -= 1;
    }
    if (KEY_DOWN(BUTTON_UP, keysPressedNow) &&
        currentAppState -> ship.yPos > 100) {
        //move up if up is pressed
        nextAppState -> ship.yPos -= 1;
    }
    if (KEY_DOWN(BUTTON_DOWN, keysPressedNow) &&
        currentAppState -> ship.yPos < HEIGHT - SHIPHEIGHT) {
        //move down if down is pressed
        nextAppState -> ship.yPos += 1;
    }
}

void fire(AppState *currentAppState, AppState *nextAppState, 
    u32 keysPressedNow) {
    if (KEY_DOWN(BUTTON_A, keysPressedNow) && !(currentAppState -> adown == 1)) { // if a is pressend and wasn't pressed before
        nextAppState -> fireball.xPos = nextAppState -> ship.xPos + 3; // spawn fireball above ship
        nextAppState -> fireball.yPos = nextAppState -> ship.yPos - 10; // ""
        nextAppState -> adown = 1; // a is now pressed
        nextAppState -> ship.fire = 1; // a fireball is now on the screen
        nextAppState -> shotGone = 0; // no more shots left
    }
    if ((currentAppState -> adown == 1) && !KEY_DOWN(BUTTON_A, keysPressedNow) && 
        currentAppState -> shotGone == 1) { // if a is down and a isn't actually pressed
        nextAppState -> adown = 0; // a isn't pressed
        nextAppState -> ship.fire = 0; // ship can now fire again when shot comes back
    }
}

void moveFire(AppState *currentAppState, AppState *nextAppState) { // moves the fireball
    if (currentAppState -> shotGone == 0) { // if the shot is on screen
        if (currentAppState -> fireball.yPos > 11){ // if the shot is still in the allowable bounds
            nextAppState -> fireball.yPos = nextAppState -> fireball.yPos - 2; // move the fireball 2 pixels up
        } else {
            nextAppState -> shotGone = 1; // the shot is now returned
        }
    }
}

void checkStartGame(AppState *nextAppState, u32 keysPressedNow) { // checks to see if the game has started
    if (KEY_DOWN(0x1FF, keysPressedNow)) {
        nextAppState -> startGame++; // allows for any key to be pressed in order to then clear instructions and spawn first alien

    }
}

void moveAlien(AppState *currentAppState, AppState *nextAppState) { // moves the alien at different speeds depending on how long you've been playing
    if (currentAppState -> alienGone != 1) { // if alien is on the screen
        if (currentAppState -> moveTimer < 5000) { // slowest speed, a pixel every 3 frames
            if (currentAppState -> alien.yPos < 160 && 
                currentAppState -> moveTimer % 3 == 0) {
                nextAppState -> alien.yPos = nextAppState -> alien.yPos + 1;
                nextAppState -> moveTimer++;
            } else if (currentAppState -> alien.yPos < 160) {
                nextAppState -> moveTimer++;
            } else { // if alien is out of bounds, it's no longer on the screen
                nextAppState -> alienGone = 1;
            }
        } else if (currentAppState -> moveTimer < 10000) { // 2nd speed, a pixel every 2 frames
            if (currentAppState -> alien.yPos < 160 && 
                currentAppState -> moveTimer % 2 == 0) {
                nextAppState -> alien.yPos = nextAppState -> alien.yPos + 1;
                nextAppState -> moveTimer++;
            } else if (currentAppState -> alien.yPos < 160) {
                nextAppState -> moveTimer++;
            } else { 
                nextAppState -> alienGone = 0;
            }
        } else if (currentAppState -> moveTimer < 15000) { // 3rd speed, a pixel every frame
            if (currentAppState -> alien.yPos < 160) {
                nextAppState -> alien.yPos = nextAppState -> alien.yPos + 1;
                nextAppState -> moveTimer++;
            } else if (currentAppState -> alien.yPos < 160) {
                nextAppState -> moveTimer++;
            } else {
                nextAppState -> alienGone = 0;
            }
        } else {
            if (currentAppState -> alien.yPos < 160) { // final speed, 4 pixels every frame
                nextAppState -> alien.yPos = nextAppState -> alien.yPos + 2;
                nextAppState -> moveTimer++;
            } else if (currentAppState -> alien.yPos < 160) {
                nextAppState -> moveTimer++;
            } else {
                nextAppState -> alienGone = 0;
            }
        }
    }
}

void checkAlienPos(AppState *currentAppState, AppState *nextAppState) { // checks for collisions with either ship or with fireball
    if (currentAppState -> alien.yPos > HEIGHT - ENEMY_HEIGHT) {
        nextAppState -> life = 0;
    }
    if ((currentAppState -> alien.yPos + ENEMY_HEIGHT >= 
        currentAppState -> ship.yPos &&
        currentAppState -> alien.yPos <= 
        currentAppState -> ship.yPos &&
        currentAppState -> alien.xPos >= 
        currentAppState -> ship.xPos && 
        currentAppState -> alien.xPos <= 
        currentAppState -> ship.xPos + SHIPWIDTH) ||
            (currentAppState -> alien.yPos + ENEMY_HEIGHT >= 
            currentAppState -> ship.yPos &&
            currentAppState -> alien.yPos <= 
            currentAppState -> ship.yPos &&
            currentAppState -> alien.xPos + ENEMY_WIDTH - 2 >= 
            currentAppState -> ship.xPos && 
            currentAppState -> alien.xPos + ENEMY_WIDTH - 2 <= 
            currentAppState -> ship.xPos + SHIPWIDTH) ||
                (currentAppState -> alien.yPos + ENEMY_HEIGHT >= 
                currentAppState -> ship.yPos &&
                currentAppState -> alien.yPos <= 
                currentAppState -> ship.yPos &&
                currentAppState -> alien.xPos + ENEMY_WIDTH / 2 >= 
                currentAppState -> ship.xPos && 
                currentAppState -> alien.xPos + ENEMY_WIDTH / 2 <= 
                currentAppState -> ship.xPos + SHIPWIDTH)) {
        nextAppState -> life = 0; // checks ship collisions to see if it touches ship
    }
    if ((currentAppState -> alien.yPos + ENEMY_HEIGHT >= 
        currentAppState -> fireball.yPos && 
        currentAppState -> alien.yPos <= 
        currentAppState -> fireball.yPos &&
        currentAppState -> alien.xPos >= 
        currentAppState -> fireball.xPos && 
        currentAppState -> alien.xPos <= 
        currentAppState -> fireball.xPos + PROJ_WIDTH) ||
            (currentAppState -> alien.yPos + ENEMY_HEIGHT >= 
            currentAppState -> fireball.yPos && 
            currentAppState -> alien.yPos <= 
            currentAppState -> fireball.yPos &&
            currentAppState -> alien.xPos + ENEMY_WIDTH - 2 >= 
            currentAppState -> fireball.xPos - 3 && 
            currentAppState -> alien.xPos + ENEMY_WIDTH - 2 <= 
            currentAppState -> fireball.xPos + PROJ_WIDTH) ||
                (currentAppState -> alien.yPos + ENEMY_HEIGHT >= 
                currentAppState -> fireball.yPos && 
                currentAppState -> alien.yPos <= 
                currentAppState -> fireball.yPos &&
                currentAppState -> alien.xPos + ENEMY_WIDTH / 2 >= 
                currentAppState -> fireball.xPos - 3 && 
                currentAppState -> alien.xPos + ENEMY_WIDTH / 2 <= 
                currentAppState -> fireball.xPos + PROJ_WIDTH)) { // checks fireball collisions to see if it touches the fireball bounds
        nextAppState -> alienGone = 1; // alien is now gone
        nextAppState -> shotGone = 1; // fireball shot is now gone
        nextAppState -> fireball.xPos = 0; // fireball placed offscreen for one frame in order to prevent error of killing a new alien if it spawned
        nextAppState -> fireball.yPos = 180; // and hit the same bounds.
    }
}

void randomAlienSpawn(AppState *currentAppState, AppState *nextAppState) { // choses random coords to spawn new alien
    if (currentAppState -> alienGone == 1) {
        nextAppState -> alien.yPos = 14; // always must spawn greater than 13 y in order to prevent scoreCard overlap
        nextAppState -> alien.xPos = randint(15, 210); // makes sure no aliens spawn too close to the side of the screen
        nextAppState -> alienGone = 0; // alien is now deployed
    }
}

void updateGameScore(AppState *currentAppState, AppState *nextAppState) { // updates gamescore by 20 if an alien is hit with a fireball
    if (currentAppState -> alienGone == 1) {
        nextAppState -> gameScore += 20;
    }
}






// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */

    AppState nextAppState = *currentAppState;

    if (currentAppState -> life == 0) { // if life = 0 end game
        nextAppState.gameOver = 1;
    }
    if (currentAppState -> startGame < 10) { // increment startGame if the player hasn't moved past controls screen
        checkStartGame(&nextAppState, keysPressedNow);
    }
    if (currentAppState -> startGame == 10) { // main body calls after the game is started
        moveShip(currentAppState, &nextAppState, keysPressedNow);
        fire(currentAppState, &nextAppState, keysPressedNow);
        moveFire(currentAppState, &nextAppState);
        randomAlienSpawn(currentAppState, &nextAppState);
        moveAlien(currentAppState, &nextAppState);
        checkAlienPos(currentAppState, &nextAppState);
        updateGameScore(currentAppState, &nextAppState);
    }

    UNUSED(keysPressedBefore);
    return nextAppState;
}
