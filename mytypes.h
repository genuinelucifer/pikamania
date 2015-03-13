#ifndef __MYTYPES__H_
#define __MYTYPES__H_

#include"consts.h"

/* Some error Codes used in our game.. */
typedef enum tagGameErrors
{
    GE_NO_ERROR =0,
    GE_SDL_NOT_SETUP =20,
    GE_VIDEO_NOT_INIT =21,
    GE_IMAGES_NOT_FOUND =31,
    GE_MAP_NOT_FOUND  = 40,
    GE_MIXER_NOT_INIT = 50,
    GE_MUSIC_NOT_FOUND = 23,
    GE_TTF_NOT_INIT = 60,
    GE_FONT_NOT_FOUND =61
}GameErrors;

/* Just an alternative for 'bool'  */
typedef enum tagmyTF
{
    mFALSE = 0,
    mTRUE  = 1
}myTF;


typedef enum tagDirection
{
    DLeft  =  0,
    DRight = 1
}Direction;

typedef enum tagEnemyTypes
{
    ETe1 =0,
    ETe2 =1,
    ETe3 =2
}EnemyTypes;

/** A struct to hold player info.. */
typedef struct tagPlayer
{
    /* co-ords of the Player   */
    int  curx,cury;
    int  speedx,speedy;                 /* speed of the player in the 2 directions    */
    Direction dir;
    myTF living;
    int health;


}Player;

typedef struct tagEnemy
{
    /* co-ords of the Player   */
    int  curx,cury;
    int  speedx,speedy;                 /* speed of the player in the 2 directions    */
    Direction dir;
    myTF living;
    int health;

    EnemyTypes et;
}Enemy;
//Type of tiles in the game
typedef enum tagTileTypes
{
    TTSky           = 0,
    TTCloud         = 1,
    TTStone         = 2,
    TTGrass         = 3,
    TTCoin          = 4,
    TTWeapon        = 5,
    TTBush          = 6,
    TTCup           = 7
}TileTypes;

typedef struct tagTiles
{
    TileTypes type;
}Tiles;

/** All the States the game can be in.. */
typedef enum tagGameStates
{
   GSMenu           = 1,
   GSPlaying        = 2,
   GSControls       = 3,
   GSCredits        = 4,
   GSSplashWelcome  = 5,
   GSSplashEnd      = 6,
   GSQuit           = 7

}GameStates;


typedef class tagWeapons
{
    myTF hasgot;       // If player has got weapon to be used!!
    myTF active;
    Direction dir_weapon;
    int speed;
    int cur_x;
    int cur_y;

    myTF iscollided(Tiles* all_tiles1[])   //to check collision with stone
    {
        int t1,t2,t3;
        Tiles T1,T2;
        /** collision with topleft and topright*/

                    t1 = cur_y/TILE_HEIGHT;

                    t2 = (cur_x)/TILE_WIDTH ;
                    T1 = all_tiles1[t1][t2];

                    t3 = (cur_x + WEAPON_WIDTH)/TILE_WIDTH;
                    T2 = all_tiles1[t1][t3];

                    if(T1.type == TTStone || T2.type == TTStone)
                    {
                        return mTRUE;
                    }
        /** collision with bottom left and bottom right */

                    t1 = (cur_y+WEAPON_HEIGHT)/TILE_HEIGHT;
                    t2 = (cur_x)/TILE_WIDTH ;
                    T1 = all_tiles1[t1][t2];
                    t3 = (cur_x + WEAPON_WIDTH)/TILE_WIDTH;
                    T2 = all_tiles1[t1][t3];
                    if(T1.type == TTStone || T2.type == TTStone)
                    {
                        return mTRUE;
                    }

                    return mFALSE;
    }
    myTF iscollided(Enemy e)
    {
        if(active==mFALSE)
            return mFALSE;
        if(e.living==mFALSE)
            return mFALSE;
    if((e.curx+PLAYER_WIDTH)<(cur_x))
        return mFALSE;
    if((e.cury + PLAYER_HEIGHT)<cur_y)
        return mFALSE;
    if(e.curx>(cur_x+WEAPON_WIDTH))
        return mFALSE;
    if(e.cury>(cur_y + WEAPON_HEIGHT))
        return mFALSE;
    return mTRUE;
    }

public:

    tagWeapons()
    {
        hasgot=mFALSE;
        active = mFALSE;
        dir_weapon= DLeft;
        speed=0;
        cur_x=0;
        cur_y=0;
    }

    ~tagWeapons()
    {
       // active=mFALSE;
    }

    void fired(int x,int y,Direction dir)
    {
        if(hasgot==mFALSE)
        {
            return;
        }
        if(active==mTRUE)         // If one fire is already in progress
            return;

        active = mTRUE;
        cur_x =x + ((dir==DLeft) ? (-WEAPON_WIDTH) : (PLAYER_WIDTH));
        cur_y =y ;
        dir_weapon = dir;
        speed= (dir==DRight) ? WEAPON_VEL_X : -WEAPON_VEL_X;
    }

    void move(Tiles** all_tiles,int n,Enemy* all_enemy,int m,int camx,int camy)
    {
        if(iscollided(all_tiles))
        {
            active =mFALSE;
            return;
        }
        for(int i=0;i<m;++i)
        {
            if(iscollided(all_enemy[i]))
            {
                all_enemy[i].health -= WEAPON_DAMAGE;
                if(all_enemy[i].health<=0)
                {
                    all_enemy[i].living = mFALSE;
                }
                active = mFALSE;
                return;
            }
        }
        cur_x+=speed;
        if(cur_x<=camx || cur_x>=(camx + SCREEN_WIDTH))
        {
            active = mFALSE;
            return;
        }
    }

    void show(SDL_Surface* weapon,SDL_Surface*  screen,int camx,int camy)
    {
        if(active==mFALSE)
            return;
        SDL_Rect off;
        off.x=cur_x-camx;
        off.y=cur_y-camy;
        SDL_BlitSurface(weapon,NULL,screen,&off);
    }

    Direction get_dir()
    {
        return dir_weapon;
    }
    myTF return_state()
    {
        return active;
    }
    void set_hasgot(myTF newstat)
    {
        hasgot = newstat;
    }
    myTF return_hasgot()
    {
        return hasgot;
    }

}Weapons;

#endif
