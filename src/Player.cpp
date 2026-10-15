#include "Player.hpp"
#include "arcade_input.h"

Vector2 Player::GetPos() const { return _pos; }

void Player::SetPos(Vector2 pos) { _pos = pos; }

void Player::SetAnim(std::string anim)
{
}

void Player::Update(float delta)
{
    // Movement from the SDK's input, so it works with the arcade joysticks, W A S D, the
    // arrow keys and gamepad d-pads. Player::Any = either player's controls.
    auto down = [](arcade::Action a) { return arcade::IsActionDown(arcade::Player::Any, a); };
    _moveDir.x = (down(arcade::Action::Right) ? 1.0f : 0.0f) - (down(arcade::Action::Left) ? 1.0f : 0.0f);
    _moveDir.y = (down(arcade::Action::Down)  ? 1.0f : 0.0f) - (down(arcade::Action::Up)   ? 1.0f : 0.0f);

    _pos.x += _speed * _moveDir.x * delta;
    _pos.y += _speed * _moveDir.y * delta;

    if (_moveDir.y < 0)
    {
        _curAnim = "player.walk.n";
    }
    else if (_moveDir.y > 0)
    {
        _curAnim = "player.walk.s";
    }
    else if (_moveDir.x > 0) {
        _curAnim = "player.walk.e";
    }
    else if (_moveDir.x < 0) {
        _curAnim = "player.walk.w";
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