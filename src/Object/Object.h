#pragma once

class Input;

class Object
{
public:
    virtual void Update( float dt ) = 0;
    virtual void Draw() = 0;
    virtual void Clean() = 0;
};
