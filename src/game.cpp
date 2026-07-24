#include "game.hpp"

float velocity;
float gravity;
Vector2 ballPosition;
Texture2D backgrounds[3];
Texture2D pipes[3];
float bg_1_start;
float bg_2_start;
float pipe_1_start;
float pipe_2_start;
float pipe_3_start;
float bg_speed;
float pipe_speed;
float delta_time;
int bg_1 , bg_2;
int pipe_1_gap;
int pipe_2_gap;
int pipe_3_gap;
int pipe_distance;
int pipe_gap;

void init_game(int screenWidth, int screenHeight){
    pipe_distance =0.4*screenWidth;
    pipe_gap=100;
    pipe_1_start=screenWidth/2;
    pipe_2_start=pipe_1_start+pipe_distance;
    pipe_3_start=pipe_2_start+pipe_distance;
    bg_1=GetRandomValue(0,2);
    bg_2=GetRandomValue(0,2);
    pipe_1_gap= GetRandomValue(1,7);
    pipe_2_gap= GetRandomValue(1,7);
    pipe_3_gap= GetRandomValue(1,7);

    bg_1_start = 0;
    bg_2_start = screenWidth;
    bg_speed = 60;
    pipe_speed = 90;
    velocity = 0;
    gravity = 15;
    ballPosition = { (float)screenWidth/3, (float)screenHeight/2 };

    Image background_image_1= LoadImage("background_1.png");
    ImageResize(&background_image_1,screenWidth,screenHeight);
    Image background_image_2= LoadImage("background_2.png");
    ImageResize(&background_image_2,screenWidth,screenHeight);
    Image background_image_3= LoadImage("background_3.png");
    ImageResize(&background_image_3,screenWidth,screenHeight);
    Image pipe = LoadImage("pipe.png");
    ImageResize(&pipe,50,50);
    Image pipe_head = LoadImage("pipe_head.png");
    ImageResize(&pipe,50,50);
    //Image pipe_head_reverse = pipe_head;
  

    backgrounds[0] = LoadTextureFromImage(background_image_1);
    backgrounds[1] = LoadTextureFromImage(background_image_2);
    backgrounds[2] = LoadTextureFromImage(background_image_3);
    
    pipes[0] = LoadTextureFromImage(pipe);
    pipes[1] = LoadTextureFromImage(pipe_head);
   // pipes[2] = LoadTextureFromImage(pipe_head_reverse);
    
    
    UnloadImage(background_image_1);
    UnloadImage(background_image_2);
    UnloadImage(background_image_3);

    UnloadImage(pipe);
//    UnloadImage(pipe_head);
  //  UnloadImage(pipe_head_reverse);

}

void un_init_game(){
  UnloadTexture(backgrounds[0]);
  UnloadTexture(backgrounds[1]);
  UnloadTexture(backgrounds[2]);


  UnloadTexture(pipes[0]);
  UnloadTexture(pipes[1]);
 // UnloadTexture(pipes[2]);

}

void run_phisics(){
    velocity -= delta_time *  gravity * gravity  * 0.5;
    ballPosition.y -= velocity *delta_time;
}


void ubdate_game() {
    float bg_width = (float)backgrounds[0].width;

    bg_1_start -= delta_time * bg_speed;
    bg_2_start -= delta_time * bg_speed;

    if (bg_1_start <= -bg_width) {
        bg_1_start = bg_2_start + bg_width;
        bg_1 = GetRandomValue(0, 2);
    }

    if (bg_2_start <= -bg_width) {
        bg_2_start = bg_1_start + bg_width;
        bg_2 = GetRandomValue(0, 2);
    }

    pipe_1_start -= delta_time * pipe_speed;
    pipe_2_start -= delta_time * pipe_speed;
    pipe_3_start -= delta_time * pipe_speed;
    
    if(pipe_1_start <= -100){
      pipe_1_start+= pipe_distance*3;
      pipe_1_gap= GetRandomValue(1,7);
    }

    if(pipe_2_start <= -100){
      pipe_2_start+= pipe_distance*3;
      pipe_2_gap= GetRandomValue(1,7);
    }

    if(pipe_3_start <= -100){
      pipe_3_start+= pipe_distance*3;
      pipe_3_gap= GetRandomValue(1,7);
    }

    if (IsKeyPressed(KEY_SPACE)) velocity = 120;
    run_phisics();
}


void draw_game(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_background();
    draw_pipes();
    DrawCircleV(ballPosition, 20, MAROON);
    EndDrawing();
}

void draw_background() {
    DrawTexture(backgrounds[bg_1],  bg_1_start, 0.0f , WHITE);
    DrawTexture(backgrounds[bg_2],  bg_2_start, 0.0f , WHITE);
}

void draw_pipes() {
    for(int i=0;i<10;i++){
      if(i==pipe_1_gap){
        i++;
        continue;
      }
      DrawTexture(pipes[0],pipe_1_start,i*50,WHITE);
    }
    
    for(int i=0;i<10;i++){
      if(i==pipe_2_gap){
        i++;
        continue;
      }
      DrawTexture(pipes[0],pipe_2_start,i*50,WHITE);
    }
    
    for(int i=0;i<10;i++){
      if(i==pipe_3_gap){
        i++;
        continue;
      }
      DrawTexture(pipes[0],pipe_3_start,i*50,WHITE);
    }

}

void run_game(){
    delta_time=GetFrameTime();
    ubdate_game();
    draw_game();
}


