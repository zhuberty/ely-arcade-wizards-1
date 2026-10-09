#include "TextureAtlas.hpp"

void TextureAtlas::SetTexture(Texture tex)
{
    _texture = tex;
}

void TextureAtlas::Draw(std::string texName, Vector2 dest, Vector2 origin, float rot, Color tint, int frame)
{
    auto it = TAK::map.find(texName);

    if (it == TAK::map.end()) return;

    const AtlasTexture& atlasTexture = it->second;

    const Indices& indices = atlasTexture.indices;

    Rectangle srcRect = {indices.x + (frame - 1) * TA::TILE_SIZE, indices.y * TA::TILE_SIZE, TA::TILE_SIZE, TA::TILE_SIZE};
    Rectangle destRect = {dest.x, dest.y, TA::TILE_SIZE, TA::TILE_SIZE};

    DrawTexturePro(_texture, srcRect, destRect, origin, rot, tint);
}