/*
Faça um moonlander:

- A nave tem que ter combustível -- FEITO
- A nave quando acelerar para cima tem que começar a perder a velocidade até começar a ganhar a velocidade -- FEITO
- O jogo é scroll infinito para direita (Gerar o mapa ou não se ficar muito difícil)
- Tem que ter um score
- Algumas bases reabastacem, outras não
- Tem que ter um menu, com as opções: Iniciar, Pontuações (só as que fizeram enquanto o jogo está rodando, não precisa salvar), Sair 

*/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const float GRAVIDADE = 1.0;
    float acelGravidade = 0;
    
    Rectangle playerFoguete = {screenWidth/2 - 20, screenHeight/2 - 20, 40 , 40};
    float velFoguete = 2.0;
    float acelFoguete = 0;
    int combustivel = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] - moonlander");

    Image fogueteDesativado = LoadImage("../image/rocket.png");
    Image fogueteAtivado = LoadImage("../image/rocketactive.png");
    Texture2D foguete = LoadTextureFromImage(fogueteDesativado);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        playerFoguete.y += GRAVIDADE + GRAVIDADE*acelGravidade;
        
        if (combustivel != 0) {
            if(IsKeyDown(KEY_K)) {
                foguete = LoadTextureFromImage(fogueteAtivado);
                playerFoguete.y -= velFoguete + velFoguete * acelFoguete;
                acelFoguete += 0.1f;
                acelGravidade = 0.0001f;
                combustivel--;
            } else {
                foguete = LoadTextureFromImage(fogueteDesativado);
                acelFoguete = 0.0004f;
                acelGravidade += 0.1f;
            }
        } else {
            foguete = LoadTextureFromImage(fogueteDesativado);
        }

        

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawTexture(foguete, playerFoguete.x, playerFoguete.y, WHITE);
            DrawText(TextFormat("%i", combustivel), 100, 40, 40, LIGHTGRAY);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(foguete);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}