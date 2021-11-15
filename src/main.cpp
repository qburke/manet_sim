/* Code adapated from Lazy Foo' Productions SDL tutorial examples.
Simulates a dynamic environment for performing experiments on manets.
This file renders the environment described by an Environment class.
*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "environments.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			SimpleEnvironment env(SCREEN_WIDTH, SCREEN_HEIGHT);

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				// Draw data
				SDL_Rect fillRect = { 0, 0, 1, 1 };
				for(int i = 0; i < SCREEN_WIDTH; i++) {
					for(int j = 0; j < SCREEN_HEIGHT; j++) {
						fillRect.x = i;
						fillRect.y = j;
						SDL_SetRenderDrawColor( gRenderer, env.dataRAt(i ,j), env.dataGAt(i ,j), env.dataBAt(i ,j), 0xFF );		
						SDL_RenderFillRect( gRenderer, &fillRect );
					}
				}

				// Draw devices
				int r = 2;
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				for(auto loc : env.devices())
				{
					fillRect.x = loc.pos.x - r;
					fillRect.y = loc.pos.y - r;
					fillRect.w = 2*r;
					fillRect.h = 2*r;
					SDL_RenderFillRect( gRenderer, &fillRect );
					//SDL_RenderDrawPoint(gRenderer, loc.pos.x, loc.pos.y);
				}

				//Update screen
				SDL_RenderPresent( gRenderer );

				// Step environment
				env.step();
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}