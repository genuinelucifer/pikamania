#include "myfuncs.h"                     // Custom header file

int main( int argc, char* args[] )
{
    srand(time(NULL));
    //Quit flag
    bool quit=false;
    //Frame rate determiner
    Uint32 time_now;

    if(!init() || !load_files())
        return (int)(getErrorCode());              // Initialise and load everything

    //While the user hasn't quit
    while( quit == false )
    {
        /** Get current Time.. */
         time_now = SDL_GetTicks();

        /** Do everything here... */
        quit=GameMain();

        /**If we have done drawing before the time for 1 frame ends.. */
        if( (SDL_GetTicks()-time_now) < 1000 / FRAMES_PER_SECOND )
       {
            /**Sleep the remaining frame time.. */
           SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - (SDL_GetTicks()-time_now) );
       }
    }

    //Clean up
    clean_up();

    return (int)(getErrorCode());
}
