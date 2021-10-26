#include "ObjectFactory.h"

#include "Character/Airship.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

void ObjectFactory::RegisterType( std::string classname, std::function<GameObject*(Props* props)> type )
{
    m_TypeRegistry[classname] = type;
}

GameObject* ObjectFactory::Create( std::string type, Props* props )
{
    GameObject* object = nullptr;
    auto it = m_TypeRegistry.find( type );
    if ( it != m_TypeRegistry.end() )
        object = it->second( props );
    else
        SDL_Log("%s not found", type.c_str());
        
    return object;
}

void ObjectFactory::Parse( std::string source, std::vector<GameObject*> &objects )
{
    TiXmlDocument xml;
    xml.LoadFile( source );
    if ( xml.Error() )
        SDL_Log( "Failed to load xml file: %s", source.c_str() );

    TiXmlElement* root = xml.RootElement();
    for ( TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement() )
    {
        if ( e->Value() == std::string( "props" ) )
        {
            int width, height;
            double x, y;
            std::string classname = e->Attribute( "classname" );
            std::string textureId = e->Attribute( "textureId" );
            e->Attribute( "width", &width );
            e->Attribute( "height", &height );
            e->Attribute( "x", &x );
            e->Attribute( "y", &y );

            GameObject* obj = Create( classname, new Props( textureId, (float)x, (float)y, width, height ) );
            objects.push_back( obj );
        }
    }
}
