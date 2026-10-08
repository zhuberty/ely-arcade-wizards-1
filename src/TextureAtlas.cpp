#include "TextureAtlas.hpp"

void TextureAtlas::SetTexture(Texture tex)
{
    _texture = tex;
}

void TextureAtlas::Draw(const char* texName, Vector2 dest, Vector2 origin, float rot, Color tint)
{
    auto it = TAK::map.find(texName);

    if (it == TAK::map.end()) return;

    const Indices& indices = it->second;

    Rectangle srcRect = {indices.x * TA::TILE_SIZE, indices.y * TA::TILE_SIZE, TA::TILE_SIZE, TA::TILE_SIZE};
    Rectangle destRect = {dest.x, dest.y, TA::TILE_SIZE, TA::TILE_SIZE};

    DrawTexturePro(_texture, srcRect, destRect, origin, rot, tint);
}