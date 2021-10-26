#include "SeqAnimation.h"

SeqAnimation::SeqAnimation( bool repeat )
    : Animation( repeat )
{}

void SeqAnimation::Update( float dt )
{
    if ( m_Repeat || m_IsEnded )
    {
        m_IsEnded = false;
        m_CurrentFrame = ( SDL_GetTicks() / m_CurrentSeq.Speed ) % m_CurrentSeq.FrameCount;
        
    }
    else if ( !m_Repeat && m_CurrentFrame == ( m_CurrentSeq.FrameCount - 1 ) )
    {
        m_IsEnded = true;
        m_CurrentFrame = m_CurrentSeq.FrameCount - 1;
    }
}

void SeqAnimation::DrawFrame( float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, 
    SDL_RendererFlip flip )
{
	Texture::Instance()->Draw( m_CurrentSeq.TextureIDs[m_CurrentFrame], x, y, m_CurrentSeq.Width, m_CurrentSeq.Height, 
        xScale, yScale, flip );
}

void SeqAnimation::SetCurrentSeq( std::string seqID )
{
    if ( m_Seq.count( seqID ) > 0 )
        m_CurrentSeq = m_Seq[seqID];
    else
        SDL_Log( "The given sequence animation is not matching: %s", seqID );
}

void SeqAnimation::Parse( std::string source )
{
    TiXmlDocument xml;
    xml.LoadFile( source );
    if ( xml.Error() )
        SDL_Log( "Failed to load animation file: %s", source );

    TiXmlElement* root = xml.RootElement();
    for ( TiXmlElement* e = root->FirstChildElement(); e != nullptr; root->NextSiblingElement() )
    {
        if ( e->Value() == std::string( "sequence" ) )
        {
            Sequence seq;
            std::string seqID = e->Attribute( "id" );
            e->Attribute( "speed", &seq.Speed );
            e->Attribute( "width", &seq.Width );
			e->Attribute( "height", &seq.Height );
			e->Attribute( "frameCount", &seq.FrameCount );

            for ( TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement() )
			{
				seq.TextureIDs.push_back( frame->Attribute( "textureID" ) );
			}
			m_Seq[seqID] = seq;
        }
    }
}
