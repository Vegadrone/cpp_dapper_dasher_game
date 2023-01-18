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

        //Rectangle Jump
        if (IsKeyPressed(KEY_SPACE))
        {        
            velocity -= 10;
        }
        posY += velocity;
        
        //Stop Drawing
        EndDrawing();
    }

    CloseWindow();
}