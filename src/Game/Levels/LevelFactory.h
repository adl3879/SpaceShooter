#pragma once

#include <string>
#include <functional>
#include <map>
#include "Engine.h"
#include "Level.h"

class LevelFactory
{
public:
    static LevelFactory* Instance()
    {
        return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new LevelFactory();
    }

    void RegisterType( std::string level, std::function<Level*()> type );

    Level* GetLevel( std::string level );

private:
    static LevelFactory* s_Instance;
    std::map<std::string, std::function<Level*()>> m_TypeRegistry;
};

template<class T>
class LevelRegistrar
{
public:
    LevelRegistrar( std::string level )
    {
        // callback function has params of Props* and returns Level*
		LevelFactory::Instance()->RegisterType( level, []()->Level* { return new T(); } );
    }
};
