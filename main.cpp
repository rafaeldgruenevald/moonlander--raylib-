/*

Faça um moonlander:

- A nave tem que ter combustível -- FEITO
- A nave quando acelerar para cima tem que começar a perder a velocidade até começar a ganhar a velocidade -- FEITO
- O jogo é scroll infinito para direita (Gerar o mapa ou não se ficar muito difícil) -- FEITO
- Tem que ter um score -- FEITO
- Algumas bases reabastacem, outras não -- FEITO
- Tem que ter um menu, com as opções: Iniciar, Pontuações (só as que fizeram enquanto o jogo está rodando, não precisa salvar), Sair -- FEITO 

*/

#include "raylib.h"

void resetarValores (float& gravidade, float& acelGravidade, float& bateuMorreu, float& velFoguete, float& acelFoguete, int& combustivel, bool& playerMorto, bool& baseAbastesivel, float& playerFogueteX, float& playerFogueteY, int& score, float& baseX, float& obstaculoX, float& obstaculoY) 
{
    gravidade = 3.0;
    acelGravidade = 0;
    bateuMorreu = 3.5;
    velFoguete = 2.0;
    acelFoguete = 0;
    combustivel = 1000;
    playerMorto = false;
    baseAbastesivel = true;
    playerFogueteX = (GetScreenWidth()/2) - 20;
    playerFogueteY = (GetScreenHeight()/2) - 20;
    score = 0;
    baseX = 800;
    obstaculoX = 800;
    obstaculoY = 0;
}

void scoreSystem (int& score, int& hiscore)
{
    if (score > hiscore) {
        hiscore = score;
    }
}

void checarColiPlayerBase (Rectangle& playerFoguete, Rectangle& base, Texture2D& baseDeReabastecimento, Image& baseNaoAtivavel, float& gravidade, float& acelGravidade, float& bateuMorreu, float& velFoguete, Texture2D& foguete, Image& fogueteExplodiu, bool& playerMorto, int& telaDoJogo, bool& baseAbastesivel, int& combustivel, int& score, int& hiscore) {
    if (CheckCollisionRecs(playerFoguete, base)) {
        baseDeReabastecimento = LoadTextureFromImage(baseNaoAtivavel);

        if (gravidade*acelGravidade >= bateuMorreu) {
            velFoguete = 0;
            foguete = LoadTextureFromImage(fogueteExplodiu);
            playerMorto = true;
            scoreSystem(score, hiscore);
            telaDoJogo = 2;
        } else if (baseAbastesivel) {
            combustivel += 100;
            baseAbastesivel = false;
        }
        gravidade = 0;
        acelGravidade = 0;
    } else {
        gravidade = 3.0;
    }
}


void resetarBase (float& baseX, float& baseY, bool& baseAbastesivel, Texture2D& baseDeReabastecimento, Image& baseAtivavel, Image& baseNaoAtivavel, int& sorte)
{
    
    baseX = 800;
    baseY = GetRandomValue(200,395);
    if (sorte % 2 == 0) {
        baseAbastesivel = true;
        baseDeReabastecimento = LoadTextureFromImage(baseAtivavel);
    } else {
        baseDeReabastecimento = LoadTextureFromImage(baseNaoAtivavel);
    }

}

