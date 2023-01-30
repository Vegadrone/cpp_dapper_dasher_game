//Libraries
#include "raylib.h"

//Create a custom type
struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


//Main function
int main(){
    
    //Array
    int windowDimensions [2];
    windowDimensions [0] = 512;
    windowDimensions [1] = 380;

    //Rectangle /Char velocity
    int velocity {};
    // nebula x velocity frame per second
    int nebVel{-200};

    //Accelleration due to gravity ((pixels * second) * second)
    const int gravity {1'000};

    //Initialize the window
    //Mettilo SEMPRE prima del caricamento delle texture o da errori!
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    //Textures
    //Scarfy var
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.runningTime = 0;
    scarfyData.updateTime = 1.0/12.0;

    //Nebula var
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    /*
    Invece di inizializzare tutto separatamente si può farlo dentro parentesi graffe.
    Per capire quali paramatei utilizzare e in che ordine fare click destro sul tipo sepciale, 
    andare su peek e poi peek definition.
    */
    AnimData nebData {
        {0.0, 0.0, nebula.width/8, nebula.height/8},//nebRectangle
        {windowDimensions[0], windowDimensions[1] - nebula.height/8},//Vector 2 Pos
        0, //int frame
        1.0/12.0, //float updateTime
        0 //float runningTime
    };

    AnimData nebData2{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8}, // nebRectangle
        {windowDimensions[0] + 300, windowDimensions[1] - nebula.height / 8}, // Vector 2 Pos
        0,
        1.0/16.0,
        0
    };

    AnimData nebulae [10]{};

    for (int i = 0; i < 10; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/12.0;
        nebulae[i].pos.x = windowDimensions[0] += 300;
    }

    //is in Air?
    bool isInAir{};
    //JumpVelocity pixels * seconds
    const int JumpVel{-600};

    // Setting FPS
    SetTargetFPS(60);

    //GameLoop
    while (!WindowShouldClose())
    {   
        //deltaTime const
        const float dT {GetFrameTime()};
        
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //Ground Check
        /*
            Se metti == quando salti posY non è più uguale a wH - rH di conseguenza la velocità non
            è più zero come nell'if ma va nell'else e il rettangolo sprofonda
        */
        if (scarfyData.pos.y >= (windowDimensions[1] - scarfyData.rec.height))
        {
            velocity = 0;
            // In questo caso il rettangolo/character è a terra quindi setto a false
            isInAir = false;
        }
        else
        {
            velocity += gravity*dT;
            // In questo caso il rettangolo/character è in aria quindi setto a true
            isInAir = true;
        }
        
        //Jump Check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {        
            velocity += JumpVel;
        }

        //Update Scarfy Position
        scarfyData.pos.y += velocity*dT;

        //Scarfy Animation
        if(!isInAir){
            //  Update running time animation
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                // update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }
        
        //Nebula Animation
        for (int i = 0; i < 10; i++)
        {
            //Update nebula position 
            nebulae[i].pos.x += nebVel*dT;

            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;

                // update animation frame
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            }
            //Draw Nebulas
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        //Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        //Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}