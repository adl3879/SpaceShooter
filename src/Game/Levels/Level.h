#pragma once

class Level
{
public:
    virtual void Draw() = 0;
    virtual void Update( float dt ) = 0;
    virtual void Clean() = 0;

protected:
    bool m_IsCompleted;
};
