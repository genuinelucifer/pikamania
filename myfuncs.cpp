#include"myfuncs.h"
#include<iostream>
#include<fstream>
using namespace std;


char GAME_NAME[30] = "Pika Mania 1.0";
SDL_Color GameNameColor = {200,174,87};
SDL_Color HiBiColor = {220,100,90};

int playingsound=0;
SDL_Rect global_Camera;
char last_msg_won[20] = "CONGRATS!! YOU WON!";
char last_msg_lost[15]  = "You LOSE!!";
char points_msg[10] = "Score:";
SDL_Color textColor = {50,250,70},SelMenuColor={50,30,250},GameStatusColor={230,50,60};
int checksdlkeydown=0;

char msg_lvl_change[30]="Level Complete!";
char all_tiles_bmp_names[2][8][40]= { {"data/pics/day/sky.bmp","data/pics/day/cloud.bmp","data/pics/day/stone.bmp","data/pics/day/grass.bmp","data/pics/day/coin.bmp","data/pics/day/weapon.bmp","data/pics/day/bush.bmp","data/pics/day/cup.bmp"},
                                    {"data/pics/night/sky.bmp","data/pics/night/cloud.bmp","data/pics/night/stone.bmp","data/pics/night/grass.bmp","data/pics/night/coin.bmp","data/pics/night/weapon.bmp","data/pics/night/bush.bmp","data/pics/night/cup.bmp"} };
char main_weapon_bmp_name[40] = "data/pics/other/mainweapon.bmp";
char enemy_bmp_name[3][2][40] = {{"data/pics/other/e1l.bmp","data/pics/other/e1r.bmp"},{"data/pics/other/e2l.bmp","data/pics/other/e2r.bmp"},{"data/pics/other/e3l.bmp","data/pics/other/e3r.bmp"}};
char mainplayer_bmp_name[2][40]={"data/pics/other/player_left.bmp","data/pics/other/player_right.bmp"};
char fade_bmp_name[40] = "data/pics/other/fade.bmp";
char pikamania_bmp_name[40] = "data/pics/other/pikamania.bmp";
char lost_bmp_name[40] = "data/pics/other/lost.bmp";
char won_bmp_name[40] = "data/pics/other/won.bmp";
char menu_bmp_name[40] = "data/pics/other/menu.bmp";
int colorkey_main[3] = {153,217,234};              /**Colorkey used*/

char welcome_text[30] = "WELCOME TO  Pika Mania!";
char end_text[22] = "Thanks for playing!!";

char all_menu[5][10] = {"CONTINUE","NEW GAME","CONTROLS","CREDITS","QUIT"};
char str_lost_msg[55] = "You Lost the pervious game! Better Luck Next Time...";
char str_won_msg[40]  = "CONGRATS!! You WON the previous Game!!";
char str_continue_msg[44] = "Hit CONTINUE to resume your last game...";

int map_num=0;

SDL_Color all_credits_colors[7] = {SelMenuColor,textColor,textColor,textColor,textColor,textColor,SelMenuColor};
char all_credits[7][45] = {"CREDITS","Abhinav Tripathi","Aniket Jadhav","Hari Kishore","Hursh Tiwari","Parul Gupta","Click anywhere or press Esc to go back..."};

SDL_Color all_controls_colors[6] = {SelMenuColor,textColor,textColor,textColor,textColor,SelMenuColor};
char all_controls[6][55] = {"CONTROLS","Use left and right arrow keys to move player.","Use Up arrow to jump.","Use Spacebar to fire thunderbolt.","While playing game press Esc anytime to go to Menu.","Click anywhere or press Esc to go back..."};

char game_levels[4][40]={"data/maps/level1.txt","data/maps/level2.txt","data/maps/level3.txt","data/maps/level4.txt"};
char levels_sounds[4][40]={"data/music/level1.wav","data/music/level2.wav","data/music/level3.wav","data/music/level4.wav"};

GameErrors global_Error = GE_NO_ERROR;
GameErrors getErrorCode()
{
    return global_Error;
}

GameStates global_curState = GSSplashWelcome;
bool call=false,showlastmsg=false;
Uint32 prev_ticks;

SDL_Surface* message=NULL;
TTF_Font* font=NULL;
SDL_Surface* screen=NULL;
Player global_MainPlayer;
Weapons global_weapon;
myTF played = mFALSE, won = mFALSE;

myTF isloaded=mFALSE;        // continue available??

int global_points = 0;
//SDL_Surface* background=NULL;

SDL_Event event;

//The background music that will be played


//The sound effects that will be used
Mix_Chunk *wav_coin = NULL;
//Mix_Chunk *wav_jump = NULL;
Mix_Chunk *wav_enemy = NULL;
Mix_Chunk *wav_win = NULL;
Mix_Chunk *wav_lose = NULL;
Mix_Chunk *wav_credits=NULL;
Mix_Chunk *wav_controls=NULL;
Mix_Chunk *wav_menu = NULL;
Mix_Chunk *wav_level[4]={NULL,NULL,NULL,NULL};
/*Mix_Chunk *wav_credit;*/


SDL_Surface* all_tiles_images[2][NUM_TILE_TYPES];
SDL_Surface* MainPlayer_image[2];
SDL_Surface* Enemy_image[3][2];
SDL_Surface* main_weapon_image = NULL;
SDL_Surface* fade_image = NULL;
SDL_Surface* pikamania_image = NULL;
SDL_Surface* lost_image = NULL;
SDL_Surface* won_image = NULL;
SDL_Surface* menu_image = NULL;

/** Define few functions... */


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{

    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}
void put_Text(int x,int y,char* text,SDL_Color clr=textColor,myTF CENTER_X = mTRUE,TTF_Font* fnt = font)
{
    SDL_Surface* msg = TTF_RenderText_Solid(fnt,text,clr);
     if(CENTER_X == mTRUE)
        x -= msg->w/2;
    apply_surface(x,y,msg,screen);
    SDL_FreeSurface(msg);
}


