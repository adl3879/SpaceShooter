#pragma one

#include <tinyxml.h>
#include "Animation.h"

#include <vector>
#include <string>
#include <map>

struct Sequence
{
    int Speed;
    int FrameCount;
    int Width, Height;
    std::vector<std::string> TextureIDs;
};

class SeqAnimation : public Animation
{
public:
    SeqAnimation ( bool repeat = false );

    virtual void Update( float dt );
    /**
     * Loads an xml file and reads data for textureIds and path
     * @param source filepath for xml file
    */
    void Parse( std::string source );

    /**
     * Sets current sequnce information and save in a map with id as key
     * @param seqID id of new sequence
    */
    void SetCurrentSeq( std::string seqID );

    /**
     * Draws texture to screen for aech frame
    */
    void DrawFrame( float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, 
        SDL_RendererFlip flip = SDL_FLIP_NONE );

	inline void SetRepeat( bool repeat ) { m_Repeat = repeat; }

private:
    Sequence m_CurrentSeq;
    std::map<std::string, Sequence> m_Seq;
    bool m_Repeat;
};
