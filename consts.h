#ifndef __CONSTS_MY_H__
#define __CONSTS_MY_H__

#include<SDL/SDL.h>

#include<SDL/SDL_ttf.h>

#include <SDL/SDL_mixer.h>

#include <time.h>
#include <stdlib.h>

/** Declare Variables to be used.. */

#define WAIT_TIME_START   2000             //millisec
#define WAIT_TIME_END     2000             //millisec
#define WAIT_TIME_MSG     2000             //millisec

#define GAME_FONT_SIZE 32
#define MENU_START  90
#define MENU_SPACE_LINE (45-GAME_FONT_SIZE)
#define CREDITS_START 120
#define VERT_TILES 12
#define TILE_WIDTH 40
#define TILE_HEIGHT 40
#define NUM_MENU_ITEMS 5
#define NUM_TILE_TYPES 8

#define PIKAMANIA_IMG_STARTX  140
#define PIKAMANIA_IMG_STARTY  105

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frames per seconds
#define  FRAMES_PER_SECOND  30

#define PLAYER_WIDTH  30
#define PLAYER_HEIGHT 30
#define PLAYER_VEL_X  6
#define PLAYER_VEL_Y  31
#define PLAYER_MAX_VEL_Y  30
#define PLAYER_MAX_X   SCREEN_WIDTH/4

#define TOTAL_ENEMIES 3
#define ENEMY_VEL_X   3
#define ENEMY_HEALTH 50
#define PLAYER_HEALTH 100
#define GRAVITY 3

#define WEAPON_WIDTH 40
#define WEAPON_HEIGHT 20
#define WEAPON_VEL_X 10
#define WEAPON_DAMAGE 120           //damage caused by 1 hit of the weapon

#define FADE_ALPHA_INCREMENT 5
#define FADE_DELAY    50       // millisec

#define GAME_NAME_Y 2

#define COLLISION_CLEARENCE 1

#define POINTS_COIN  100
#define POINTS_X     50
#define POINTS_Y     20

#define MIX_CHANNELS_CREDITS 2
#define MIX_CHANNELS_THUNDER 5
#define MIX_CHANNELS_CONTROLS 3
#define MIX_CHANNELS_LEVEL 1
#define MIX_CHANNELS_EXTRAS 4
#define MIX_CHANNELS_MENU 6
#define INFINITE_PLAY_MUSIC -1

#define TOTAL_LEVELS 4

#endif // __CONSTS_MY_H__
