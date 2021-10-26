#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <tinyxml.h>

#include <string>
#include <map>
#include <vector>
#include <tuple>
#include <unordered_map>

struct GlyphInfo
{
    SDL_Surface* surface; // Only used for generation
    SDL_Rect src;
    size_t textureId;
};

struct BitmapFontInfo
{
    std::vector<std::tuple<SDL_Texture*, SDL_Rect>> textures;
    std::unordered_map<char, GlyphInfo> glyphs;
};

class Text
{
public:
    Text();
    Text( std::string id, unsigned char startGlyph = 0, unsigned char endGlyph = 255 );
    Text( std::string id, const char* glyphs, size_t glyphsSize );
    Text( std::string id, const std::vector<char>& glyphs );
    virtual ~Text();

    void Init( std::string id );
    static bool Parse( std::string path );
    void Clean();

    uint32_t SetColor( uint32_t color );
    SDL_Color SetColor( const SDL_Color& color );
    const uint32_t GetColorAsHex() const;
    const SDL_Color& GetColor() const;

    void Draw( const std::string& text, const SDL_Point& point );
    void Draw( const std::string& text, const SDL_Rect& dst, bool noClip = true );
    SDL_Rect Measure( const std::string& text, const SDL_Point& point = SDL_Point{ 0, 0 } ) const;

    const int GetHeight() const;
    const int GetWidth() const;
    static const std::map<std::string, TTF_Font*> GetFonts();

private:
    void Create( const std::vector<char>& glyphs );
    void Destroy();

private:
    static std::map<std::string, TTF_Font*> m_Fonts;
    std::string m_FontID = "default";
    std::string m_Text;

    static constexpr int m_MaxTextureWidth = 2048;
    static constexpr int m_MaxTextureHeight = 2048;
    BitmapFontInfo m_FontInfo;
    SDL_Color m_Color = { 255, 255, 255, 255 };
};
