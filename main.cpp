/*
Faça um moonlander:

- A nave tem que ter combustível -- FEITO
- A nave quando acelerar para cima tem que começar a perder a velocidade até começar a ganhar a velocidade -- FEITO
- O jogo é scroll infinito para direita (Gerar o mapa ou não se ficar muito difícil)
- Tem que ter um score
- Algumas bases reabastacem, outras não -- FEITO
- Tem que ter um menu, com as opções: Iniciar, Pontuações (só as que fizeram enquanto o jogo está rodando, não precisa salvar), Sair 

*/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    float gravidade = 3.0;
    float acelGravidade = 0;
    float bateuMorreu = 3.5;
    
    Rectangle playerFoguete = {screenWidth/2 - 20, screenHeight/2 - 20, 40 , 40};
    float velFoguete = 2.0;
    float acelFoguete = 0;
    int combustivel = 600;
    bool playerMorto = false;

    Rectangle base = {screenWidth/2 - 40, 400, 80, 40};
    bool baseAbastesivel = true;

    int telaDoJogo = 0;

    InitWindow(screenWidth, screenHeight, "raylib [core] - moonlander");

    Image fogueteDesativado = LoadImage("../image/rocket.png");
    Image fogueteAtivado = LoadImage("../image/rocketActive.png");
    Image fogueteExplodiu = LoadImage("../image/rocketExplosion.png");
    Texture2D foguete = LoadTextureFromImage(fogueteDesativado);

    Image baseAtivavel = LoadImage("../image/plataformUsable.png");
    Image baseNaoAtivavel = LoadImage("../image/plataformUnsable.png");
    Texture2D baseDeReabastecimento = LoadTextureFromImage(baseAtivavel);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(telaDoJogo)
        {
            case 0:
            {
                if (IsKeyPressed(KEY_ENTER)) {
                    telaDoJogo = 1;
                }
            } break;
            
            case 1:
            {
                acelGravidade += 0.1f;
                playerFoguete.y += gravidade + gravidade*acelGravidade;
        
                if (combustivel != 0 && !playerMorto) {
                    if(IsKeyDown(KEY_K)) {
                        foguete = LoadTextureFromImage(fogueteAtivado);
                        playerFoguete.y -= velFoguete + velFoguete * acelFoguete;
                        acelFoguete += 0.1f;
                        acelGravidade = 0.0001f;
                        combustivel--;
                    } else {
                        foguete = LoadTextureFromImage(fogueteDesativado);
                        acelFoguete = 0.0004f;
                    }
                }

                if(CheckCollisionRecs(playerFoguete, base)) {
                    baseDeReabastecimento = LoadTextureFromImage(baseNaoAtivavel);
            
                    if (gravidade*acelGravidade >= bateuMorreu) {
                        velFoguete = 0;
                        foguete = LoadTextureFromImage(fogueteExplodiu);
                        playerMorto = true;
                        telaDoJogo = 2;
                    } else if (baseAbastesivel) {
                        combustivel += 100;
                        baseAbastesivel = false;
                    }
                    gravidade = 0;
                } else {
                    gravidade = 3.0;
                }
            } break;

            case 2:
            {

            } break;
        
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            switch (telaDoJogo)
            {
                case 0:
                {
                    DrawText("moonlander", 280, screenHeight/2 - 80, 40, LIGHTGRAY);
                    DrawText("APERTE [ENTER] PARA COMEÇAR A JOGAR!", 60, screenHeight/2, 30, LIGHTGRAY);
                } break;

                case 1:
                {
                    DrawTexture(foguete, playerFoguete.x, playerFoguete.y, WHITE);
                    DrawText(TextFormat("%i", combustivel), 100, 40, 40, LIGHTGRAY);
            
                    DrawTexture(baseDeReabastecimento, base.x, base.y, WHITE); 

                } break;

                case 2:
                {
                    DrawText("VOCÊ MORREU!", 250, screenHeight/2 - 80, 40, LIGHTGRAY);
                    DrawText("SUA PONTUAÇÃO FOI: XXXX", 180, screenHeight/2 + 40, 30, LIGHTGRAY);
                    DrawText("SUA MELHOR PONTUAÇÃO FOI: XXXX", 100, screenHeight/2 + 80, 30, LIGHTGRAY);
                } break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(foguete);
    UnloadTexture(baseDeReabastecimento);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}