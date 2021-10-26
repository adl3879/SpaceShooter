#pragma once

#include "GameObject.h"
#include <tinyxml.h>
#include "Character/Airship.h"

#include <map>
#include <string>
#include <functional>
#include <vector>

class ObjectFactory
{
public:
    static ObjectFactory* Instance()
    {
        return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new ObjectFactory();
    }

    /**
     * Registers new object type
     * @param classname identifier for new object
     * @param type callback fn that creates new instance of the object
    */
    void RegisterType( std::string classname, std::function<GameObject*( Props* props )> type );

    /**
     * Loads and parse game objects from xml file
     * @param source xml filepath
    */
    void Parse( std::string source, std::vector<GameObject*> &objects );

private:
    /**
     * Creates new object
     * @param type classname of registered object
     * @param props properties of object to be created
    */
    GameObject* Create( std::string type, Props* props );

private:
    ObjectFactory() {}
    std::map<std::string, std::function<GameObject*( Props* props )>> m_TypeRegistry;
    static ObjectFactory* s_Instance;
};

template<class T>
class Registrar
{
public:
    Registrar( std::string classname )
    {
        // callback function has params of Props* and returns GameObject*
		ObjectFactory::Instance()->RegisterType( classname, []( Props* props )->GameObject* { return new T( props ); } );
    }
};
