//Libraries
#include "raylib.h"

//Main function
int main(){
    
    //Window dimensions
    const int windowWidth {800};
    const int windowHeight {500};

    //Rectangle /Char velocity
    int velocity {};

    //Accelleration due to gravity ((pixels * second) * second)
    const int gravity {1'000};

    //Initialize the window
    //Mettilo SEMPRE prima del caricamento delle texture o da errori!
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    //Texture
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //is in Air?
    bool isInAir{};
    //JumpVelocity pixels * seconds
    const int JumpVel{-600};

    //Setting FPS
    SetTargetFPS(60);

    //GameLoop
    while (!WindowShouldClose())
    {   
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //deltaTime const
        const float dT {GetFrameTime()};

        //Ground Check
        /*
            Se metti == quando salti posY non è più uguale a wH - rH di conseguenza la velocità non
            è più zero come nell'if ma va nell'else e il rettangolo sprofonda
        */
        if (scarfyPos.y >= (windowHeight - scarfyRec.height))
        {
            velocity = 0;
            //In questo caso il rettangolo/character è a terra quindi setto a false
            isInAir = false;
        }
        else
        {
            velocity += gravity*dT;
            // In questo caso il rettangolo/character è in aria quindi setto a true
            isInAir = true;
        }
        
        //Rectangle Jump
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {        
            velocity += JumpVel;
        }        

        //Update Position
        scarfyPos.y += velocity*dT;

        //Draw rectangle/character
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
        //Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}