#include "Vector2D.h"

#include <iostream>
#include <SDL.h>

void Vector2D::Print()
{
    SDL_Log(" x: %f, y: %f ", x, y );
}

Vector2D Vector2D::operator+ ( const Vector2D& vec2 ) const
{
    return Vector2D( x + vec2.x, y + vec2.y  );
}

Vector2D Vector2D::operator- ( const Vector2D& vec2 ) const
{
    return Vector2D( x - vec2.x, y - vec2.y );
}

Vector2D Vector2D::operator* ( const float& scalar ) const
{
    return Vector2D( x * scalar, y * scalar );
}

Vector2D Vector2D::operator/ ( const float& scalar ) const
{
    return Vector2D( x / scalar, y / scalar );
}

Vector2D operator+= ( Vector2D& vec1, const Vector2D& vec2 )
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    return vec1;
}

Vector2D operator-= ( Vector2D& vec1, const Vector2D& vec2 )
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    return vec1;
}

float Vector2D::Length()
{
    return sqrt( pow( x, 2 ) + pow( y, 2 ) );
}

void Vector2D::Normalize()
{
    float length = Length();
    if ( length > 0 )
    {
        ( *this ) *= 1 / length;
    }
}

Vector2D Vector2D::Zero()
{
    return Vector2D( 0.0f, 0.0f );
}
