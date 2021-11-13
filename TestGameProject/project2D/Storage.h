#pragma once
#include "Building.h"

class Empire;

class Storage :
    public Building
{
public:
    Storage(aie::Texture* pTexture, Vector2 v2Location);

};