GameStates SplashWelcome()
{


    if(call==false) //call is a(to be defined) global variable which takes the number of times splass welcome is called
    {

         prev_ticks=SDL_GetTicks();

         call=true;
    }
    else if(SDL_GetTicks()-prev_ticks>=WAIT_TIME_START)
        {

            call=false;
            //Free the Events list
            while(SDL_PollEvent(&event))
            {
                ;
            }
        return GSMenu;
        }

    SDL_FillRect( screen,NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF,0xFF) )   ;      //we have to declare background remember
    apply_surface(PIKAMANIA_IMG_STARTX,PIKAMANIA_IMG_STARTY,pikamania_image,screen);
    put_Text(SCREEN_WIDTH/2,GAME_NAME_Y,GAME_NAME,GameNameColor);
    put_Text(SCREEN_WIDTH/2,400,welcome_text,HiBiColor);
    SDL_Flip(screen);
    return GSSplashWelcome;
    }


GameStates SplashEnd()
{


    if(call==false) //call is a(to be defined) global variable which takes the number of times splass welcome is called
    {
         prev_ticks=SDL_GetTicks();

         call=true;
    }
    else if(SDL_GetTicks()-prev_ticks>=WAIT_TIME_END)
        {

            call=false;
        return GSQuit;
        }

    SDL_FillRect( screen,NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF,0xFF) )   ;      //we have to declare background remember
    apply_surface(PIKAMANIA_IMG_STARTX,PIKAMANIA_IMG_STARTY,pikamania_image,screen);
    put_Text(SCREEN_WIDTH/2,GAME_NAME_Y,GAME_NAME,GameNameColor);
    put_Text(SCREEN_WIDTH/2,400,end_text,HiBiColor);

    SDL_Flip(screen);
    return GSSplashEnd;
}


myTF play_sound_effect(Mix_Chunk * chnk,int channel_num=-1,int loop=0)
{
    //Play the low hit effect
    if( Mix_PlayChannel(channel_num, chnk, loop ) == -1 )
    {
         return mFALSE;
    }
    return mTRUE;
}

int selected=1;
int y;

int playedmenu=0;
GameStates ShowMenu()
{
     if(playedmenu==0)
    {
         play_sound_effect(wav_menu,MIX_CHANNELS_MENU,INFINITE_PLAY_MUSIC);
          playedmenu=1;
    }
    else if(playedmenu==2)
    {
        Mix_Resume(MIX_CHANNELS_MENU);
    }
    /** ALWAYS do first all event handling then rendering... */
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_MOUSEMOTION)
        {
            y = event.motion.y;
            if(y<(MENU_START-(MENU_SPACE_LINE/2)) || y>(MENU_START + NUM_MENU_ITEMS*(GAME_FONT_SIZE + MENU_SPACE_LINE)))
                    continue;
            selected = ((y-MENU_START-(MENU_SPACE_LINE/2))/(GAME_FONT_SIZE+(MENU_SPACE_LINE)));
            if(selected<0)
                selected=0;
            else if(selected>(NUM_MENU_ITEMS-1))
                selected=NUM_MENU_ITEMS-1;
            if(selected==0 && isloaded==mFALSE)
                    selected = 1;
        }
        else if( event.type == SDL_MOUSEBUTTONDOWN )
       {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
                 Mix_Pause(MIX_CHANNELS_MENU);
                playedmenu=2;
                switch(selected)
                {
                case 0:
                    return GSPlaying;
                case 1:
                    isloaded=mFALSE;
                    map_num=0;
                    playingsound=0;

                    return GSPlaying;
                case 2:
                    return GSControls;
                case 3:
                    return GSCredits;
                case 4:
                    return GSSplashEnd;
                }
        }

       }
       else if(event.type == SDL_KEYDOWN)
       {
           switch(event.key.keysym.sym)
           {
           case SDLK_UP :
            selected--;
            if(selected<0)
            {
                selected = NUM_MENU_ITEMS-1;
            }
            if(isloaded==mFALSE && selected==0)
                selected=NUM_MENU_ITEMS-1;
            break;
           case SDLK_DOWN :
            selected++;
            if(selected>(NUM_MENU_ITEMS-1))
            {
                selected=0;
            }
            if(isloaded==mFALSE && selected==0)
                selected=1;
            break;
           case SDLK_RETURN :
                Mix_Pause(MIX_CHANNELS_MENU);
                playedmenu=2;
            switch(selected)
            {
                case 0:
                    return GSPlaying;
                case 1:
                    isloaded = mFALSE;
                    map_num=0;
                    playingsound=0;
                    return GSPlaying;
                case 2:
                    return GSControls;
                case 3:
                    return GSCredits;
                case 4:
                    return GSSplashEnd;
                }
                default : break;
           }

       }
    }

    //SDL_FillRect( screen,NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF,0xFF));         //we have to declare background remember
    apply_surface(0,0,menu_image,screen);
    put_Text(SCREEN_WIDTH/2,GAME_NAME_Y,GAME_NAME,GameNameColor);
    for(int i=0;i<NUM_MENU_ITEMS;++i)
    {
        if(i==0 && isloaded==mFALSE)
            continue;
        if(selected==i)
        {
            put_Text(140,MENU_START + (i*(MENU_SPACE_LINE + GAME_FONT_SIZE)),all_menu[i],SelMenuColor);
        }
        else
        {
            put_Text(140,MENU_START + (i*(MENU_SPACE_LINE + GAME_FONT_SIZE)),all_menu[i],textColor);
        }
    }

    //Show message if req
    if(played == mTRUE)
    {
        if(isloaded==mFALSE)
        {
            if(won==mFALSE)
            {
                put_Text((SCREEN_WIDTH/2),40,str_lost_msg,GameStatusColor);
            }
            else
            {
                put_Text(SCREEN_WIDTH/2,40,str_won_msg,GameStatusColor);
            }
        }
        else
        {
            put_Text(SCREEN_WIDTH/2,40,str_continue_msg,GameStatusColor);
        }
    }

    SDL_Flip(screen);

    return  GSMenu;
}
int playedcredits=0;
GameStates ShowCredits()           //isme screen ko kaisa set karna hai(meaning what color and everything woh baad me kar lenge)
{
  /** ALWAYS do first all event handling then rendering... */
    if(playedcredits==0)
    {
         play_sound_effect(wav_credits,MIX_CHANNELS_CREDITS,INFINITE_PLAY_MUSIC);
          playedcredits=1;
    }
    else if(playedcredits==2)
    {
        Mix_Resume(MIX_CHANNELS_CREDITS);
    }
    //If a mouse button was pressed
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                    Mix_Pause(MIX_CHANNELS_CREDITS);
                playedcredits=2;
                return GSMenu;
            }
        }
        else if(event.type==SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                    Mix_Pause(MIX_CHANNELS_CREDITS);
                playedcredits=2;
                return GSMenu;
            }
        }
    }
    SDL_FillRect( screen,NULL, SDL_MapRGB(screen->format, 230, 220,150));         //we have to declare background remember
    put_Text(SCREEN_WIDTH/2,GAME_NAME_Y,GAME_NAME,GameNameColor);
    for(int i=0;i<7;++i)
    {
        put_Text((SCREEN_WIDTH)/2,CREDITS_START + (i*(MENU_SPACE_LINE + GAME_FONT_SIZE)),all_credits[i],all_credits_colors[i]);
    }
    SDL_Flip(screen);

    return GSCredits;
}
int playedcontrols=0;
GameStates ShowControls()
{
   /** ALWAYS do first all event handling then rendering... */
    if(playedcontrols==0)
    {
         play_sound_effect(wav_controls,MIX_CHANNELS_CONTROLS,INFINITE_PLAY_MUSIC);
            playedcontrols=1;
    }
    else if(playedcontrols==2)
    {
            Mix_Resume(MIX_CHANNELS_CONTROLS);
    }

    //If a mouse button was pressed
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                Mix_Pause(MIX_CHANNELS_CONTROLS);
                playedcontrols=2;
                return GSMenu;
            }
        }
        else if(event.type==SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                playedcontrols=2;
                Mix_Pause(MIX_CHANNELS_CONTROLS);
                return GSMenu;
            }
        }
    }
    SDL_FillRect( screen,NULL, SDL_MapRGB(screen->format, 230, 220,150));         //we have to declare background remember
    put_Text(SCREEN_WIDTH/2,GAME_NAME_Y,GAME_NAME,GameNameColor);
    for(int i=0;i<6;++i)
    {
        put_Text((SCREEN_WIDTH)/2,CREDITS_START + (i*(MENU_SPACE_LINE + GAME_FONT_SIZE)),all_controls[i],all_controls_colors[i]);
    }
    SDL_Flip(screen);

    return GSControls;
}

