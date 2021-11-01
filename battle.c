#include "raylib.h"
#include <math.h>

int main(void) {
    const int width = 800;
    const int height = 600;
    
    InitWindow(width, height, "Island Survival");
    
    Texture2D heartImg = LoadTexture("Assets/heart.png");
    Texture2D waterImg = LoadTexture("Assets/water.png");
    Texture2D meatImg = LoadTexture("Assets/meat.png");
    Texture2D mushroomImg = LoadTexture("Assets/mushroom.png");
    Texture2D bulletImg = LoadTexture("Assets/bullet.png");
    Texture2D waterHealth = LoadTexture("Assets/waterHealth.png");
    Texture2D playerImg = LoadTexture("Assets/playerImg.png");
    Texture2D gameImg = LoadTexture("Assets/icon.png");
    
    Texture2D imgToRender;
    
    int object = GetRandomValue(1,3);
    float healthLevel = 120;
    float waterHealthLevel = 120;
    
    Image iconImage = LoadImage("Assets/icon.png");
    
    SetWindowIcon(iconImage);
    
    float speed = 4.7;
    
    SetTargetFPS(60);
    
    Vector2 ballP = {(float)width/2, (float)height/2 + 300 - 100};
    Vector2 bullet = {ballP.x - 25, ballP.y - 25};
    Vector2 ballObject = {(float)100, (float)100};
    float radius1 = 30.0;
    float radius2 = 35.0;
    
    int ballObjectX = 3.5;
    int bulletSpeed = 16;
    
    int score = 0;
    
    bool bulletG = true;
    bool lose = false;
    bool playerRun = false;
    
    while(!WindowShouldClose()) {
        
        healthLevel -= 0.03;
        waterHealthLevel -= 0.03;
        
        ballObject.x += ballObjectX;
        
       if (IsKeyDown(KEY_Q)) {
           CloseWindow();
       }
       
       if (bulletG) {
       bullet.y = ballP.y;
       bullet.x = ballP.x;
       }
       

        if (IsKeyDown(KEY_RIGHT)) ballP.x += speed;
        if (IsKeyDown(KEY_R)) playerRun = true;
        if (IsKeyDown(KEY_LEFT)) ballP.x -= speed;
        if (IsKeyDown(KEY_D)) ballP.x += speed;
        if (IsKeyDown(KEY_A)) ballP.x -= speed;
        if (IsKeyDown(KEY_SPACE)) {
            bulletG = false;
        }
      
        if (!bulletG) {
            bullet.y -= bulletSpeed;
        }
        
        if (bullet.y <= 0) {
            bulletG = true;
        }
        
        if (CheckCollisionCircles(ballObject, radius1, bullet, radius2)) {
            bulletG = true;
            ballObject.x = GetRandomValue(50, 750);
            ballObject.y = GetRandomValue(50, 170);
            score ++;
            object = GetRandomValue(1,3);
            
            if (object == 1) {
                waterHealthLevel += 4;
            }
            if (object == 2 || object == 3) {
                healthLevel += 2.7;
            }
        }
        
        if (healthLevel >= 121) {
            healthLevel = 120;
        }
        
        if (waterHealthLevel >= 121) {
            waterHealthLevel = 120;
        }
        
        if (object == 1) {
            imgToRender = waterImg;
        }
        
        if (object == 2) {
            imgToRender = meatImg;
        }
        
        if (object == 3) {
            imgToRender = mushroomImg;
        }
        
        if (ballP.x <= 50) {
            ballP.x = 50;
        } else if (ballP.x >= 749) {
            ballP.x = 749;
        }
        
        if (ballObject.x <= 0) {
            ballObjectX = 3.5;
        } else if (ballObject.x >= 749) {
            ballObjectX = -3.5;
        }
        
        if (healthLevel <= 0 || waterHealthLevel <= 0) {
            lose = true;
        }
        
        
        
        BeginDrawing();

           ClearBackground(WHITE);
          
           
           if(!lose && playerRun) {DrawTexture(bulletImg, bullet.x + 10, bullet.y + 40, WHITE);
           
           //DrawCircleV(ballP, 50, DARKBLUE);
           
           DrawRectangle(660, 10, healthLevel, 30, RED);
           DrawRectangle(660, 50, waterHealthLevel, 30, DARKBLUE);
           
           DrawText(TextFormat("Score: %i", score), 10, 10, 35, LIGHTGRAY);
           DrawTexture(heartImg, 600, 10, WHITE);
           DrawTexture(waterHealth, 600, 60, WHITE);
           DrawTexture(imgToRender, ballObject.x, ballObject.y, WHITE);
           DrawTexture(playerImg, ballP.x, ballP.y, WHITE);
           }
           
           if (lose && playerRun) DrawText("You Lost!", 360, 240, 60, LIGHTGRAY);
           
           if (!playerRun) {
               DrawText("Island Survival", width/2 - 220, height/2 - 200, 60, BLACK);
               DrawText("Press R To Play", width/2 - 175, height/2 + 200, 40, BLACK);
               DrawTexture(gameImg, width/2 - 100, height/2 - 100, WHITE);
           }
           
        EndDrawing();
    }    
    
    CloseWindow();
    
    return 0;
}