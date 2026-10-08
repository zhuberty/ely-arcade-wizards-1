#pragma once

#include "game_utils.h"
#include <unordered_map>
#include <array>
#include <string>

namespace TAK
{
    inline const std::unordered_map<std::string, Indices> map = {
        {"floor", {0, 0}},
        {"wall", {0, 1}},
        {"grate", {0, 2}},
    };
}