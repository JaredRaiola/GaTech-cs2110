#ifndef LOGIC_H
#define LOGIC_H

//Author: Jared Raiola
//GTID: 903293358

#include "gba.h"

typedef struct { // spaceship struct, this is the player
    int xPos; // x coordinate
    int yPos; // y coordinate
    int fire; // tracks if the player fire
} spaceshipPlayer;

#define SHIPWIDTH 15 // width of ship
#define SHIPHEIGHT 15 // height of ship

typedef struct { // struct to track fireballs shot
    int xPos; // x coordinate
    int yPos; // y coordinate
} projectile;

#define PROJ_HEIGHT 10 // height of fireball
#define PROJ_WIDTH 10 // width of fireball

typedef struct { // struct to track aliens
    int xPos; // x coordinate
    int yPos; // y coordinate
} enemy;

#define ENEMY_HEIGHT 15 // alien height
#define ENEMY_WIDTH 20 // alien width

typedef struct { //stores the state of overarching parts of the ap
    // Store whether or not the game is over in this member:
    int gameOver; // checks to see if the game is over
    int life; // checks to see amount of lives left
    int inMotion; // checks
    spaceshipPlayer ship; // creates the players ship
    projectile fireball; // creates fireball
    enemy alien; // creates alien
    int adown; // creates the var to check if a is pressed
    int shotGone; // creates the var to check if there's a shot on the screen
    int startGame; // creates the var to see if the game is started
    int moveTimer; // creates a game timer
    int alienGone; // creates a var to see if the alien is on the screen
    int gameScore; // creates overall game score
} AppState;

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

void moveShip(AppState *currentAppState, AppState *nextAppState, 
    u32 keysPressedNow);


#endif
