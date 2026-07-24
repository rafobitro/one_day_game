#include "game.hpp"
#include "menu.hpp"

//const float ASPECT_RATIO = 9/9;
const int screenWidth = 800;
const int screenHeight = 450;


enum Program_Mode{
    menue,
    game
};

enum Game_State{
    alive,
    dead
};

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
    Program_Mode program_mode=game;
    Game_State game_state=alive;

	SetTargetFPS(60);

	init_game(screenWidth,screenHeight); 
  while(!WindowShouldClose()){
    if(program_mode==menue){
	  //drow_menue();
	  }
	  else if(program_mode==game){
        
      if(game_state==alive){
          if(!run_game())
              game_state=dead;
      }
      if(game_state==dead){
        //score
        WaitTime(200);
      }
    }

  }
  

    un_init_game();
    CloseWindow();
    return 0;
}
