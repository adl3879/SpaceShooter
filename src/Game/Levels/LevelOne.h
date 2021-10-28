#pragma once

#include "Level.h"
#include "Engine.h"

class LevelOne : public Level
{
public:
    LevelOne();

    virtual void Draw() override;
    virtual void Update( float dt ) override;
    virtual void Clean() override;

private:

};
