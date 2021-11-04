#pragma once

#include "Level.h"
#include "Engine.h"
#include "Character/Enemy.h"
#include "LevelParser.h"

#include <unordered_map>
#include <string>

class LevelOne : public Level
{
public:
    LevelOne();

    virtual void Draw() override;
    virtual void Update( float dt ) override;
    virtual void Clean() override;

private:
    EnemyArr m_Enemies;
    unsigned int m_Wave;
};