bool init()
{
    //Initialise Everything


    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        global_Error = GE_SDL_NOT_SETUP;           // Set the error code
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE|SDL_FULLSCREEN );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        global_Error = GE_VIDEO_NOT_INIT;           // Set the error code
        return false;
    }
     //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        global_Error = GE_TTF_NOT_INIT;           // Set the error code
        return false;
    }

     //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        global_Error = GE_MIXER_NOT_INIT;           // Set the error code
        return false;
    }


    //Set the window caption
    SDL_WM_SetCaption( "Name of Our GAme", NULL );


    //If everything initialized fine
    return true;
}

SDL_Surface *load_image( char* filename )
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = SDL_LoadBMP( filename );

    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}

bool load_files()
{
    //Load All the required files
    for(int j=0;j<2;++j)
    {
        for(int i=0;i<NUM_TILE_TYPES;++i)
        {
            all_tiles_images[j][i] = load_image(all_tiles_bmp_names[j][i]);
            if(all_tiles_images[j][i]==NULL)
            {
                global_Error = GE_IMAGES_NOT_FOUND;           // Set the error code
                return false;
            }
        }
    }

    //Load main player images
    for(int i=0;i<2;++i)
    {
           MainPlayer_image[i] = load_image(mainplayer_bmp_name[i]);
            if(MainPlayer_image[i]==NULL)
            {
                global_Error = GE_IMAGES_NOT_FOUND;           // Set the error code
                return false;
            }
            //colorkey our player images
            Uint32 MainPlayer_colorkey = SDL_MapRGB(MainPlayer_image[i]->format,colorkey_main[0],colorkey_main[1],colorkey_main[2]);
            SDL_SetColorKey( MainPlayer_image[i], SDL_SRCCOLORKEY, MainPlayer_colorkey );
    }

    //load enemy images
    for(int j=0;j<TOTAL_ENEMIES;j++)
    {
        for(int i=0;i<2;++i)
        {
            Enemy_image[j][i] = load_image(enemy_bmp_name[j][i]);
            if(Enemy_image[j][i]==NULL)
            {
                global_Error = GE_IMAGES_NOT_FOUND;           // Set the error code
                return false;
            }
            //colorkey our player images
            Uint32 Enemy_colorkey = SDL_MapRGB(Enemy_image[j][i]->format,colorkey_main[0],colorkey_main[1],colorkey_main[2]);
            SDL_SetColorKey( Enemy_image[j][i], SDL_SRCCOLORKEY, Enemy_colorkey );
        }
    }

    fade_image = load_image(fade_bmp_name);
    if(fade_image==NULL)
    {
        global_Error = GE_IMAGES_NOT_FOUND;
        return false;
    }

    pikamania_image = load_image(pikamania_bmp_name);
    if(pikamania_image==NULL)
    {
        global_Error = GE_IMAGES_NOT_FOUND;
        return false;
    }
    lost_image = load_image(lost_bmp_name);
    if(lost_image==NULL)
    {
        global_Error = GE_IMAGES_NOT_FOUND;
        return false;
    }
    won_image = load_image(won_bmp_name);
    if(won_image==NULL)
    {
        global_Error = GE_IMAGES_NOT_FOUND;
        return false;
    }
    menu_image = load_image(menu_bmp_name);
    if(menu_image==NULL)
    {
        global_Error = GE_IMAGES_NOT_FOUND;
        return false;
    }

    main_weapon_image = load_image(main_weapon_bmp_name);
    if(main_weapon_image==NULL)
    {
        global_Error = GE_IMAGES_NOT_FOUND;
        return false;
    }
    Uint32 Weapon_colorkey = SDL_MapRGB(main_weapon_image->format,colorkey_main[0],colorkey_main[1],colorkey_main[2]);
    SDL_SetColorKey( main_weapon_image, SDL_SRCCOLORKEY, Weapon_colorkey );

    //Open the font
    font = TTF_OpenFont( "data/font.ttf", GAME_FONT_SIZE);  //give the  ttf address i have taken
    //If there was an error in loading the font
    if( font == NULL )
    {
        global_Error = GE_FONT_NOT_FOUND;           // Set the error code
        return false;
    }

    //load map
    if(!load_map(game_levels[map_num]))
    {
        global_Error = GE_MAP_NOT_FOUND;           // Set the error code
        return false;
    }




    //Load the sound effects
    wav_coin = Mix_LoadWAV( "data/music/coin.wav" );
   // wav_jump = Mix_LoadWAV( "data/music/jump.wav" );
    wav_enemy = Mix_LoadWAV( "data/music/enemy.wav" );
    wav_win = Mix_LoadWAV( "data/music/win.wav" );
    wav_lose = Mix_LoadWAV("data/music/lose.wav");
    wav_credits=Mix_LoadWAV("data/music/credits.wav");
    wav_controls=Mix_LoadWAV("data/music/controls.wav");
    wav_menu = Mix_LoadWAV("data/music/menu.wav");

    //If there was a problem loading the sound effects
    if( ( wav_coin == NULL ) ||  ( wav_enemy == NULL ) || ( wav_win == NULL ) || ( wav_lose == NULL ) )
    {
        global_Error = GE_MUSIC_NOT_FOUND;           // Set the error code
        return false;
    }
    for(int i=0;i<TOTAL_LEVELS;i++)
    {
        wav_level[i]=Mix_LoadWAV(levels_sounds[i]);
        if(wav_level[i]==NULL)
          {
            global_Error = GE_MUSIC_NOT_FOUND;           // Set the error code
            return false;
          }
    }
    //If everything loaded fine
    return true;
}

