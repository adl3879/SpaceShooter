#pragma once

#include "GameObject.h"
#include "RigidBody.h"
#include "Bullet.h"
#include "Vector2D.h"
#include <vector>

typedef std::vector<std::vector<Bullet*>> Bullets;

class Airship : public GameObject
{
public:
    Airship( Props* props );

    virtual void Update( float dt ) override;
    virtual void Draw() override;
    virtual void Clean() override;

    static Bullets* GetBullets();

private:
    void HandleInput( float dt );

private:
    RigidBody* m_RigidBody;
    static Bullets m_Bullets;
    float m_BulletInterval;
    Vector2D m_LastSafePos;
};
