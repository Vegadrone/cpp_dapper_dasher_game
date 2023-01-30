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

bool isOnGround(AnimData data, int windowHeight){
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData (AnimData data, float deltaTime, int maxFrame){
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime){
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame){
            data.frame = 0;
        }
    }
    return data;
}

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

    //Meglio usare una variabile così non c'è bisogno di cambiare il numero in più parti
    const int sizeOfNebulae{10};
    
    AnimData nebulae [sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/12.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }

    Texture2D background = LoadTexture("textures/far-buildings.png");

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

        Vector2 bgPos{0.0, 0.0};
        //Draw Background
        DrawTextureEx(background, bgPos, 0.0, 2.0, WHITE);

        //Ground Check
        /*
            Se metti == quando salti posY non è più uguale a wH - rH di conseguenza la velocità non
            è più zero come nell'if ma va nell'else e il rettangolo sprofonda
        */
        if (isOnGround(scarfyData, windowDimensions[1]))
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
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }
        
        //Nebula Animation
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            //Update nebula position 
            nebulae[i].pos.x += nebVel*dT;

            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
       
            //Draw Nebulae
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        //Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        //Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    CloseWindow();
}