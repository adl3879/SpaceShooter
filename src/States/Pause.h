#pragma once

#include "GameState.h"
#include "Engine.h"
#include "Text.h"
#include <map>
#include <string>

class Pause : public GameState
{
public:
    Pause();

    virtual bool Init() override;
    virtual bool Exit() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    std::map<std::string, Text*> m_Text;
};
