#pragma once

#include "Engine.h"
#include "Vector2D.h"
#include "RigidBody.h"

#include <string>
#include <vector>

class Bullet
{
public:
    enum Direction { UP = -1, DOWN = 1 };

    Bullet( std::string type, float x, float y, float angle = 0, Direction direction = UP, float speed  = 8.0f );
    void Draw();
    void Update( float dt );

    inline Vector2D* GetPos() const { return m_Pos; }

private:
    Vector2D* m_Pos;
    RigidBody* m_RigidBody;
    std::string m_Type;
    bool m_IsFired;
    float m_Angle;
    float m_Speed;
    Direction m_Direction;
};
