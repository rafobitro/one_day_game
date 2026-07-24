#include "game.hpp"
#include <iostream>
float velocity;
float gravity;
float jump_velocity;
Vector2 player_position;
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
int score;
int hiscore=0;

Vector2 mousePoint;


void init_game(int screenWidth, int screenHeight){
    Vector2 mousePoint = {0,0};
    score = 0; 
    pipe_distance =0.4*screenWidth;
    pipe_gap=100;
    pipe_1_start=screenWidth;
    pipe_2_start=pipe_1_start+pipe_distance;
    pipe_3_start=pipe_2_start+pipe_distance;
    bg_1=GetRandomValue(0,2);
    bg_2=GetRandomValue(0,2);
    pipe_1_gap= GetRandomValue(1,6);
    pipe_2_gap= GetRandomValue(1,6);
    pipe_3_gap= GetRandomValue(1,6);

    bg_1_start = 0;
    bg_2_start = screenWidth;
    bg_speed = 0;
    pipe_speed = 0;
    velocity = 0;
    gravity = 30;
    jump_velocity= 210;
    player_position = { (float)screenWidth/3, (float)screenHeight/2 };

    Image background_image_1= LoadImage("background_1.png");
    ImageResize(&background_image_1,screenWidth,screenHeight);
    Image background_image_2= LoadImage("background_2.png");
    ImageResize(&background_image_2,screenWidth,screenHeight);
    Image background_image_3= LoadImage("background_3.png");
    ImageResize(&background_image_3,screenWidth,screenHeight);
    Image pipe = LoadImage("pipe.png");
    ImageResize(&pipe,50,50);
    Image pipe_head = LoadImage("pipe_head.png");
    ImageResize(&pipe_head,50,50);

    ImageColorReplace(&pipe,Color{0,255,0,255},Color{0,0,0,0,});
    ImageColorReplace(&pipe_head,Color{0,255,0,255},Color{0,0,0,0,});

    pipes[2] = LoadTextureFromImage(pipe_head);
    ImageRotate(&pipe_head,180);

    backgrounds[0] = LoadTextureFromImage(background_image_1);
    backgrounds[1] = LoadTextureFromImage(background_image_2);
    backgrounds[2] = LoadTextureFromImage(background_image_3);
    
    pipes[0] = LoadTextureFromImage(pipe);
    pipes[1] = LoadTextureFromImage(pipe_head);
    
    
    UnloadImage(background_image_1);
    UnloadImage(background_image_2);
    UnloadImage(background_image_3);

    UnloadImage(pipe);
    UnloadImage(pipe_head);

}

void un_init_game(){
  UnloadTexture(backgrounds[0]);
  UnloadTexture(backgrounds[1]);
  UnloadTexture(backgrounds[2]);


  UnloadTexture(pipes[0]);
  UnloadTexture(pipes[1]);
  UnloadTexture(pipes[2]);

}

void run_phisics(){
    velocity -= delta_time *  gravity * gravity  * 0.5;
    player_position.y -= velocity *delta_time;
}


void ubdate_game() {
    float bg_width = (float)backgrounds[0].width;
    bg_speed=90+(score*0.03);
    pipe_speed=120+(score*0.05);

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
      pipe_1_gap= GetRandomValue(1,6);
    }

    if(pipe_2_start <= -100){
      pipe_2_start+= pipe_distance*3;
      pipe_2_gap= GetRandomValue(1,6);
    }

    if(pipe_3_start <= -100){
      pipe_3_start+= pipe_distance*3;
      pipe_3_gap= GetRandomValue(1,6);
    }

    if (IsKeyPressed(KEY_SPACE)) velocity = jump_velocity;
    run_phisics();
}


void draw_game(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_background();
    draw_pipes();
    DrawCircleV(player_position, 20, MAROON);
    DrawText(TextFormat("Score: %08i", score), 0, 0, 30, GREEN);
    EndDrawing();
}

void draw_background() {
    DrawTexture(backgrounds[bg_1],  bg_1_start, 0.0f , WHITE);
    DrawTexture(backgrounds[bg_2],  bg_2_start, 0.0f , WHITE);
}

void draw_pipes() {
    for(int i=0;i<10;i++){
      if(i==pipe_1_gap - 1){
        DrawTexture(pipes[2],pipe_1_start,i*50 -1,WHITE);

        DrawTexture(pipes[1],pipe_1_start-1,(i+3)*50+1 ,WHITE);
        
        i+=3;
        continue;
      }
      DrawTexture(pipes[0],pipe_1_start,i*50,WHITE);
    }
    
    for(int i=0;i<10;i++){
      if(i==pipe_2_gap-1){
        
        DrawTexture(pipes[2],pipe_2_start,i*50 ,WHITE);

        DrawTexture(pipes[1],pipe_2_start-1,(i+3)*50+1 ,WHITE);
        
        i+=3;
        continue;
      }
      DrawTexture(pipes[0],pipe_2_start,i*50,WHITE);
    }
    
    for(int i=0;i<10;i++){
      if(i==pipe_3_gap-1){
        
        DrawTexture(pipes[2],pipe_3_start,i*50 ,WHITE);

        DrawTexture(pipes[1],pipe_3_start-1,(i+3)*50+1 ,WHITE);
        
        i+=3;
        continue;
      }
      DrawTexture(pipes[0],pipe_3_start,i*50,WHITE);
    }

}

bool colison_detection(){
    if(player_position.x>=pipe_1_start && player_position.x<=pipe_1_start+50 ){
        if(player_position.y<pipe_1_gap*50 ||
           player_position.y>pipe_1_gap*50+100){
           //player is dead
           return true;
        }
        else{
          score++;
        }
    }
    if(player_position.x>=pipe_2_start && player_position.x<=pipe_2_start+50 ){
        if(player_position.y<pipe_2_gap*50 ||
           player_position.y>pipe_2_gap*50+100){
           //player is dead
           return true;
        }
        else{
          score++;
        }
    }
    if(player_position.x>=pipe_3_start && player_position.x<=pipe_3_start+50 ){
        if(player_position.y<pipe_3_gap*50 ||
           player_position.y>pipe_3_gap*50+100){
           //player is dead
           return true;
        }
        else{
          score++;
        }
    }
    return false;
}

bool run_game(){
    delta_time=GetFrameTime();
    ubdate_game();
    draw_game();
    if(colison_detection()){
      hiscore=std::max(score,hiscore);
      return false;
    }
    return true;
}

bool score_menue(){
    mousePoint=GetMousePosition();
    





    BeginDrawing();

    //DrawRectangle(100, 50, 600, 350, GRAY);
    if(score==hiscore)
        DrawText(TextFormat("NEW RECORD Score: %08i", score), 200, 80, 20, BLUE);
    else
        DrawText(TextFormat("Score: %08i", score), 200, 80, 20, RED);
        DrawText(TextFormat("HiScore: %08i", hiscore), 200, 120, 20, GREEN);
        Rectangle replay_bt= {200,200,200,50};
        DrawRectangleRec(replay_bt ,GREEN);
        DrawText("Press to replay    or pres ENTER to replay ",220,215, 20,WHITE);
        if (CheckCollisionPointRec(mousePoint, replay_bt) ){
                     
            DrawRectangleRec(replay_bt ,LIME);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                return true;
            
        }
        if(IsKeyPressed(KEY_ENTER))
            return true;
        

    EndDrawing();
    




    return false;
    EndDrawing();
}

