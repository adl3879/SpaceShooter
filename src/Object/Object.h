#pragma once

/**
 * Pure virtual class
 * Acts as an structural interface for children classes 
*/
class Object
{
public:
    virtual void Update( float dt ) = 0;
    virtual void Draw() = 0;
    virtual void Clean() = 0;
};
