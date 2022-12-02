//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdio>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>
#include "character.h"
#include "LTexture.h"
#include "healthbar.h"

using namespace std;
const int SCREEN_WIDTH = 1440;  //Screen dimension constants
const int SCREEN_HEIGHT = 810;

int block_x = SCREEN_WIDTH/16;
int block_y = SCREEN_HEIGHT/9;

enum game_state {				//game states
	start,						//just entered game
	explanation,				//game background detail explanation
	enter_stage,				//enter battling stage
	student_attacking,  		//student draw card and attack
	professor_attacking,		//professor attack student
	gatcha,						//draw a test paper
	no_school,					//student be defeated by professor
	get_f,						//student defeated boss but did not get all paper
	get_aplus					//student defeated boss and got all paper
};
game_state state = start;	  //define state as the variable indicates current game state
int stage = 1;				  //stage indicate which stage now is in
	
bool init();				  //Starts up SDL and creates window

bool loadMedia();     		  //Loads media

void close();				  //Frees media and shuts down SDL

SDL_Window* gWindow = NULL;	  //The window we'll be rendering to

#ifndef _GRENDERER
#define _GRENDERER
SDL_Renderer* gRenderer = NULL;//The window renderer
#endif

SDL_Surface* gScreenSurface = NULL;

#ifndef _GFONT
#define _GFONT 
TTF_Font *gFont = NULL;
#endif

int probability(double hit_rate, double avoid_rate){		//function of hitting of not
	srand(time(NULL));
	double rate = pow(hit_rate * (1-avoid_rate),0.5);
	rate *= 100;
	if( (rand()%100+1) < rate )	return 1 ;
	else						return 0 ;
}



//Mouse button sprites


//Buttons objects

//Texture wrapper class

