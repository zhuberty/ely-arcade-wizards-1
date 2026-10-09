#include "Player.hpp"

Vector2 Player::GetPos() const { return _pos; }

void Player::SetPos(Vector2 pos) { _pos = pos; }

void Player::SetAnim(std::string anim)
{
}

void Player::Update(float delta)
{
    _moveDir.x = (IsKeyDown(KEY_D) ? 1.0f : 0.0f) - (IsKeyDown(KEY_A) ? 1.0f : 0.0f);
    _moveDir.y = (IsKeyDown(KEY_S) ? 1.0f : 0.0f) - (IsKeyDown(KEY_W) ? 1.0f : 0.0f);

    _pos.x += _speed * _moveDir.x * delta;
    _pos.y += _speed * _moveDir.y * delta;

    if (_moveDir.x != 0 || _moveDir.y != 0)
    {
        _curAnim = "player.walk.s";
    }
    else
    {
        _curAnim = "player.stand.s";
        _animFrame = 1;
    }

    auto it = TAK::map.find(_curAnim);

    if (it == TAK::map.end())
        throw std::runtime_error("Texture not found '" + _curAnim + "'");

    const AtlasTexture &atlasTexture = it->second;

    TA::get().Draw(_curAnim, _pos, {0, 0}, 0.0f, WHITE, _animFrame);

    if (atlasTexture.endFrame > 1)
    {
        _deltaFrameTime += delta;
        if (_deltaFrameTime > 0.10f)
        {
            _animFrame++;
            _deltaFrameTime = 0;
        }

        if (_animFrame > atlasTexture.endFrame)
            _animFrame = 1;
    }
}