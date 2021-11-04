#include "LevelOne.h"
#include "LevelFactory.h"

static LevelRegistrar<LevelOne> registrar( "one" );

LevelOne::LevelOne()
{
    LevelParser::Instance()->Parse( "one", m_Enemies );
    m_Wave = 0;
}

void LevelOne::Draw()
{
    std::unordered_map<std::string, Enemy*>::iterator it;
    for ( it = m_Enemies[m_Wave].begin(); it != m_Enemies[m_Wave].end(); it++ )
        it->second->Draw();
}

void LevelOne::Update( float dt )
{
    std::unordered_map<std::string, Enemy*>::iterator it;
    for ( it = m_Enemies[m_Wave].begin(); it != m_Enemies[m_Wave].end(); it++ )
    {
        it->second->Update( dt );
        if ( it->second->IsDead() )
        {
            delete it->second;
            m_Enemies[m_Wave].erase( it );
        }
    }

    if ( m_Enemies[m_Wave].empty() && m_Wave < m_Enemies.size() - 1 ) m_Wave++;
}

void LevelOne::Clean()
{
    std::unordered_map<std::string, Enemy*>::iterator it;
    for ( it = m_Enemies[m_Wave].begin(); it != m_Enemies[m_Wave].end(); it++ )
    {
        delete it->second;
    }
}