void clean_up()
{
    int i;
    //Free the images
    for(int j=0;j<2;++j)
    {
        for(i=0;i<NUM_TILE_TYPES;++i)
        {
            SDL_FreeSurface(all_tiles_images[j][i]);
        }
    }

    for(i=0;i<2;++i)
    {
        SDL_FreeSurface(MainPlayer_image[i]);
        for(int j=0;j<TOTAL_ENEMIES;j++)
        SDL_FreeSurface(Enemy_image[j][i]);
    }
    SDL_FreeSurface(main_weapon_image);
    SDL_FreeSurface(pikamania_image);
    SDL_FreeSurface(menu_image);
    SDL_FreeSurface(lost_image);
    SDL_FreeSurface(won_image);

    //Free the sound effects
    Mix_FreeChunk( wav_coin );
    Mix_FreeChunk( wav_enemy );
   // Mix_FreeChunk( wav_jump );
    Mix_FreeChunk( wav_lose );
    Mix_FreeChunk( wav_win );
    Mix_FreeChunk(wav_controls);
    Mix_FreeChunk(wav_credits);

    for(int i=0;i<3;i++)
    {
        Mix_FreeChunk(wav_level[i]);
    }
    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();
}

Tiles* all_tiles[VERT_TILES];
int num_horiz_tiles,num_enemies;
Enemy* all_enemies;
bool map_loaded=false;
bool getintfromfile(ifstream &file,int &n)
{
    file>>n;
    if(file.fail()==true)
    {
        file.close();
        return false;
    }
    return true;
}

bool load_map( char* map_name)
{
    ifstream my_map(map_name);

    if(my_map==NULL)
    {
        return false;
    }
    int num_tiles,temp;
    if(!getintfromfile(my_map,num_tiles))
    {
        return false;
    }
    if(num_tiles<(SCREEN_WIDTH/TILE_WIDTH))
    {
        return false;
    }
    num_horiz_tiles = num_tiles;

    for(int i=0;i<VERT_TILES;++i)
    {
        all_tiles[i] = new Tiles[num_tiles];
        for(int j=0;j<num_tiles;++j)
        {
            if(!getintfromfile(my_map,temp))
            {
                return false;
            }

            if(temp<0 || temp>7)
            {
                return false;
            }
            all_tiles[i][j].type = (TileTypes)temp;
        }
    }

    if(!getintfromfile(my_map,num_enemies))
    {
        return false;
    }
    all_enemies = new Enemy[num_enemies];
    int k;
    for(int i=0;i<num_enemies;++i)
    {
        if(!getintfromfile(my_map,temp))
        {
            return false;
        }
        all_enemies[i].cury = temp*TILE_HEIGHT + (TILE_HEIGHT-PLAYER_HEIGHT);
        if(!getintfromfile(my_map,temp))
        {
            return false;
        }
        all_enemies[i].curx = temp*TILE_WIDTH + (TILE_WIDTH-PLAYER_WIDTH)/2;
        all_enemies[i].dir = DLeft;
        all_enemies[i].speedx = -ENEMY_VEL_X;
        all_enemies[i].speedy = 0;
        all_enemies[i].living = mTRUE;
        all_enemies[i].health = ENEMY_HEALTH;
        k=rand()%TOTAL_ENEMIES;
        all_enemies[i].et=(EnemyTypes)k;
    }

    map_loaded = true;
    my_map.close();
    //Set up Camera
    global_Camera.x=0;
    global_Camera.y=0;
    global_Camera.w=SCREEN_WIDTH;
    global_Camera.h=SCREEN_HEIGHT;
    //Setup Player
    global_MainPlayer.curx = TILE_WIDTH;              //on 2nd tile
    global_MainPlayer.cury = SCREEN_HEIGHT - (TILE_HEIGHT + PLAYER_HEIGHT) ;  // bottom 2nd tile
    global_MainPlayer.speedx = 0;
    global_MainPlayer.speedy = 0;
    global_MainPlayer.dir  = DRight;
    global_MainPlayer.living = mTRUE;
    global_MainPlayer.health = PLAYER_HEALTH;
    //Setup Weapon
    global_weapon.set_hasgot(mFALSE);
    checksdlkeydown =0;
    return true;
}

