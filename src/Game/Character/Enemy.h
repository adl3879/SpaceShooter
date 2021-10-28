#pragma once

#include "Engine.h"
#include "GameObject.h"
#include "Bullet.h"
#include "RigidBody.h"
#include "Collision/BoxCollider.h"

#include <string>

enum EnemyType
{

};

class Enemy : public GameObject
{
public:
    Enemy( Props* props ): GameObject( props )
    {
        m_RigidBody = new RigidBody();
        m_Collider = new BoxCollider();
    };

    virtual void Update( float dt ) = 0;
    virtual void Draw() = 0;
    virtual void Clean() = 0;

protected:
    EnemyType m_Type;
    Uint8 m_Health;
    RigidBody* m_RigidBody;
    BoxCollider* m_Collider;
};
