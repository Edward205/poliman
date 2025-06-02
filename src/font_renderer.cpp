#include <iostream>
#include "include/font_renderer.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_surface.h"

FontRenderer::FontRenderer(SDL_Renderer *renderer, const char *path, int x, int y, float scale, int max_chars)
{
    this->x = x;
    this->y = y;
    this->scale = scale;
    this->max_chars = max_chars;
    if(!loadFont(renderer, path))
        std::cerr << "Failed to load font: " << path << std::endl;
}

bool FontRenderer::loadFont(SDL_Renderer *renderer, const char* path)
{
    font_surface = SDL_LoadBMP(path);
    if(!font_surface)
        return false;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_DestroySurface(font_surface);
    if(!texture)
        return false;
    
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    font_texture = texture;
    return true;
}

void FontRenderer::render(SDL_Renderer *renderer)
{
    for(unsigned int i = 0; i < text.size(); ++i)
    {
        int aux = text[i] - 32; 

        SDL_FRect srcrect({1.0f + (float)(aux % 16) * 6.0f, 2.0f + (float)(aux / 16) * 12.0f, 5.0f, 9.0f});
        SDL_FRect destrect({x + (i % max_chars) * (5.0f * scale + 2.0f), y + (i / max_chars) * (8.0f * scale), 5.0f * scale,9.0f * scale});

        SDL_RenderTexture(renderer, font_texture, &srcrect, &destrect);
    }}

FontRenderer::~FontRenderer()
{
    SDL_DestroySurface(font_surface);
}