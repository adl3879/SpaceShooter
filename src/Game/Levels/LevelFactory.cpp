#include "LevelFactory.h"

LevelFactory* LevelFactory::s_Instance = nullptr;

void LevelFactory::RegisterType( std::string level, std::function<Level*()> type )
{
    m_TypeRegistry[level] = type;
}

Level* LevelFactory::GetLevel( std::string level )
{
    Level* lvl = nullptr;
    auto it = m_TypeRegistry.find( level );
    if ( it != m_TypeRegistry.end() )
        lvl = it->second();
        
    return lvl;
}
