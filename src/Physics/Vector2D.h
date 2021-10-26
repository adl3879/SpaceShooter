#pragma once

#include <math.h>

class Vector2D
{
public:
    Vector2D() : x( 0.0f ), y( 0.0f ) {}
    Vector2D( float x, float y ) : x( x ), y( y ) {}

    /**
     * Prints value of x and y
    */
    void Print();

    Vector2D operator+ ( const Vector2D& vec2 ) const;
    Vector2D operator- ( const Vector2D& vec2 ) const;
    Vector2D operator* ( const float& scalar ) const;
    Vector2D operator/ ( const float& scalar ) const;

    friend Vector2D operator+= ( Vector2D& vec1, const Vector2D& vec2 );
    friend Vector2D operator-= ( Vector2D& vec1, const Vector2D& vec2 );

    inline Vector2D operator*= ( const float& scalar )
    {
        x *= scalar;
		y *= scalar;
		return *this;
    }

    inline Vector2D operator/= ( const float& scalar )
    {
        x /= scalar;
		y /= scalar;
		return *this;
    }

    float Length();
    /**
     * Makes the length of a vector one
    */
    void Normalize();
    Vector2D Zero();

public:
    float x, y;
};
