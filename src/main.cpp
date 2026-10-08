#include "raylib.h"
#include "resource_dir.h"
#include "arcade_input.h"
#include "TextureAtlas.hpp"
#include "VideoRecorder.hpp"
#include <string>
#include <vector>

int main(void)
{
    const int screenBaseWidth = 1280;
    const int screenBaseHeight = 720;
    const int targetFps = 60;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenBaseWidth, screenBaseHeight, "Wizards");

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

    VideoRecorder recorder;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_R) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)))
        {
            if (!recorder.IsRecording())
            {
                SetTargetFPS(targetFps);
                recorder.Start(screenBaseWidth, screenBaseHeight, targetFps);
            }
            else
            {
                recorder.Stop();
                SetTargetFPS(0);
            }
        }

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

        DrawFPS(0, 0);
        EndMode2D();

        if (recorder.IsRecording())
        {
            recorder.CaptureFrame();
            if (!recorder.IsRecording()) // auto-stopped at max duration
                SetTargetFPS(0);
        }
        recorder.DrawOverlay();
        EndDrawing();
    }

    UnloadTexture(texAtlasTexture);
    CloseWindow();
    return 0;
}