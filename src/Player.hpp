#pragma once

#include <string>
#include <stdexcept>
#include "raylib.h"
#include "TextureAtlas.hpp"
#include "GameConfig.hpp"

class Player
{
public:
    Player(Vector2 pos) { _pos = pos; }
    Vector2 GetPos() const;
    void SetPos(Vector2 pos);
    void SetAnim(std::string anim);
    void Update(float delta);

private:
    float _speed = Conf::PLAYER_SPEED;
    Vector2 _moveDir = {0.0f, 0.0f};
    Vector2 _pos;
    std::string _curAnim = "player.stand.s";
    float _deltaFrameTime = 0;
    int _animFrame = 1;
};