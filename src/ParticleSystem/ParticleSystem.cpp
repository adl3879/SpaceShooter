#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
    // SDL_Log( "Loading Particle System" );
}

ParticleSystem* ParticleSystem::Instance()
{
    static ParticleSystem* instance = new ParticleSystem();
    return instance;
}

bool ParticleSystem::Parse( const std::string& path )
{
    TiXmlDocument xml;
    xml.LoadFile( path );
    if ( xml.Error() )
        SDL_Log( "Failed to load file %s", path.c_str() );

    TiXmlElement* root = xml.RootElement();
    for ( TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement() )
    {
        if ( e->Value() == std::string( "emitter" ) )
        {
            std::string type = e->Attribute( "type" );
            EmitterData data;

            // Texture ID
            e->QueryStringAttribute( "texture", &data.TextureID );

            // Angle range
            e->FirstChildElement( "angleRange" )->QueryFloatAttribute( "min", &data.AngleRange.x );
            e->FirstChildElement( "angleRange" )->QueryFloatAttribute( "max", &data.AngleRange.y );

            // Particle speeds
            e->FirstChildElement( "rotSpeed" )->QueryDoubleAttribute( "value", &data.RotSpeed );
            e->FirstChildElement( "startSpeed" )->QueryFloatAttribute( "value", &data.StartSpeed );
            e->FirstChildElement( "endSpeed" )->QueryFloatAttribute( "value", &data.EndSpeed );

            // Random controls
            e->FirstChildElement( "startSpeed" )->QueryFloatAttribute( "randMin", &data.StartSpeedRand.x );
            e->FirstChildElement( "startSpeed" )->QueryFloatAttribute( "randMax", &data.StartSpeedRand.y );
            e->FirstChildElement( "endSpeed" )->QueryFloatAttribute( "randMin", &data.EndSpeedRand.x );
            e->FirstChildElement( "endSpeed" )->QueryFloatAttribute( "randMax", &data.EndSpeedRand.y );

            e->FirstChildElement( "rotSpeed" )->QueryFloatAttribute( "randMin", &data.RotSpeedRand.x);
            e->FirstChildElement( "rotSpeed" )->QueryFloatAttribute( "randMax", &data.RotSpeedRand.y);

            e->FirstChildElement( "emitVariance" )->QueryFloatAttribute( "randMin", &data.EmitVarianceRand.x );
            e->FirstChildElement( "emitVariance" )->QueryFloatAttribute( "randMax", &data.EmitVarianceRand.y );

            e->FirstChildElement( "maxParticleLife" )->QueryFloatAttribute( "randMin", &data.MaxParticleLifeRand.x );
            e->FirstChildElement( "maxParticleLife" )->QueryFloatAttribute( "randMax", &data.MaxParticleLifeRand.y );

            e->FirstChildElement( "startSize" )->QueryFloatAttribute( "randMin", &data.StartSizeRand.x );
            e->FirstChildElement( "startSize" )->QueryFloatAttribute( "randMax", &data.StartSizeRand.y );

            e->FirstChildElement( "endSize" )->QueryFloatAttribute( "randMin", &data.EndSizeRand.x );
            e->FirstChildElement( "endSize" )->QueryFloatAttribute( "randMax", &data.EndSizeRand.y );

            // Particle size
            e->FirstChildElement( "startSize" )->QueryFloatAttribute( "value", &data.StartSize );
            e->FirstChildElement( "endSize" )->QueryFloatAttribute( "value", &data.EndSize );

            // Emission properties
            e->FirstChildElement( "emitNumber" )->QueryUnsignedAttribute( "value", &data.EmitNumber );
            e->FirstChildElement( "emitVariance" )->QueryUnsignedAttribute( "value", &data.EmitVariance );

            // Particle life
            e->FirstChildElement( "maxParticleLife" )->QueryUnsignedAttribute( "value", &data.MaxParticleLife );

            // Rect from particle atlas
            e->FirstChildElement( "textureRect" )->QueryIntAttribute( "x", &data.TextureRect.x );
            e->FirstChildElement( "textureRect" )->QueryIntAttribute( "y", &data.TextureRect.y );
            e->FirstChildElement( "textureRect" )->QueryIntAttribute( "w", &data.TextureRect.w );
            e->FirstChildElement( "textureRect" )->QueryIntAttribute( "h", &data.TextureRect.h );

            // Lifetime of emitter
            e->FirstChildElement( "lifetime" )->QueryDoubleAttribute( "value", &data.LifeTime );

            // Start color
            int r, g, b, a;
            e->FirstChildElement( "startColor" )->QueryIntAttribute( "r", &r );
            e->FirstChildElement( "startColor" )->QueryIntAttribute( "g", &g );
            e->FirstChildElement( "startColor" )->QueryIntAttribute( "b", &b );
            e->FirstChildElement( "startColor" )->QueryIntAttribute( "a", &a );
            data.StartColor.r = r;
            data.StartColor.g = g;
            data.StartColor.b = b;
            data.StartColor.a = a;

            // End color
            e->FirstChildElement( "endColor" )->QueryIntAttribute( "r", &r );
            e->FirstChildElement( "endColor" )->QueryIntAttribute( "g", &g );
            e->FirstChildElement( "endColor" )->QueryIntAttribute( "b", &b );
            e->FirstChildElement( "endColor" )->QueryIntAttribute( "a", &a );
            data.EndColor.r = r;
            data.EndColor.g = g;
            data.EndColor.b = b;
            data.EndColor.a = a;

            std::string blendMode;
            blendMode = e->FirstChildElement( "blendMode" )->Attribute( "mode" );

            if ( blendMode == "none" ) data.BlendMode = SDL_BlendMode::SDL_BLENDMODE_NONE;
            else if ( blendMode == "add" ) data.BlendMode = SDL_BlendMode::SDL_BLENDMODE_ADD;
            else if ( blendMode == "blend" ) data.BlendMode = SDL_BlendMode::SDL_BLENDMODE_BLEND;
            else if ( blendMode == "invalid" ) data.BlendMode = SDL_BlendMode::SDL_BLENDMODE_INVALID;
            else if ( blendMode == "mul" ) data.BlendMode = SDL_BlendMode::SDL_BLENDMODE_MUL;
            else if ( blendMode == "mod" ) data.BlendMode = SDL_BlendMode::SDL_BLENDMODE_MOD;

            m_EmitterMap[type] = data;
        }
    }
    return true;
}
 
