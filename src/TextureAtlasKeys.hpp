#pragma once

#include "game_utils.h"
#include <unordered_map>
#include <array>
#include <string>

struct AtlasTexture
{
    Indices indices;
    int endFrame; // a texture with 3 animation frames would have an endframe of 3
};

namespace TAK
{
    inline const std::unordered_map<std::string, AtlasTexture> map = {
        {"floor", {{0, 0}, 1}},
        {"wall", {{0, 1}, 1}},
        {"grate", {{0, 2}, 1}},
        {"player.stand.s", {{0, 3}, 1}},
        {"player.walk.s", {{0, 4}, 12}},
        {"player.walk.n", {{0, 5}, 12}},
    };
}