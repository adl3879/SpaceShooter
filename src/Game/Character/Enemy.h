#pragma once

#include "GameObject.h"
#include "Bullet.h"

#include <string>

enum EnemyType
{

};

class Enemy : public GameObject
{
public:
    Enemy( Props* props ): GameObject( props ) {};

    virtual void Shoot( Bullet* bullet ) = 0;

protected:
    EnemyType m_Type;
    Uint8 m_Health;

};
