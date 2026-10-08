#include "raylib.h"
#include "resource_dir.h"
#include "arcade_input.h"
#include <string>
#include <vector>

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Wizards");

    // Load Floor Tile
    std::string appDir = GetApplicationDirectory();
    std::string imgDir = appDir + "../../assets/images";
    ChangeDirectory(imgDir.c_str());
    Texture texAtlas = LoadTexture("tiles.png");

    std::vector<std::vector<char>> mapDef(20, std::vector<char>(20, '.'));

    mapDef[10][10] = '|';

    Camera2D camera = {};
    camera.zoom = 2.0f;
    camera.offset = {0, 0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        BeginMode2D(camera);

            ClearBackground(BLACK);

            for (size_t y = 0; y < mapDef.size(); y++)
            {
                for (size_t x = 0; x < mapDef[y].size(); x++)
                {
                    char tileChar = mapDef[y][x];
                    if (tileChar == '.')
                        DrawTexturePro(texAtlas, {0, 0, 16, 16}, {(float)x * 16, (float)y * 16, 16, 16}, {0, 0}, 0.0f, WHITE);
                    if (tileChar == '|') {
                        DrawTexturePro(texAtlas, {0, 0, 16, 16}, {(float)x * 16, (float)y * 16, 16, 16}, {0, 0}, 0.0f, WHITE);
                        DrawTexturePro(texAtlas, {0, 32, 16, 16}, {(float)x * 16, (float)y * 16, 16, 16}, {0, 0}, 0.0f, WHITE);                 
                    }
                }
            }

        DrawFPS(0, 0);
        EndMode2D();
        EndDrawing();
    }

    UnloadTexture(texAtlas);
    CloseWindow();
    return 0;
}