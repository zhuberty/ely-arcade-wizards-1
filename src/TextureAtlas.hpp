// given a texture atlas, provide tools surrounding fetching and drawing textures by name
#pragma once

#include <unordered_map>
#include <string>

#include "raylib.h"
#include "TextureAtlasKeys.hpp"

class TextureAtlas
{
public:
    static TextureAtlas& instance()
    {
        static TextureAtlas inst;
        return inst;
    }
    TextureAtlas(const TextureAtlas&) = delete; // prevent copying
    // Prevent assignment
    TextureAtlas& operator=(const TextureAtlas&) = delete;

    void SetTexture(Texture tex);
    void Draw(std::string texName, Vector2 dest, Vector2 origin, float rot, Color tint, int frame = 1);

private:
    TextureAtlas() = default;
    Texture _texture;
};

namespace TA {
    inline TextureAtlas& get() { return TextureAtlas::instance(); }
    constexpr float TILE_SIZE = 16;
}