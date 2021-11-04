#pragma once

#include <tinyxml.h>

#include "Engine.h"
#include "GameObject.h"
#include "Bullet.h"
#include "RigidBody.h"
#include "Collision/BoxCollider.h"
#include "Vector2D.h"
#include "Texture.h"

#include <string>
#include <unordered_map>
#include <functional>

namespace enemy
{
    struct Props 
    {
    public:
        Props( const std::string& type, const std::string& textureID, int spriteWidth, int spriteHeight, int spriteRow, int spriteColumn,
            SDL_RendererFlip flip, float scale, int health, int firePower, const std::string& bulletTexture, int bulletSpeed )
        {
            Type = type;
            TextureID = textureID;
            SpriteWidth = spriteWidth;
            SpriteHeight = spriteHeight;
            SpriteRow = spriteRow;
            SpriteColumn = spriteColumn;
            Flip = flip;
            Scale = scale;
            Health = health;
            FirePower = firePower;
            BulletTexture = bulletTexture;
            BulletSpeed = bulletSpeed;
        }
        
    public:
        std::string Type;
        std::string TextureID;
        int SpriteWidth, SpriteHeight, SpriteRow, SpriteColumn;
        SDL_RendererFlip Flip;
        float Scale;
        int Health, FirePower, BulletSpeed;
        std::string BulletTexture;
    };
};

class Enemy
{
public:
    Enemy( enemy::Props* props, float x = 0.0f, float y = 0.0f );
    virtual ~Enemy();

    void Update( float dt );
    void Draw();

    const Vector2D& GetPosition() { return m_Position; }
    const Vector2D& GetInitialPosition() { return m_InitialPosition; }
    void SetPosition( float x, float y);
    void Move( float x, float y );
    void Shoot( int size, int speed, float angle );
    bool IsDead();

    static void Parse( const std::string& path );
    static Enemy* New( const std::string& type, float x = 0.0f, float y = 0.0f );

private:
    static void RegisterType( std::string type, std::function<Enemy*( enemy::Props* props, float x, float y )> etype);
    static void RegisterProps( std::string type, enemy::Props* props );

private:
    enemy::Props* m_Props;
    bool m_IsAlive;
    Vector2D m_Position;
    Vector2D m_InitialPosition;
    int m_Health;

    RigidBody* m_RigidBody;
    BoxCollider* m_Collider;

    static std::unordered_map<std::string, std::function<Enemy* ( enemy::Props* props, float x, float y )>> m_EnemyMap;
    static std::unordered_map<std::string, enemy::Props*> m_PropsMap;
};
