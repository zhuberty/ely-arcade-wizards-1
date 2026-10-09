#include "raylib.h"
#include "resource_dir.h"
#include "arcade_input.h"
#include "GameConfig.hpp"
#include "TextureAtlas.hpp"
#include "VideoRecorder.hpp"
#include "Player.hpp"
#include <string>
#include <vector>

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(Conf::BASE_W, Conf::BASE_H, "Wizards");

    // Load Floor Tile
    std::string appDir = GetApplicationDirectory();
    std::string imgDir = appDir + "../../assets/images";

    ChangeDirectory(imgDir.c_str());
    Texture texAtlasTexture = LoadTexture("tiles.png");
    TA::get().SetTexture(texAtlasTexture);

    std::vector<std::vector<char>> mapDef(20, std::vector<char>(20, '.'));

    mapDef[10][10] = '|';

    Camera2D camera = {};
    camera.zoom = 8.0f;
    camera.offset = {Conf::BASE_W / 2, Conf::BASE_H / 2};
    camera.target = {10 * TA::TILE_SIZE + TA::TILE_SIZE / 2, 10 * TA::TILE_SIZE + TA::TILE_SIZE / 2};

    VideoRecorder recorder;
    recorder.SetMaxDuration(360);

    Player player({11 * TA::TILE_SIZE, 10 * TA::TILE_SIZE});

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        recorder.HandleInput(Conf::BASE_W, Conf::BASE_H, Conf::TARGET_FPS);

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
                if (tileChar == '|')
                {
                    TA::get().Draw("floor", {x * TA::TILE_SIZE, y * TA::TILE_SIZE}, {0, 0}, 0.0f, WHITE);
                    TA::get().Draw("grate", {x * TA::TILE_SIZE, y * TA::TILE_SIZE}, {0, 0}, 0.0f, WHITE);
                }
            }
        }

        player.Update(dt);

        EndMode2D();
        DrawFPS(0, 0);

        recorder.EndFrame();
        EndDrawing();
    }

    UnloadTexture(texAtlasTexture);
    CloseWindow();
    return 0;
}