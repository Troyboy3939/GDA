#include "GameObject.h"
#include "Tile.h"
GameObject::GameObject(Tile* pTile)
{
    Initialise(pTile);
}

GameObject::GameObject()
{
    m_v2Position = Vector2();
}

GameObject::~GameObject()
{
}

void GameObject::Initialise(Tile* pTile)
{
    auto nWidth = pTile->GetTexture()->getWidth();
    auto nHeight = pTile->GetTexture()->getHeight();

    pTile->SetOn(false);
    Vector2 v2Position = pTile->GetPosition();

    
    m_pTile = pTile;

         
    m_v2Position = v2Position;
}

Vector2 GameObject::GetPosition()
{
    return m_v2Position;
}

void GameObject::SetPosition(Vector2 v2Pos)
{
    m_v2Position = v2Pos;
}
