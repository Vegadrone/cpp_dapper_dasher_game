//Libraries
#include "raylib.h"

//Main function
int main(){
    
    //Window dimensions
    const int windowWidth {800};
    const int windowHeight {500};

    //Rectangle dimensions
    const int rectWidth {50};
    const int rectHeight{80};

    //Rectangle position
    int posY {windowHeight - rectHeight};

    //Rectangle velocity
    int velocity {};

    //Accelleration due to gravity ((pixels * frame) * frame)
    const int gravity {1};

    //is in Air?
    bool isInAir{};
    //JumpVelocity
    const int JumpVel{-20};

    //Initialize the window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");
    
    //Setting FPS
    SetTargetFPS(60);
    //GameLoop
    while (!WindowShouldClose())
    {   
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //Draw rectangle
        DrawRectangle((windowWidth/2), posY, rectWidth, rectHeight, BLUE);

        //Ground Check
        /*
            Se metti == quando salti posY non è più uguale a wH - rH di conseguenza la velocità non
            è più zero come nell'if ma va nell'else e il rettangolo sprofonda
        */
        if (posY >= (windowHeight - rectHeight))
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity;
            isInAir = true;
        }
        
        //Rectangle Jump
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {        
            velocity += JumpVel;
        }        

        //Update Position
        posY += velocity;
        
        //Stop Drawing
        EndDrawing();
    }

    CloseWindow();
}