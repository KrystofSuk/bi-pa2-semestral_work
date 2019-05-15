#include "tile.h"

namespace GameLogic
{

Tile::Tile()
{
    _char = ' ';
}

Tile::Tile(const char & c, const Color & col, const bool & p)
{
    _char = c;
    _color = col;
    _passable = p;
}

void Tile::SetPass(const bool & p)
{
    _passable = p;
}

void Tile::SetChar(const char & n)
{
    _char = n;
}

const char & Tile::GetChar() const
{
    return _char;
}

const Color & Tile::GetColor() const
{
    return _color;
}

const bool & Tile::GetPassable() const
{
    return _passable;
}

} // namespace GameLogic