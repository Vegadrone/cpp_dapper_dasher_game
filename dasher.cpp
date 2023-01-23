//Libraries
#include "raylib.h"

//Main function
int main(){
    
    //Window dimensions
    const int windowWidth {800};
    const int windowHeight {500};

    //Rectangle /Char velocity
    int velocity {};
    // nebula x velocity frame per second
    int nebVel{-600};

    //Accelleration due to gravity ((pixels * second) * second)
    const int gravity {1'000};

    //Initialize the window
    //Mettilo SEMPRE prima del caricamento delle texture o da errori!
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    //Textures
    //Scarfy var
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //Nebula var
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    /*
    Invece di inizializzare tutto separatamente si può farlo dentro parentesi graffe.
    Per capire quali paramatei utilizzare e in che ordine fare click destro sul tipo sepciale, 
    andare su peek e poi peek definition.
    */
    Rectangle nebulaRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};



    //is in Air?
    bool isInAir{};
    //JumpVelocity pixels * seconds
    const int JumpVel{-600};

    //Animation frame
    int frame{};

    //Amount of time  before we update animation frame
    const float updateTime{1.0/12.0};
    // Scarfy running time animation
    float runningTime{};

        // Setting FPS
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
            // In questo caso il rettangolo/character è a terra quindi setto a false
            //  Update running time animation
            runningTime += dT;

            if (runningTime >= updateTime)
            {
                runningTime = 0.0;

                // update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
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

        //Update nebula position 
        nebulaPos.x += nebVel*dT;

        //Update Scarfy Position
        scarfyPos.y += velocity*dT;

        
        
        //Draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        //Draw Nebulas
        DrawTextureRec(nebula, nebulaRec,nebulaPos, WHITE);
        
        //Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}