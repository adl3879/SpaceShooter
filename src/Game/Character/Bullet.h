#pragma once

#include "Engine.h"
#include "Vector2D.h"
#include "RigidBody.h"

#include <string>

class Bullet
{
public:
    Bullet();
    void Draw();
    void Update( float dt );
    void Shoot( std::string type, float x, float y );

    inline float GetY() const { return m_Pos->y; }

private:
    Vector2D* m_Pos;
    RigidBody* m_RigidBody;
    std::string m_Type;
    bool m_IsFired;
};
