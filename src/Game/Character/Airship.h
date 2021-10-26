#pragma once

#include "GameObject.h"
#include "RigidBody.h"
#include "Bullet.h"
#include "Vector2D.h"
#include <vector>

class Airship : public GameObject
{
public:
    Airship( Props* props );

    virtual void Update( float dt ) override;
    virtual void Draw() override;
    virtual void Clean() override;

private:
    RigidBody* m_RigidBody;
    Bullet m_Bullets[100][2];
    float m_BulletSpeed;
    Vector2D m_LastSafePos;
};