void resetarObstaculo (int& ObstaculoY) {
    ObstaculoY = GetRandomValue(40, 398);
}


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    int score = 0;
    int hiscore = 0;
    int passcore = 0;
    
    int sorte;
    int sorte2;
    
    float gravidade = 3.0;
    float acelGravidade = 0;
    float bateuMorreu = 3.5;
    
    Rectangle playerFoguete = {screenWidth/2 - 20, screenHeight/2 - 20, 40 , 40};
    float velFoguete = 2.0;
    float acelFoguete = 0;
    int combustivel = 1000;
    bool playerMorto = false;

    Rectangle base = {900, 395, 80, 40};
    float velBase = 3.0;
    int baseY;
    int baseX = GetRandomValue(800, 1400);
    bool baseAbastesivel = true;

    Rectangle base2 = {900, 395, 80, 40};
    float velBase2 = 3.0;
    int base2Y;
    bool base2Abastesivel = false;

    Rectangle obstaculo = {900, 0, 80, 450};
    float velObstaculo = 3.0;
    int obstaculoY = GetRandomValue(10,398);
    int obstaculoX = GetRandomValue(800, 1200);


    Rectangle chao = {0, 430, 800, 20};

    Rectangle Background = {0, 0, 1000, 1000};


    int telaDoJogo = 0;

    InitWindow(screenWidth, screenHeight, "raylib [core] - moonlander");

    Image moonlanderBackground = LoadImage("../image/background.png");
    Texture2D background = LoadTextureFromImage(moonlanderBackground);

    Image starsBackground = LoadImage("../image/stars.png");
    Texture2D stars = LoadTextureFromImage(starsBackground);
    
    Image fogueteDesativado = LoadImage("../image/rocket.png");
    Image fogueteAtivado = LoadImage("../image/rocketActive.png");
    Image fogueteExplodiu = LoadImage("../image/rocketExplosion.png");
    Texture2D foguete = LoadTextureFromImage(fogueteDesativado);

    Image baseAtivavel = LoadImage("../image/plataformUsable.png");
    Image baseNaoAtivavel = LoadImage("../image/plataformUnsable.png");
    Texture2D baseDeReabastecimento = LoadTextureFromImage(baseAtivavel);
    Texture2D baseDeReabastecimento2 = LoadTextureFromImage(baseAtivavel);

    Image obstaculoImg = LoadImage("../image/obstacle.png");
    Texture2D obstaculuzada = LoadTextureFromImage(obstaculoImg);

    Image groundBase = LoadImage("../image/groundzin.png");
    Texture2D groundzada = LoadTextureFromImage(groundBase);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        baseY = GetRandomValue(200,395);
        base2Y = GetRandomValue(200,395);
        int base2X = GetRandomValue(800, 1000);
        
        switch(telaDoJogo)
        {
            
            case 0:
            {
                if (IsKeyPressed(KEY_ENTER)) {
                    telaDoJogo = 1;
                }

                if (IsKeyPressed(KEY_P)) {
                    telaDoJogo = 3;
                }

                if (IsKeyPressed(KEY_S)) {
                    telaDoJogo = 4;
                }

                base.y = baseY;
                base.x = baseX;
                base2.y = base2Y;
                base2.y = base2X;
                obstaculo.y = obstaculoY;
                obstaculo.x = obstaculoX;
                

            } break;
            
            case 1:
            {
                score++;

                base.x -= velBase;
                base2.x -= velBase2;

                obstaculo.x -= velObstaculo;
                
                
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

                checarColiPlayerBase(playerFoguete, base, baseDeReabastecimento, baseNaoAtivavel, gravidade, acelGravidade, bateuMorreu, velFoguete, foguete, fogueteExplodiu, playerMorto, telaDoJogo, baseAbastesivel, combustivel, score, hiscore);
                checarColiPlayerBase(playerFoguete, base2, baseDeReabastecimento2, baseNaoAtivavel, gravidade, acelGravidade, bateuMorreu, velFoguete, foguete, fogueteExplodiu, playerMorto, telaDoJogo, base2Abastesivel, combustivel, score, hiscore);
                
                if(CheckCollisionRecs(base, base2)) {
                    sorte2 = GetRandomValue(0, 1000) * sorte;
                    resetarBase(base2.x, base2.y, base2Abastesivel, baseDeReabastecimento2, baseAtivavel, baseNaoAtivavel, sorte2);
                }
                
                if (CheckCollisionRecs(playerFoguete, chao)) {
                    foguete = LoadTextureFromImage(fogueteExplodiu);
                    playerMorto = true;
                    scoreSystem(score, hiscore);
                    telaDoJogo = 2;
                }

                if (CheckCollisionRecs(playerFoguete, obstaculo)) {
                    foguete = LoadTextureFromImage(fogueteExplodiu);
                    playerMorto = true;
                    scoreSystem(score, hiscore);
                    telaDoJogo = 2;
                }
                
                
                if (base.x < 0) {
                    sorte = GetRandomValue(0, 1000);
                    resetarBase(base.x, base.y, baseAbastesivel, baseDeReabastecimento, baseAtivavel, baseNaoAtivavel, sorte);
                } else if (base2.x < 0) {
                    sorte2 = GetRandomValue(0, 1000) * sorte;
                    resetarBase(base2.x, base2.y, base2Abastesivel, baseDeReabastecimento2, baseAtivavel, baseNaoAtivavel, sorte2);
                } else if (obstaculo.x <= 0) {
                    resetarObstaculo(obstaculoY);
                    obstaculo.x = 800;
                }

                if (CheckCollisionRecs(obstaculo, base)|| obstaculo.x == base2.x) {
                    resetarBase(base.x, base.y, baseAbastesivel, baseDeReabastecimento, baseAtivavel, baseNaoAtivavel, sorte);
                    resetarBase(base2.x, base2.y, base2Abastesivel, baseDeReabastecimento2, baseAtivavel, baseNaoAtivavel, sorte2);
                    baseX = GetRandomValue(800, 1400);
                    base2X = GetRandomValue(900, 1000);
                }



            } break;

            case 2:
            {
                passcore = score;
                if(IsKeyPressed(KEY_ENTER)) {
                    sorte = GetRandomValue(0, 1000);
                    sorte2 = GetRandomValue(0, 1000) * sorte;
                    resetarObstaculo(obstaculoY);
                    resetarValores(gravidade, acelGravidade, bateuMorreu, velFoguete, acelFoguete, combustivel, playerMorto, baseAbastesivel, playerFoguete.x, playerFoguete.y, score, base.x, obstaculo.x, obstaculo.y);
                    resetarBase(base.x, base.y, baseAbastesivel, baseDeReabastecimento, baseAtivavel, baseNaoAtivavel, sorte);
                    resetarBase(base2.x, base2.y, base2Abastesivel, baseDeReabastecimento2, baseAtivavel, baseNaoAtivavel, sorte2);
                    telaDoJogo = 0;
                }
            } break;

            case 3:
            {
                if (IsKeyPressed(KEY_ENTER)) {
                    telaDoJogo = 0;
                }
            } break;

            case 4:
            {
                if (IsKeyPressed(KEY_Y)) {
                    CloseWindow();
                }

                if (IsKeyPressed(KEY_N)) {
                    telaDoJogo = 0;
                }
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
                    DrawTexture(background, Background.x, Background.y, WHITE);
                    DrawText("moonlander...", 280, screenHeight/2 - 80, 40, LIGHTGRAY);
                    DrawText("APERTE [ENTER] PARA COMEÇAR A JOGAR!", 60, screenHeight/2, 30, LIGHTGRAY);
                    DrawText("APERTE [P] PARA VER SUA PONTUAÇÃO!", 70, screenHeight/2 + 40, 30, LIGHTGRAY);
                    DrawText("SAIR", screenWidth/2 - 50, screenHeight/2 + 80, 30, LIGHTGRAY);
                } break;

                case 1:

                    DrawTexture(obstaculuzada, obstaculo.x, obstaculo.y, WHITE);
                {
                    DrawText(TextFormat("PONTUAÇÃO: %i", score), 100, 80, 40, LIGHTGRAY);
                    
                    DrawTexture(foguete, playerFoguete.x, playerFoguete.y, WHITE);
                    DrawText(TextFormat("%i", combustivel), 100, 40, 40, LIGHTGRAY);
            
                    DrawTexture(baseDeReabastecimento, base.x, base.y, WHITE);
                    DrawTexture(baseDeReabastecimento2, base2.x, base2.y, WHITE);

                    DrawTexture(groundzada, chao.x, chao.y, WHITE);

                } break;

                case 2:
                {
                    DrawText("VOCÊ MORREU!", 250, screenHeight/2 - 80, 40, LIGHTGRAY);
                    DrawText(TextFormat("SUA PONTUAÇÃO FOI: %i", score), 180, screenHeight/2 + 40, 30, LIGHTGRAY);
                    DrawText(TextFormat("SUA MELHOR PONTUAÇÃO FOI: %i", hiscore), 100, screenHeight/2 + 80, 30, LIGHTGRAY);
                    DrawText("PRESSIONE [ENTER] PARA IR AO MENU INICIAL", 30, screenHeight/2 + 120, 30, LIGHTGRAY);
                } break;

                case 3:
                {
                    DrawTexture(stars, Background.x, Background.y, WHITE);
                    DrawText(TextFormat("SUA MAIOR PONTUAÇÃO FOI: %i", hiscore), screenWidth/2 - 250, screenHeight/2 - 40, 30, LIGHTGRAY);
                    DrawText(TextFormat("NA ULTIMA PARTIDA SUA PONTUAÇÃO FOI: %i", passcore), screenWidth/2 - 350, screenHeight/2 + 40, 30, LIGHTGRAY);
                    DrawText("APERTE [ENTER] PARA VOLTAR", screenWidth/2 - 250, screenHeight/2 + 120, 30, LIGHTGRAY);
                } break;

                case 4:
                {
                    DrawText("TEM CERTEZA QUE DESEJA SAIR? [Y/N]", screenWidth/2 - 330, screenHeight/2, 30, LIGHTGRAY);
                } break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);
    UnloadTexture(stars);
    UnloadTexture(obstaculuzada);
    UnloadTexture(groundzada);
    UnloadTexture(foguete);
    UnloadTexture(baseDeReabastecimento);
    UnloadTexture(baseDeReabastecimento2);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
