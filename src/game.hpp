#include "raylib.h"

Vector2 ballPosition;


void init_game(int screenWidth, int screenHeight){

    ballPosition = { (float)screenWidth/3, (float)screenHeight/2 };
}

void ubdate_game(){

      if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
      if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
      if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
      if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
}

void draw_game(){

	
    
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        
        DrawText(TextFormat("BallPosition: %02.02f , %02.02f ", ballPosition.x , ballPosition.y),0,0,20,LIGHTGRAY);

        DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing();

  

}

void run_game(){
    ubdate_game();
    draw_game();
}
