#include "Text.h"

#include "Engine.h"
#include <algorithm>

std::map<std::string, TTF_Font*> Text::m_Fonts = {};

static void GenerateGlyphSurfaces( TTF_Font* font, const std::vector<char>& glyphs, BitmapFontInfo& fontInfo );
static void GenerateGlyphSrc( BitmapFontInfo& fontInfo );
static void GenerateGlyphTextures( BitmapFontInfo& fontInfo, bool freeGlyphSurfaces = true );

bool Text::Parse( std::string path )
{
    // Load and store default font
    m_Fonts["default"] = TTF_OpenFont( "../res/font/calibri.ttf", 24 );

    TiXmlDocument xml;
    xml.LoadFile( path );
    if ( xml.Error() )
    {
        SDL_Log( "Could not open file %s", path.c_str() );
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for ( TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement() )
    {
        if ( e->Value() == std::string( "font" ) )
        {
            std::string id, source;
            int size;
            id = e->Attribute( "id" );
            source = e->Attribute( "source" );
            e->Attribute( "size", &size );
            // Load font
            TTF_Font* newFont = TTF_OpenFont( source.c_str(), size );
            m_Fonts[id] = newFont;
        }
    }

    return true;
}

Text::Text( std::string id, unsigned char startGlyph, unsigned char endGlyph )
{
    m_FontID = id;
    size_t numGlyphs = ( static_cast<size_t>( endGlyph ) - startGlyph ) + 1;
    std::vector<char> glyphs(numGlyphs);

    unsigned char currentGlyph = startGlyph;
    for ( size_t i = 0; i < numGlyphs; currentGlyph++, i++ )
    {
        glyphs[i] = static_cast<char>( currentGlyph );
    }

    Create( glyphs );
}

Text::Text( std::string id, const std::vector<char>& glyphs )
{
    m_FontID = id;
    Create( glyphs );    
}

uint32_t Text::SetColor( uint32_t color )
{
    auto pixelFormat = SDL_AllocFormat( SDL_PIXELFORMAT_RGB888 );

    SDL_Color newColor{};
    SDL_GetRGBA(
        color, pixelFormat,
        &newColor.r,
        &newColor.g,
        &newColor.b,
        &newColor.a
    );

    uint32_t oldColor = GetColorAsHex();
    SetColor( newColor );
    SDL_FreeFormat( pixelFormat );
    
    return oldColor;
}

const uint32_t Text::GetColorAsHex() const
{
    SDL_Color color = GetColor();
    return
        color.a +
        ( color.b << 8 ) +
        ( color.g << 16 ) +
        ( color.r << 24 );
}

SDL_Color Text::SetColor( const SDL_Color& color )
{
    SDL_Color oldColor = m_Color;
    m_Color = color;
    return oldColor;
}

const SDL_Color& Text::GetColor() const
{
    return m_Color;
}

void Text::Draw( const std::string& text, const SDL_Point& point )
{
    m_Text = text;
    SDL_Rect dst = { point.x, point.y, 0, 0 };

    Draw( text, dst, true );
}

void Text::Draw( const std::string& text, const SDL_Rect& dst, bool noClip )
{
    m_Text = text;

    for ( const auto& textureInfo : m_FontInfo.textures )
    {
        SDL_Texture* texture = std::get<0>( textureInfo );
        SDL_SetTextureColorMod( texture, m_Color.r, m_Color.g, m_Color.b );
        SDL_SetTextureAlphaMod( texture, m_Color.a );
    }

    // to keep up with the current glyph drawing position
    SDL_Rect glyphDst{ dst.x, dst.y };

    // Text rendering
    for ( char character : text )
    {
        if ( m_FontInfo.glyphs.count( character ) == 0 ) continue;

        const auto& info = m_FontInfo.glyphs.at( character );
        glyphDst = { glyphDst.x, glyphDst.y, info.src.w, info.src.h };

        if ( !noClip && !SDL_HasIntersection( &glyphDst, &dst ) ) break;

        if ( info.textureId < m_FontInfo.textures.size() )
        {
            SDL_Texture* texture = std::get<0>( m_FontInfo.textures[info.textureId] );
            if ( texture != nullptr )
                SDL_RenderCopy( Engine::Instance()->GetRenderer(), texture, &info.src, &glyphDst );
        }

        glyphDst.x += info.src.w;
    }
}

SDL_Rect Text::Measure( const std::string& text, const SDL_Point& point ) const
{
    int width, height = 0;
    
    for ( char character : text )
    {
        if ( m_FontInfo.glyphs.count( character ) != 0 )
        {
            const auto& info = m_FontInfo.glyphs.at( character );
            width += info.src.w;
            height = std::max( info.src.h, height );
        }
    }

    return SDL_Rect{ point.x, point.y, width, height };
}

Text::~Text()
{
    Destroy();
}

void Text::Create( const std::vector<char>& glyphs )
{
    GenerateGlyphSurfaces( m_Fonts[m_FontID], glyphs, m_FontInfo );
    GenerateGlyphSrc( m_FontInfo );
    GenerateGlyphTextures( m_FontInfo, true );
}

void Text::Destroy()
{
    for ( auto& textureInfo : m_FontInfo.textures )
    {
        auto& texture = std::get<0>( textureInfo );
        if ( texture )
        {
            SDL_DestroyTexture( texture );
            texture = nullptr;
        }
    }
}

void Text::Clean()
{
    std::map<std::string, TTF_Font*>::iterator it;
    for ( it = m_Fonts.begin(); it != m_Fonts.end(); it++ )
        TTF_CloseFont( it->second );
    m_Fonts.clear();
}

const int Text::GetWidth() const
{
    SDL_Rect size = Measure( m_Text );
    return size.w;
}

const int Text::GetHeight() const
{
    SDL_Rect size = Measure( m_Text );
    return size.h;
}

static void GenerateGlyphSurfaces( TTF_Font* font, const std::vector<char>& glyphs, BitmapFontInfo& fontInfo )
{
    if ( !font || glyphs.empty() ) return;
    fontInfo.glyphs.clear();

    for ( char character : glyphs )
    {
        SDL_Surface* surface = TTF_RenderGlyph_Blended( font, character, SDL_Color{ 255, 255, 255, 255 } );
        if ( surface != nullptr )
        {
            fontInfo.glyphs[character] = GlyphInfo{
                surface,
                SDL_Rect{ 0, 0, surface->w, surface->h },
                0
            };
        }
    }
}

static void GenerateGlyphSrc( BitmapFontInfo& fontInfo )
{
    if ( !fontInfo.textures.empty() || fontInfo.glyphs.empty() ) return;

    constexpr int maxTextureWidth = 2048, maxTextureHeight = 2048;
    int textureWidth = 0, textureHeight = 0;
    size_t textureIndex = 0;
    int x = 0, y = 0, rowHeight = 0;

    for ( auto& pair : fontInfo.glyphs )
    {
        char character = pair.first;
        GlyphInfo& glyph = pair.second;

        // The current row's height should be the tallest glyph
        rowHeight = std::max( rowHeight, glyph.surface->h );

        // If the farthest x-extent has been reached, start a new row
        if ( x + glyph.surface->w >= maxTextureWidth )
        {
            x = 0;
            y += rowHeight;
            rowHeight = glyph.surface->h;
        }

        // If the farthest y-extent has been reached, configure the texture's dimensions and move onto the next texture
        if ( y + glyph.surface->h >= maxTextureHeight )
        {
            fontInfo.textures.push_back(
                std::make_tuple<SDL_Texture*, SDL_Rect>(
                    nullptr,
                    SDL_Rect{ 0, 0, textureWidth, textureHeight }
                )
            );

            textureIndex++;
            textureWidth = textureHeight = x = y = 0;
        }

        // Set the glyph's source rectangle
        glyph.src = SDL_Rect{ x, y, glyph.surface->w, glyph.surface->h };
        glyph.textureId = textureIndex;

        // Increment the x cord
        x += glyph.surface->w;

        // Use the greatest x or y to update the textureWidth and textureHeight
        textureWidth = std::max( x, textureWidth );
        textureHeight = std::max( y + rowHeight, textureHeight );
    }

    // The last texture's dimension needs to be setup after the loop
    if ( textureWidth > 0 && textureHeight > 0 )
    {
        fontInfo.textures.push_back(
            std::make_tuple<SDL_Texture*, SDL_Rect>(
                nullptr,
                SDL_Rect{ 0, 0, textureWidth, textureHeight }
            )
        );
    }
}

static void GenerateGlyphTextures( BitmapFontInfo& fontInfo, bool freeGlyphSurfaces )
{
    std::vector<SDL_Surface*> atlasSurfaces;
    for ( auto& textureInfo : fontInfo.textures )
    {
        const SDL_Rect& dimensions = std::get<1>( textureInfo );
        SDL_Surface* atlasSurface = SDL_CreateRGBSurface( 0, dimensions.w, dimensions.h, 32, 
            #if SDL_BYTEORDER == SDL_BIG_ENDIAN
                0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff
            #else
                0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
            #endif
        );

        atlasSurfaces.push_back(atlasSurface );
    }

    for ( auto& pair : fontInfo.glyphs )
    {
        char character = pair.first;
        GlyphInfo& glyph = pair.second;
        const size_t textureIndex = glyph.textureId;

        // This is the dstrect in this context, since the destination surface will be the src later
        SDL_Rect dstrect = glyph.src;
        SDL_Rect srcrect = SDL_Rect{ 0, 0, dstrect.w, dstrect.h };
        SDL_Surface* dst = atlasSurfaces[textureIndex];
        if ( dst && glyph.surface )
        {
            // Disable blending for the glyph surface becauseif bleeding is enabled, black will bleed
            // through the anti-aliasing even though it's 0,0,0,0
            SDL_SetSurfaceBlendMode( glyph.surface, SDL_BLENDMODE_NONE );
            SDL_BlitSurface( glyph.surface, &srcrect, dst, &dstrect );
            if ( freeGlyphSurfaces )
            {
                SDL_FreeSurface( glyph.surface );
                glyph.surface = nullptr;
            }
        }
    }

    for ( size_t textureIndex = 0; textureIndex < fontInfo.textures.size(); textureIndex++ )
    {
        auto& texture = std::get<0>( fontInfo.textures[textureIndex] );
        auto& surface = atlasSurfaces[textureIndex];

        if ( surface )
        {
            texture = SDL_CreateTextureFromSurface( Engine::Instance()->GetRenderer(), surface );
            SDL_FreeSurface( surface );
            surface = nullptr;
        }
    }
}

const std::map<std::string, TTF_Font*> Text::GetFonts()
{
    return m_Fonts;
}
