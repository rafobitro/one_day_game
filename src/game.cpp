#include "game.hpp"

float velocity;
float gravity;
Vector2 ballPosition;
Texture2D background;
int background_start;
float background_speed;
float delta_time;

void init_game(int screenWidth, int screenHeight){
    background_start = 0;
    background_speed = 100;
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
    velocity -= delta_time *  gravity * gravity  * 0.5;
    ballPosition.y -= velocity *delta_time;
}

void ubdate_game(){
    background_start -= delta_time*background_speed;
    if(background_start == -background.width) background_start = 0; 
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
    DrawTexture(background,background_start,0,WHITE);
    DrawTexture(background,background_start+background.width,0,WHITE);
}


void run_game(){
    delta_time=GetFrameTime();
    ubdate_game();
    draw_game();
}


