//Libraries
#include "raylib.h"

//Main function
int main(){
    
    //Window dimensions
    const int windowWidth {800};
    const int windowHeight {500};
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

        //Stop Drawing
        EndDrawing();
    }
    
    CloseWindow();
}