bool ParticleSystem::Start()
{
    return true;
}

bool ParticleSystem::PreUpdate()
{
    return true;
}

bool ParticleSystem::Update( float dt )
{
    if ( m_EmittersList.size() > 0 )
    {
        std::list<Emitter*>::iterator it;
        for ( it = m_EmittersList.begin(); it != m_EmittersList.end(); ++it )
        {
            if ( *it != nullptr )
                ( *it )->Update( dt );
        }
    }
    return true;
}

bool ParticleSystem::PostUpdate()
{
    bool ret = false;

    if ( !m_EmittersToDestroy.empty() )
    {
        std::list<Emitter*>::const_iterator it;
        for ( it = m_EmittersToDestroy.begin(); it != m_EmittersToDestroy.end(); ++it )
        {
            m_EmittersList.remove( *it );
            delete ( *it );
        }
        m_EmittersToDestroy.clear();
    }

    ret = m_EmittersToDestroy.size() <= 0;
    if ( ret )
    {
        std::list<Emitter*>::iterator it;
        for ( it = m_EmittersList.begin(); it != m_EmittersList.end() && ret; ++it )
            ( *it )->Draw();
    }

    return ret;
}

bool ParticleSystem::CleanUp()
{
    std::list<Emitter*>::const_iterator it;
    for ( it = m_EmittersList.begin(); it != m_EmittersList.end(); ++it )
        if ( *it != nullptr ) delete *it;

    m_EmittersList.clear();

    return true;
}

// Emitter methods
Emitter* ParticleSystem::AddEmitter( const std::string& id, Vector2D position )
{
    Emitter* emitter = new Emitter( position, m_EmitterMap[id] );
    m_EmittersList.push_back( emitter );
    return emitter;
}

bool ParticleSystem::RemoveEmitter( Emitter* emitter )
{
    if ( emitter != nullptr && !m_EmittersList.empty() )
    {
        m_EmittersToDestroy.push_back( emitter );
        return true;
    }
    return false;
}

bool ParticleSystem::RemoveAllEmitters()
{
    if ( !m_EmittersList.empty() )
    {
        std::list<Emitter*>::const_iterator it;
        for ( it = m_EmittersList.begin(); it != m_EmittersList.end(); ++it )
        {
            if ( *it != nullptr )
                m_EmittersToDestroy.push_back( *it );
            return true;
        }
    }
    return false;
}
