#include "GameObject.h"

GameObject::GameObject(Vector2 v2Pos)
{
    Initialise(v2Pos);
}

GameObject::GameObject()
{
    m_v2Position = Vector2();
}

GameObject::~GameObject()
{
}

void GameObject::Initialise(Vector2 v2Pos)
{
    m_v2Position = v2Pos;
}

Vector2 GameObject::GetPosition()
{
    return m_v2Position;
}

void GameObject::SetPosition(Vector2 v2Pos)
{
    m_v2Position = v2Pos;
}