void show_points()
{
    SDL_Surface* points=NULL;
    char text[5];
    itoa(global_points,text,10);
    points = TTF_RenderText_Solid(font,text,textColor);
    put_Text(POINTS_X,POINTS_Y,points_msg,textColor,mFALSE);
    apply_surface(POINTS_X+(GAME_FONT_SIZE*7),POINTS_Y,points,screen);
    SDL_FreeSurface(points);
}

myTF collided(Enemy e,Player p)
{
    if((e.curx+PLAYER_WIDTH)<(p.curx+global_Camera.x))
        return mFALSE;
    if((e.cury + PLAYER_HEIGHT)<p.cury)
        return mFALSE;
    if(e.curx>(p.curx + global_Camera.x + PLAYER_WIDTH))
        return mFALSE;
    if(e.cury>(p.cury + PLAYER_HEIGHT))
        return mFALSE;
    return mTRUE;
}

int fade_alpha = SDL_ALPHA_TRANSPARENT;

void display_everything()
{
    int temp = global_Camera.x/TILE_WIDTH,tx,cx;
    SDL_Rect clip;
    for(int i=0;i<VERT_TILES;++i)
    {
        tx=0;
        for(int j=temp,k=0;;++j,++k)
        {

            cx=(j*TILE_WIDTH)-global_Camera.x;
            if(cx<0)
            {
                clip.x = -cx;
                clip.y=0;
                clip.w=TILE_WIDTH-clip.x;
                clip.h=TILE_HEIGHT;
            }
            else if(cx>=(SCREEN_WIDTH-TILE_WIDTH))
            {
                clip.x=0;
                clip.y=0;
                clip.w=SCREEN_WIDTH-cx;
                clip.h=TILE_HEIGHT;
            }
            else
            {
                clip.x=0;
                clip.y=0;
                clip.w=TILE_WIDTH;
                clip.h=TILE_HEIGHT;
            }
            apply_surface(tx,i*TILE_HEIGHT,all_tiles_images[(map_num)%2][(int)all_tiles[i][j].type],screen,&clip);
            tx+=clip.w;
            if(tx>=SCREEN_WIDTH)
            {
                break;
            }
        }
    }
    show_points();
    for(int i=0;i<num_enemies;++i)
    {

         if(all_enemies[i].curx > (global_Camera.x-PLAYER_WIDTH)  && all_enemies[i].curx < (global_Camera.x+SCREEN_WIDTH) && all_enemies[i].living == mTRUE)
            {
                SDL_Rect clip={0,0,PLAYER_WIDTH,PLAYER_HEIGHT};
                if(all_enemies[i].curx<0)
                {
                    clip.x=global_Camera.x-all_enemies[i].curx;
                }
                else if((all_enemies[i].curx+PLAYER_WIDTH)>(global_Camera.x+SCREEN_WIDTH))
                {
                    clip.w=all_enemies[i].curx+PLAYER_WIDTH-(global_Camera.x+SCREEN_WIDTH);
                }
                if(all_enemies[i].cury>SCREEN_HEIGHT-PLAYER_HEIGHT)
                {
                    clip.h=global_Camera.y+SCREEN_HEIGHT-all_enemies[i].cury;
                }
                apply_surface(all_enemies[i].curx - global_Camera.x,all_enemies[i].cury,Enemy_image[(int)all_enemies[i].et][(int)all_enemies[i].dir],screen,&clip);
            }

    }
    if(global_MainPlayer.cury<(SCREEN_HEIGHT) && global_MainPlayer.cury+PLAYER_HEIGHT>=0)
    {
                SDL_Rect clip={0,0,PLAYER_WIDTH,PLAYER_HEIGHT};
                if(global_MainPlayer.cury>SCREEN_HEIGHT-PLAYER_HEIGHT)
                {
                    clip.h=global_Camera.y+SCREEN_HEIGHT-global_MainPlayer.cury;
                }
                else if((global_MainPlayer.cury<0))
                {
                    clip.y=global_Camera.y-global_MainPlayer.cury;
                }
        apply_surface(global_MainPlayer.curx,global_MainPlayer.cury,MainPlayer_image[(int)global_MainPlayer.dir],screen,&clip);
    }

    global_weapon.show(main_weapon_image,screen,global_Camera.x,global_Camera.y);

}