//The mouse button



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
		//Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}
		//Create window
	gWindow = SDL_CreateWindow( "A+ or F", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	
	//Create renderer for window
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/ );
	if( gRenderer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	
	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		success = false;
	}	
	gScreenSurface = SDL_GetWindowSurface( gWindow );
	if( gScreenSurface == NULL )
	{
		printf( "gScreenSurface could not be created! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	

	return success;
}


LTexture start_texture ;  				//texture of start scene
LTexture explanation_texture ;			//texture of explanation scene
LTexture burning_texture ;				//texture of burning small icon
LTexture stunning_texture ; 			//texture of stunning small icon
LTexture claw_texture ;					//texture of claw(attack of professor)
LTexture get_f_texture ;				//texture of getting f end
LTexture professor_texture[6] ;			//texture of professor
LTexture stage_background_texture[6];	//texture of battle backgrounds
LTexture healthbar_texture ;			//texture of healthbar


bool loadMedia()
{
	//Loading success flag
	bool success = true;
	
	if( !start_texture.loadFromFile( "img/background.bmp" ) ){
		printf( "Failed to load start texture!\n" );			success = false;	}
	if( !explanation_texture.loadFromFile( "img/explanation.bmp" ) ){
		printf( "Failed to load explanation texture!\n" );		success = false;	}
	if( !burning_texture.loadFromFile( "img/fire.bmp" ) ){
		printf( "Failed to load burning texture!\n" );			success = false;	}
	if( !stunning_texture.loadFromFile( "img/stun.bmp" ) ){
		printf( "Failed to load stunning texture!\n" );			success = false;	}
	if( !claw_texture.loadFromFile( "img/claw.bmp" ) ){
		printf( "Failed to load claw texture!\n" );				success = false;	}
	if( !get_f_texture.loadFromFile( "img/get_f.bmp" ) ){
		printf( "Failed to load get_f texture!\n" );			success = false;	}
	if( !professor_texture[1].loadFromFile( "img/monster_1.bmp" ) ){
		printf( "Failed to load monster 1 texture!\n" );		success = false;	}
	if( !professor_texture[2].loadFromFile( "img/monster_2.bmp" ) ){
		printf( "Failed to load monster 2 texture!\n" );		success = false;	}
	if( !professor_texture[3].loadFromFile( "img/monster_3.bmp" ) ){
		printf( "Failed to load monster 3 texture!\n" );		success = false;	}
	if( !professor_texture[4].loadFromFile( "img/monster_4.bmp" ) ){
		printf( "Failed to load monster 4 texture!\n" );		success = false;	}
	if( !professor_texture[5].loadFromFile( "img/monster_5.bmp" ) ){
		printf( "Failed to load monster 5 texture!\n" );		success = false;	}
	if( !stage_background_texture[1].loadFromFile( "img/stage_background_1.bmp" ) ){
		printf( "Failed to load stage 1 bg texture!\n" );		success = false;	}
	if( !stage_background_texture[2].loadFromFile( "img/stage_background_2.bmp" ) ){
		printf( "Failed to load stage 2 bg texture!\n" );		success = false;	}
	if( !stage_background_texture[3].loadFromFile( "img/stage_background_3.bmp" ) ){
		printf( "Failed to load stage 3 bg texture!\n" );		success = false;	}
	if( !stage_background_texture[4].loadFromFile( "img/stage_background_4.bmp" ) ){
		printf( "Failed to load stage 4 bg texture!\n" );		success = false;	}
	if( !stage_background_texture[5].loadFromFile( "img/stage_background_5.bmp" ) ){
		printf( "Failed to load stage 5 bg texture!\n" );		success = false;	}
	if( !healthbar_texture.loadFromFile( "img/healthbar.bmp" ) ){
		printf( "Failed to load healthbar texture!\n" );		success = false;	}

//    gFont = TTF_OpenFont( "img/lazy.ttf", 28 );
//    if( gFont == NULL )
//	{
//		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
//		success = false;
//	}
	return success;
}

void close()
{
	//Free loaded image
	start_texture.free();		
	explanation_texture.free();	
	burning_texture.free();		
	stunning_texture.free();		
	claw_texture.free();			
	get_f_texture.free();		
	for(int i=0;i<6;i++){
		stage_background_texture[i].free();
		professor_texture[i].free();
	}
	
	
	TTF_CloseFont( gFont );
	gFont = NULL;
	
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	
	
	//Quit SDL subsystems
	IMG_Quit();
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
			
			bool quit = false;	//Main loop flag

			SDL_Event e;		//Event handler
			
			student_class student;
			professor_class* professor;
			professor = new professor_class [6];
			for(int i=0;i<5;i++)	{ professor[i] = professor_class(i); }
			professor[5] = professor_class(0);
			healthbar_class student_healthbar( block_x * 5, 45 + block_y * 4, student );
			healthbar_class * professor_healthbar ;
			professor_healthbar = new healthbar_class [6];
			for(int i=0;i<5;i++)	{ professor_healthbar[i] = healthbar_class( block_x * 8 - 332+38 , 5 , professor[i] ); }
			
			
			
			SDL_Rect student_burn_rect 		= { block_x*2  		, block_y*5	 	, block_x	 , block_y	 }; //student burning icon position
			SDL_Rect student_stun_rect 		= { block_x*2  		, block_y*6		, block_x	 , block_y   };//student stunning icon position
			SDL_Rect professor_burn_rect 	= { block_x*8 + 332, block_y*0	 	, 40		 , 40		 }; //professor burning icon position
			SDL_Rect professor_stun_rect 	= { block_x*8 + 372 , block_y*0		, 40		 , 40	 	 }; //professor stunning icon position
			SDL_Rect professor_pos_rect 	= { block_x*3  , block_y*0 + 40 , block_x*10 , block_y*4 };//professor on stage position
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
					else if(state == start){
						start_texture.render(0,0);//Render texture to screen
						SDL_RenderPresent( gRenderer );//update screen
						
						if(e.type == SDL_KEYDOWN){
							
							switch( e.key.keysym.sym )
                	        {
                	    	    case SDLK_SPACE:
                	        	    state = explanation;
                	        		break;
                   	     	}
						}
					}
					else if (state == explanation){
						explanation_texture.render(0,0);//Render texture to screen
						//here to render the explanation words 
						//or put the words in the explanation_texture
						SDL_RenderPresent( gRenderer );//Update screen
						if(e.type == SDL_KEYDOWN){
							switch( e.key.keysym.sym )
                   	    	{
                   	 	    case SDLK_SPACE:
                   	     	    state = enter_stage;
                   	     	    break;
                   	    	}
						}
					}
					else if (state == enter_stage || state == student_attacking || state == professor_attacking){
						stage_background_texture[stage].render(0,0);//Render texture to screen
						if (!student.burning){ burning_texture.render( student_burn_rect.x , student_burn_rect.y, &student_burn_rect ); }
						if (!student.stunning){ stunning_texture.render( student_stun_rect.x , student_stun_rect.y, &student_stun_rect );	}
						if (!professor[stage].burning){ burning_texture.render( professor_burn_rect.x , professor_burn_rect.y, &professor_burn_rect) ; }
						if (!professor[stage].stunning){ stunning_texture.render( professor_stun_rect.x , professor_stun_rect.y, &professor_stun_rect ); }
						
						professor_texture[stage].render( professor_pos_rect.x , professor_pos_rect.y , &professor_pos_rect );
						
						
						professor_healthbar[stage].render();	//render healthbar
						student_healthbar.render();				//render healthbar
						
						SDL_RenderPresent( gRenderer );//Update screen
						
						if ( state == enter_stage ){
							//tell player what ability that enemy posesses
							
							
						}
						else if( state == student_attacking ){
							//if mouse is on card: show detail
							
							//professor get hurt 
							//professor died or not
							
							//deal with card effect
							
							
						}
						else if( state == professor_attacking ){
							
							if(!professor[stage].stunning){
								student.hurt( probability( professor[ stage ].hit_rate, student.avoid_rate ) * professor[ stage ].attack );

								switch ( professor[ stage ].special ){
									case health_to_attack:
									if (student.burning == true)	student.burning = false;
									if (student.stunning == true)	student.stunning = false;
									break;
									
									
									case swifty:
									if (student.burning == true)	student.burning = false;
									if (student.stunning == true)	student.stunning = false;
									break;
									
									
									case armored:
									if (student.burning == true)	student.burning = false;
									if (student.stunning == true)	student.stunning = false;
									break;
									
									
									case stun:
									if(student.stunning == false && professor[stage].stun_counter >= 6){
										student.stunning == true;
										professor[stage].stun_counter = 0;
									}
									else{
										if(professor[stage].stun_counter >= 2)
											professor[stage].stun_counter = 0;
										else
											professor[stage].stun_counter +=1;
										if (student.stunning == true){ student.stunning = false;}
									}
									
									if (student.burning == true){ student.burning = false;}
									break;
									
										
									case firing:
									if(student.burning == false && professor[stage].ignite_counter >= 5){
										student.burning == true;
										professor[stage].ignite_counter = 0;
									}
									else{
										if(professor[stage].ignite_counter >= 5)
											professor[stage].ignite_counter = 0;
										else
											professor[stage].ignite_counter +=1;
									}
									if(student.stunning == true){ student.stunning = false;}
									break;
									
								}
								
							}
							
							if( student.burning == true){ student.hurt(3); }
							if( student.alive() == false ){	state = no_school; }
						}
					
						
					}
					else if(state == gatcha){
						//
					}
					else if(state == no_school){
						//wasted animation
					}
					else if(state == get_f){
						//wasted animation
					}
					else if(state == get_aplus){
						
					}
					
				}
				
				
			}
		}
	}

	//Free resources and close SDL
	close();
	
	return 0;
}
