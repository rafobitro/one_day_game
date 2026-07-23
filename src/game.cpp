#include "game.hpp"

float velocity;
float gravity;
Vector2 ballPosition;
Texture2D background;

void init_game(int screenWidth, int screenHeight){
    velocity = 0;
    gravity = 15;
    ballPosition = { (float)screenWidth/3, (float)screenHeight/2 };
    Image background_image= LoadImage("background.png");
    ImageResize(&background_image,screenWidth,screenHeight);
    background = LoadTextureFromImage(background_image);
    UnloadImage(background_image);

}

void un_init_game(){
  UnloadTexture(background);
}

void run_phisics(){
    float delta_time = GetFrameTime();
    velocity -= delta_time *  gravity * gravity  * 0.5;
    ballPosition.y -= velocity *delta_time;
}

void ubdate_game(){
    if (IsKeyPressed(KEY_SPACE)) velocity=120;
    run_phisics();
}

void draw_game(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_background();
    DrawCircleV(ballPosition, 20, MAROON);
    EndDrawing();
}

void draw_background(){
    DrawTexture(background,0,0,WHITE);
}


void run_game(){
    ubdate_game();
    draw_game();
}