GameStates Play_MainGame()
{
  if(!showlastmsg)
  {
    played = mTRUE;
    won = mFALSE;
       if(playingsound==0)
    {
         play_sound_effect(wav_level[map_num],MIX_CHANNELS_LEVEL,INFINITE_PLAY_MUSIC);
            playingsound=1;
    }
    else if(playingsound==2)
    {
            Mix_Resume(MIX_CHANNELS_LEVEL);
    }
    if(isloaded==mFALSE)
    {
        if(map_num==0)
            global_points = 0;

        load_map(game_levels[map_num]);
        isloaded=mTRUE;

        /** Fade in ... */
        fade_alpha = SDL_ALPHA_OPAQUE;
        while(fade_alpha>SDL_ALPHA_TRANSPARENT)
                {
                    display_everything();
                    SDL_SetAlpha( fade_image, SDL_SRCALPHA, fade_alpha );
                    apply_surface(0,0,fade_image,screen);
                    SDL_Flip(screen);
                    fade_alpha -= FADE_ALPHA_INCREMENT;
                    SDL_Delay(FADE_DELAY);
                }

                //SDL_Delay(2000);
                while(SDL_PollEvent(&event))
                {
                    ;
                }



    }
  /** ALWAYS do first all event handling then rendering... */


    //If a mouse button was pressed
    while(SDL_PollEvent(&event))
    {

        if(event.type==SDL_KEYDOWN)
        {   checksdlkeydown=1;
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE :
                checksdlkeydown=0;
                global_MainPlayer.speedx=0;
                Mix_Pause(MIX_CHANNELS_LEVEL);
                playingsound=2;
                return GSMenu;
                break;
            case SDLK_RIGHT :
                {
                    global_MainPlayer.speedx += PLAYER_VEL_X;
                }
                break;
            case SDLK_LEFT :
                {
                    global_MainPlayer.speedx -= PLAYER_VEL_X;
                }
                break;
            case SDLK_UP :
                {
                    if(global_MainPlayer.speedy == 0)
                    {
                       // play_sound_effect(wav_jump,MIX_CHANNELS_EXTRAS);
                        global_MainPlayer.speedy = -PLAYER_VEL_Y;
                    }
                }
                break;
            case SDLK_SPACE :
                {
                       if(global_weapon.return_hasgot()==mTRUE)
                    {
                        if(global_weapon.return_state()==mFALSE)
                            play_sound_effect(wav_enemy,MIX_CHANNELS_THUNDER);
                    }
                    global_weapon.fired(global_MainPlayer.curx+global_Camera.x,global_MainPlayer.cury+global_Camera.y,global_MainPlayer.dir);

                }
                break;
            default :
                break;
            }
        }
        else  if(event.type==SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {

            case SDLK_RIGHT :
                {

                    if(checksdlkeydown==1)
                        global_MainPlayer.speedx -= PLAYER_VEL_X;

                }
                break;
            case SDLK_LEFT :
                {
                        if(checksdlkeydown==1)
                        global_MainPlayer.speedx += PLAYER_VEL_X;
                }
                break;
            default :
                break;
            }
        }
    }

    if(global_MainPlayer.speedx>0)
    {
        global_MainPlayer.dir = DRight;
    }
    else if(global_MainPlayer.speedx<0)
    {
        global_MainPlayer.dir = DLeft;
    }

    global_weapon.move(all_tiles,num_horiz_tiles,all_enemies,num_enemies,global_Camera.x,global_Camera.y);

    //Update Player Pos
    global_MainPlayer.curx+=global_MainPlayer.speedx;
    for(int i=0;i<num_enemies;++i)
    {
            if(all_enemies[i].curx > 0  && all_enemies[i].curx < (global_Camera.x+SCREEN_WIDTH-(PLAYER_WIDTH)) && all_enemies[i].living == mTRUE)
            {

                if(collided(all_enemies[i],global_MainPlayer)==mTRUE)
                {
                    isloaded = mFALSE;
                    play_sound_effect(wav_lose);
                    showlastmsg = true;
                    break;
                }
                all_enemies[i].curx += all_enemies[i].speedx;

                if(all_enemies[i].speedx!=0)
                {
                    int t1,t2,t3;
                    t1 = all_enemies[i].cury/TILE_HEIGHT;
                    t2 = (all_enemies[i].curx)/TILE_WIDTH ;
                    Tiles T1,T2;
                    T1 = all_tiles[t1][t2];
                    t3 = (all_enemies[i].curx + PLAYER_WIDTH)/TILE_WIDTH;
                    T2 = all_tiles[t1][t3];
                    if(T1.type == TTStone || T2.type == TTStone)
                    {
                        all_enemies[i].curx-=all_enemies[i].speedx;
                        all_enemies[i].speedx = -all_enemies[i].speedx;
                        all_enemies[i].dir = (all_enemies[i].dir==DLeft) ? DRight : DLeft;
                    }
                }
                if(all_enemies[i].speedy>0)
                {
                    all_enemies[i].cury +=all_enemies[i].speedy;
                    if(all_enemies[i].cury > (SCREEN_HEIGHT-PLAYER_HEIGHT))
                     {
                         all_enemies[i].living = mFALSE;
                         all_enemies[i].speedy=0;
                         continue;
                     }
                    all_enemies[i].speedy += GRAVITY;
                    if(all_enemies[i].speedy>PLAYER_MAX_VEL_Y)
                    {
                        all_enemies[i].speedy=PLAYER_MAX_VEL_Y;
                    }
                }

                if(all_enemies[i].speedy>=0 && all_enemies[i].cury<=(SCREEN_HEIGHT-TILE_HEIGHT-PLAYER_HEIGHT))
                {
                        int t1,t2,t3;
                        t2 = (all_enemies[i].curx)/TILE_WIDTH;
                        t1 = ((all_enemies[i].cury+PLAYER_HEIGHT-1)/TILE_HEIGHT)+1;
                        Tiles T1,T2;
                        T1 = all_tiles[t1][t2];
                        t3 = (all_enemies[i].curx+PLAYER_WIDTH)/TILE_WIDTH;
                        T2 = all_tiles[t1][t3];
                        if(T1.type==TTStone || T2.type==TTStone)
                        {
                            all_enemies[i].speedy = 0;
                            all_enemies[i].cury = (t1*TILE_HEIGHT) - (PLAYER_HEIGHT);
                        }
                        else
                        {
                            if(all_enemies[i].speedy==0)
                            {
                                all_enemies[i].speedy = GRAVITY;
                            }

                        }
                }


            //   t1 = all_enemies
            }

    }

   if(showlastmsg==false)
   {
    //Check collision with bricks
    if(global_MainPlayer.speedx!=0 &&global_MainPlayer.cury>=0)
    {

        int t1,t2,t3;
        t1 = global_MainPlayer.cury/TILE_HEIGHT;
        t2 = (global_Camera.x + global_MainPlayer.curx)/TILE_WIDTH ;
        Tiles T1,T2;
        T1 = all_tiles[t1][t2];
        t3 = (global_Camera.x + global_MainPlayer.curx + PLAYER_WIDTH)/TILE_WIDTH;
        T2 = all_tiles[t1][t3];
        if(T1.type == TTStone)
        {
            global_MainPlayer.curx = (t2*TILE_WIDTH + TILE_WIDTH)-global_Camera.x;
        }
        else if(T2.type == TTStone)
        {
            global_MainPlayer.curx = (t3*TILE_WIDTH - PLAYER_WIDTH)-global_Camera.x;
        }
        else if(T1.type == TTCoin)
        {
            global_points += POINTS_COIN;
             play_sound_effect(wav_coin,MIX_CHANNELS_EXTRAS);
            all_tiles[t1][t2].type = TTSky;
        }
        else if(T2.type == TTCoin)
        {
            global_points += POINTS_COIN;
            play_sound_effect(wav_coin,MIX_CHANNELS_EXTRAS);
            all_tiles[t1][t3].type = TTSky;
        }
        else if(T1.type==TTWeapon)
        {
            global_weapon.set_hasgot(mTRUE);
            all_tiles[t1][t2].type = TTSky;
        }
        else if(T2.type == TTWeapon)
        {
            global_weapon.set_hasgot(mTRUE);
            all_tiles[t1][t3].type = TTSky;
        }
        else if(T1.type == TTCup)
        {
            won = mTRUE;
            isloaded = mFALSE;
             play_sound_effect(wav_win);
            showlastmsg = true;
            global_MainPlayer.curx=t2*TILE_WIDTH;
        }
        else if(T2.type == TTCup)
        {
            won = mTRUE;
            isloaded = mFALSE;
             play_sound_effect(wav_win);
            showlastmsg = true;
            global_MainPlayer.curx=t3*TILE_WIDTH;
        }
        /**     Next check... */
        t1 = (global_MainPlayer.cury+PLAYER_HEIGHT-COLLISION_CLEARENCE)/TILE_HEIGHT;
        t2 = (global_Camera.x + global_MainPlayer.curx)/TILE_WIDTH ;
        T1 = all_tiles[t1][t2];
        t3 = (global_Camera.x + global_MainPlayer.curx + PLAYER_WIDTH)/TILE_WIDTH;
        T2 = all_tiles[t1][t3];
        if(T1.type == TTStone)
        {
            global_MainPlayer.curx = (t2*TILE_WIDTH + TILE_WIDTH)-global_Camera.x;
        }
        else if(T2.type == TTStone)
        {
            global_MainPlayer.curx = (t3*TILE_WIDTH - PLAYER_WIDTH)-global_Camera.x;
        }
        else if(T1.type == TTCoin)
        {
            global_points += POINTS_COIN;
             play_sound_effect(wav_coin,MIX_CHANNELS_EXTRAS);
            all_tiles[t1][t2].type = TTSky;
        }
        else if(T2.type == TTCoin)
        {
            global_points += POINTS_COIN;
            play_sound_effect(wav_coin,MIX_CHANNELS_EXTRAS);
            all_tiles[t1][t3].type = TTSky;
        }
        else if(T1.type==TTWeapon)
        {
            global_weapon.set_hasgot(mTRUE);
            all_tiles[t1][t2].type = TTSky;
        }
        else if(T2.type == TTWeapon)
        {
            global_weapon.set_hasgot(mTRUE);
            all_tiles[t1][t3].type = TTSky;
        }
        else if(T1.type == TTCup)
        {
            won = mTRUE;
            isloaded = mFALSE;
             play_sound_effect(wav_win);
            showlastmsg = true;
            global_MainPlayer.curx=t2*TILE_WIDTH;
        }
        else if(T2.type == TTCup)
        {
            won = mTRUE;
            isloaded = mFALSE;
             play_sound_effect(wav_win);
            showlastmsg = true;
            global_MainPlayer.curx=t3*TILE_WIDTH;
        }
    }
    //Set Camera
    if(global_MainPlayer.curx>PLAYER_MAX_X && global_Camera.x<((num_horiz_tiles*TILE_WIDTH)-SCREEN_WIDTH-1))
       {
           global_Camera.x+=(global_MainPlayer.curx-PLAYER_MAX_X);
           if(global_Camera.x>(num_horiz_tiles*TILE_WIDTH  - SCREEN_WIDTH -1))
           {
               global_Camera.x = num_horiz_tiles*TILE_WIDTH  - SCREEN_WIDTH -1;
           }
           global_MainPlayer.curx = PLAYER_MAX_X;
       }
       else if(global_MainPlayer.curx<0)
        {
            global_MainPlayer.curx = 0;
        }
        else if(global_MainPlayer.curx>(SCREEN_WIDTH-PLAYER_WIDTH-1))
        {
            global_MainPlayer.curx = SCREEN_WIDTH - TILE_WIDTH-1;
        }

        global_MainPlayer.cury+=global_MainPlayer.speedy;



      if(global_MainPlayer.speedy!=0)
    {
        global_MainPlayer.speedy += GRAVITY;
        // Do not let the velocity go beyond a certain value
        if(global_MainPlayer.speedy>PLAYER_MAX_VEL_Y)
        {
            global_MainPlayer.speedy=PLAYER_MAX_VEL_Y;
        }
        else if(global_MainPlayer.cury<0)
        {
            if(global_MainPlayer.speedy>5)
            {
            global_MainPlayer.speedy=5;
            }
            else if(global_MainPlayer.speedy<0)
        {
            global_MainPlayer.speedy+=GRAVITY;
        }

        }
    }

    //If player is going up
    if(global_MainPlayer.speedy<0 && global_MainPlayer.cury>0)
    {
        int t1,t2,t3;
        t2 = (global_Camera.x+global_MainPlayer.curx)/TILE_WIDTH;


        t1 = (((global_MainPlayer.cury-1))/TILE_HEIGHT);
        Tiles T1,T2;
        T1 = all_tiles[t1][t2];
        t3 = (global_Camera.x+global_MainPlayer.curx+PLAYER_WIDTH - COLLISION_CLEARENCE)/TILE_WIDTH;
        T2 = all_tiles[t1][t3];
        if(T1.type==TTStone || T2.type==TTStone)
        {
            global_MainPlayer.speedy = 0;
            global_MainPlayer.cury = ((t1+1)*TILE_HEIGHT) + COLLISION_CLEARENCE;
        }
        else if(T1.type == TTCoin)
        {
            global_points += POINTS_COIN;
             play_sound_effect(wav_coin,MIX_CHANNELS_EXTRAS);
            all_tiles[t1][t2].type = TTSky;
        }
        else if(T2.type == TTCoin)
        {
            global_points += POINTS_COIN;
             play_sound_effect(wav_coin,MIX_CHANNELS_EXTRAS);
            all_tiles[t1][t3].type = TTSky;
        }
        else if(T1.type==TTWeapon)
        {
            global_weapon.set_hasgot(mTRUE);
            all_tiles[t1][t2].type = TTSky;
        }
        else if(T2.type == TTWeapon)
        {
            global_weapon.set_hasgot(mTRUE);
            all_tiles[t1][t3].type = TTSky;
        }
        else if(T1.type == TTCup)
        {
            won = mTRUE;
            isloaded = mFALSE;
             play_sound_effect(wav_win);
            showlastmsg = true;
            global_MainPlayer.cury=(t1+1)*TILE_HEIGHT;
        }
        else if(T2.type == TTCup)
        {
            won = mTRUE;
            isloaded = mFALSE;
             play_sound_effect(wav_win);
            showlastmsg = true;
            global_MainPlayer.cury=(t1+1)*TILE_HEIGHT;
        }

    }
    //If player is coming down
    else if(global_MainPlayer.speedy>=0 && global_MainPlayer.cury<=(SCREEN_HEIGHT-TILE_HEIGHT-PLAYER_HEIGHT) && global_MainPlayer.cury>=0)
     {
         int t1,t2,t3;
        t2 = (global_Camera.x+global_MainPlayer.curx)/TILE_WIDTH;
        t1 = (((global_MainPlayer.cury-1)+PLAYER_HEIGHT)/TILE_HEIGHT)+1;
        Tiles T1,T2;
        T1 = all_tiles[t1][t2];
        t3 = (global_Camera.x+global_MainPlayer.curx+PLAYER_WIDTH - COLLISION_CLEARENCE)/TILE_WIDTH;
        T2 = all_tiles[t1][t3];
        if(T1.type==TTStone || T2.type==TTStone)
        {
            global_MainPlayer.speedy = 0;
            global_MainPlayer.cury = (t1*TILE_HEIGHT) - (PLAYER_HEIGHT);
        }
        else if(T1.type == TTCoin)
        {
            global_points += POINTS_COIN;
            all_tiles[t1][t2].type = TTSky;
            play_sound_effect(wav_coin,MIX_CHANNELS_EXTRAS);
        }
        else if(T2.type == TTCoin)
        {
            global_points += POINTS_COIN;
            play_sound_effect(wav_coin,MIX_CHANNELS_EXTRAS);
            all_tiles[t1][t3].type = TTSky;
        }
        else if(T1.type==TTWeapon)
        {
            global_weapon.set_hasgot(mTRUE);
            all_tiles[t1][t2].type = TTSky;
        }
        else if(T2.type == TTWeapon)
        {
            global_weapon.set_hasgot(mTRUE);
            all_tiles[t1][t3].type = TTSky;
        }
        else if(T1.type == TTCup)
        {
            won = mTRUE;
            isloaded = mFALSE;
             play_sound_effect(wav_win,1);
            showlastmsg = true;
            global_MainPlayer.cury=t1*TILE_HEIGHT-PLAYER_HEIGHT;
        }
        else if(T2.type == TTCup)
        {
            won = mTRUE;
            isloaded = mFALSE;
             play_sound_effect(wav_win,1);
            showlastmsg = true;
            global_MainPlayer.cury=t1*TILE_WIDTH-PLAYER_HEIGHT;
        }
        else
        {
            if(global_MainPlayer.speedy==0)
            {
                global_MainPlayer.speedy = GRAVITY;
            }

        }

     }

     if(global_MainPlayer.cury>(SCREEN_HEIGHT-PLAYER_HEIGHT))
        {
            isloaded=mFALSE;
             play_sound_effect(wav_lose);
            showlastmsg = true;
        }
   }
  }
  else
  {
      if(call==false)
      {
         prev_ticks=SDL_GetTicks();

         call=true;
      }
      else if(SDL_GetTicks()-prev_ticks>=WAIT_TIME_MSG)
     {
            call=false;
            showlastmsg = false;
            //Free the Events list
            while(SDL_PollEvent(&event))
            {
                ;
            }
          Mix_Pause(MIX_CHANNELS_LEVEL);
                playingsound=2;
        return GSMenu;
      }
  }
    //Render
    display_everything();
    //Show last msg for win or lose
    if(showlastmsg)
    {
        if(won==mTRUE)
          {
            map_num++;
            Mix_HaltChannel(MIX_CHANNELS_LEVEL);
            playingsound=0;
            if(map_num>=TOTAL_LEVELS)
            {
                apply_surface(160,120,won_image,screen);
                put_Text(SCREEN_WIDTH/2,50,last_msg_won,GameStatusColor);
            }
            else
            {
                /** Fade out ... */
                fade_alpha = SDL_ALPHA_TRANSPARENT;
                while(fade_alpha<SDL_ALPHA_OPAQUE)
                {
                    display_everything();
                    put_Text(SCREEN_WIDTH/2,50,msg_lvl_change,GameStatusColor);
                    SDL_SetAlpha( fade_image, SDL_SRCALPHA, fade_alpha );
                    apply_surface(0,0,fade_image,screen);
                    SDL_Flip(screen);
                    fade_alpha += FADE_ALPHA_INCREMENT;
                    SDL_Delay(FADE_DELAY);
                }

                //SDL_Delay(2000);
                while(SDL_PollEvent(&event))
                {
                    ;
                }
                 isloaded=mFALSE;
                 won=mFALSE;
                 showlastmsg=false;

                 return GSPlaying;

            }
          }
        else
         {
             apply_surface(160,120,lost_image,screen);
             put_Text(SCREEN_WIDTH/2,50,last_msg_lost,GameStatusColor);
         }
    }

    SDL_Flip(screen);
    return GSPlaying;
}

bool GameMain()
{
    switch(global_curState)
    {
        case GSSplashWelcome:
                global_curState=SplashWelcome();
            break;
        case GSMenu :
                global_curState = ShowMenu();
            break;
        case  GSPlaying :
            global_curState =  Play_MainGame();
          break;
        case GSCredits :
          global_curState = ShowCredits();

          break;
        case GSControls :
         global_curState =  ShowControls();
          break;
        case GSSplashEnd :
            global_curState = SplashEnd();
            break;
        case GSQuit :
            return true;
    }
    return false;
}
