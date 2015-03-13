#ifndef __MY__FUNCS_H__
#define __MY__FUNCS_H__

#include"mytypes.h"
#include"consts.h"


/** Declare few functions,, */

bool init();
bool load_files();
SDL_Surface *load_image(char*);
void clean_up();
bool GameMain();
bool load_map(char*);
GameStates Play_MainGame();
GameErrors getErrorCode();

#endif // __MY__FUNCS_H__
