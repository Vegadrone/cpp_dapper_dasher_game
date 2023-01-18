//Libraries
#include "raylib.h"

//Main function
int main(){

    int width {800};
    int height {500};

    InitWindow(width, height, "Dapper Dasher");
    

    SetTargetFPS(60);
    while (true)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
    
}