#include "game.hpp"

float velocity;
float gravity;
Vector2 ballPosition;
Texture2D backgrounds[5];
float background_1_start;
float background_2_start;
float background_speed;
float delta_time;
int i , j;

void init_game(int screenWidth, int screenHeight){
    i=GetRandomValue(0,2);
    j=GetRandomValue(0,2);
    background_1_start = 0;
    background_2_start = screenWidth;
    background_speed = 100;
    velocity = 0;
    gravity = 15;
    ballPosition = { (float)screenWidth/3, (float)screenHeight/2 };
    Image background_image_1= LoadImage("background_1.png");
    ImageResize(&background_image_1,screenWidth,screenHeight);
    Image background_image_2= LoadImage("background_2.png");
    ImageResize(&background_image_2,screenWidth,screenHeight);
    Image background_image_3= LoadImage("background_3.png");
    ImageResize(&background_image_3,screenWidth,screenHeight);


    backgrounds[0] = LoadTextureFromImage(background_image_1);
    backgrounds[1] = LoadTextureFromImage(background_image_2);
    backgrounds[2] = LoadTextureFromImage(background_image_3);
    
    UnloadImage(background_image_1);
    UnloadImage(background_image_2);
    UnloadImage(background_image_3);

}

void un_init_game(){
  UnloadTexture(backgrounds[0]);
  UnloadTexture(backgrounds[1]);
  UnloadTexture(backgrounds[2]);

}

void run_phisics(){
    velocity -= delta_time *  gravity * gravity  * 0.5;
    ballPosition.y -= velocity *delta_time;
}


void ubdate_game() {
    float bg_width = (float)backgrounds[0].width;

    // 1. Move both positions independently at exact same speed
    background_1_start -= delta_time * background_speed;
    background_2_start -= delta_time * background_speed;

    // 2. When background 1 leaves left side, wrap it to the right of background 2
    if (background_1_start <= -bg_width) {
        // Wrap seamless position past background 2
        background_1_start = background_2_start + bg_width;
        // Pick a new random image for slot i
        i = GetRandomValue(0, 2);
    }

    // 3. When background 2 leaves left side, wrap it to the right of background 1
    if (background_2_start <= -bg_width) {
        // Wrap seamless position past background 1
        background_2_start = background_1_start + bg_width;
        // Pick a new random image for slot j
        j = GetRandomValue(0, 2);
    }

    if (IsKeyPressed(KEY_SPACE)) velocity = 120;
    run_phisics();
}


void draw_game(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_background();
    DrawCircleV(ballPosition, 20, MAROON);
    EndDrawing();
}

void draw_background() {
    DrawTexture(backgrounds[i],  background_1_start, 0.0f , WHITE);
    DrawTexture(backgrounds[j],  background_2_start, 0.0f , WHITE);
}


void run_game(){
    delta_time=GetFrameTime();
    ubdate_game();
    draw_game();
}


