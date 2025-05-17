#include <iostream>
#include "include/font_renderer.h"
#include "SDL3/SDL_surface.h"

FontRenderer::FontRenderer(SDL_Renderer *renderer, const char *path)
{
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
    if(!font_texture)
        return false;

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_PIXELART);
    font_texture = texture;
    return true;
}

void FontRenderer::render(SDL_Renderer *renderer)
{
    for(char c : text)
    {
        int aux = c - 32;
        SDL_FRect destrect({x, y, 96.0f * scale, 96.0f * scale});
        SDL_RenderTexture(renderer, font_texture, NULL, &destrect);
    }
}

FontRenderer::~FontRenderer()
{
    SDL_DestroySurface(font_surface);
}