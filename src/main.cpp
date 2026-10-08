#include "raylib.h"
#include "resource_dir.h"
#include "arcade_input.h"
#include "TextureAtlas.hpp"
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
    Texture texAtlasTexture = LoadTexture("tiles.png");
    TA::get().SetTexture(texAtlasTexture);

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
                        TA::get().Draw("floor", {x * TA::TILE_SIZE, y * TA::TILE_SIZE}, {0, 0}, 0.0f, WHITE);
                    if (tileChar == '|') {
                        TA::get().Draw("floor", {x * TA::TILE_SIZE, y * TA::TILE_SIZE}, {0, 0}, 0.0f, WHITE);
                        TA::get().Draw("grate", {x * TA::TILE_SIZE, y * TA::TILE_SIZE}, {0, 0}, 0.0f, WHITE);                 
                    }
                }
            }

        DrawFPS(0, 0);
        EndMode2D();
        EndDrawing();
    }

    UnloadTexture(texAtlasTexture);
    CloseWindow();
    return 0;
}