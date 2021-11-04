#pragma once

#include "Engine.h"
#include "Vector2D.h"
#include "RigidBody.h"
#include "Collision/BoxCollider.h"

#include <string>
#include <vector>

class Bullet
{
public:
    enum Direction { UP = -1, DOWN = 1 };

    Bullet( std::string type, float x, float y, float angle = 0, Direction direction = UP, float speed  = 8.0f );
    virtual ~Bullet();

    void Draw();
    void Update( float dt );

    void SetCollided() { m_Collided = true; }
    bool GetCollided() { return m_Collided; }

    inline Vector2D* GetPos() const { return m_Pos; }
    SDL_Rect GetCollider() const;

private:
    Vector2D* m_Pos;
    RigidBody* m_RigidBody;
    BoxCollider* m_Collider;

    std::string m_Type;
    bool m_IsFired;
    float m_Angle;
    float m_Speed;
    Direction m_Direction;
    bool m_Collided;
};
