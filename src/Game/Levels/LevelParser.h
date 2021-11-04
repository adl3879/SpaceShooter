#pragma once

#include <tinyxml.h>
#include "Character/Enemy.h"
#include "Engine.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iostream>

typedef std::vector<std::unordered_map<std::string, Enemy*>> EnemyArr;

class LevelParser
{
public:
    static LevelParser* Instance()
    {
        static LevelParser instance;
        return &instance;
    }

    void Parse( const std::string& level, EnemyArr& enemies )
    {
        TiXmlDocument xml;
        xml.LoadFile( "../res/levels/" + level + ".xml" );
        if ( xml.Error() )
            SDL_Log( "Failed to open level %s", level.c_str() );

        TiXmlElement* root = xml.RootElement();
        for ( TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement() )
        {
            if ( e->Value() == std::string( "wave" ) )
            {
                TiXmlElement* data;
                for ( TiXmlElement* e2 = e->FirstChildElement(); e2 != nullptr; e2 = e2->NextSiblingElement() )
                {
                    if ( e2->Value() == std::string( "data" ) )
                    {
                        data = e2;
                        break;
                    }
                }
                // Get raw data
                std::string matrix( data->GetText() );
                std::istringstream iss( matrix );
                std::string id;
                uint32_t enemyMap[10][14];

                for ( size_t row = 0; row < m_RowCount; row++ )
                {
                    for ( size_t column = 0; column < m_ColumnCount; column++ )
                    {
                        std::getline( iss, id, ',' );
                        std::stringstream converter( id );
                        converter >> enemyMap[row][column];

                        if ( !iss.good() ) break;
                    }
                }
                
                ParseEnemies( enemyMap, enemies );
            }
        }
    }

private:
    LevelParser() {}
    
    void ParseEnemies( uint32_t map[10][14], EnemyArr& enemies )
    {
        std::unordered_map<std::string, Enemy*> enemyMap;

        for ( size_t y = 0; y < m_RowCount; y++ )
        {
            for ( size_t x = 0; x < m_ColumnCount; x++ ) 
            {
                unsigned int curr = map[y][x];
                if ( curr > 0 )
                {
                    Enemy* enemy;
                    std::string id = std::to_string(y) + ":" + std::to_string(x);
                    if ( curr <= 12 )
                    {
                        enemy = Enemy::New( "noob_" + std::to_string( curr ), 42 * x, 48 * y );
                    }
                    enemyMap[id] = enemy;
                }
            }
        }

        enemies.push_back( enemyMap ); 
    }

private:
    unsigned int m_RowCount = 10, m_ColumnCount = 14;
};
