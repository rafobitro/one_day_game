#include "game.hpp"
#include "menu.hpp"

const int screenWidth = 800;
const int screenHeight = 450;


enum Program_Mode{
    menue,
    game
};


int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
    Program_Mode program_state=game;

	SetTargetFPS(60);

	init_game(screenWidth,screenHeight); 
  while(!WindowShouldClose()){
        
      if(program_state==game){
          if(!run_game())
              program_state=menue;
      }
      if(program_state==menue){
        //score
        if(score_menue()){
            program_state=game;
            init_game(screenWidth,screenHeight);
        }
      }

  }
  

    un_init_game();
    CloseWindow();
    return 0;
}
