#include "game.hpp"
#include "menu.hpp"

//const float ASPECT_RATIO = 16/9;
const int screenWidth = 800;
const int screenHeight = 450;


enum Program_Mode{
    menue,
    game
};

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
    Program_Mode program_mode=game;

	SetTargetFPS(60);

	init_game(screenWidth,screenHeight); 
  while(!WindowShouldClose()){
    if(program_mode==menue){
	  //drow_menue();
	  }
	  else if(program_mode==game){
        run_game();
    }

  }
  

    un_init_game();
    CloseWindow();
    return 0;
}
