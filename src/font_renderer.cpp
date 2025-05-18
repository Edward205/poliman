#include <iostream>
#include "include/font_renderer.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_surface.h"

FontRenderer::FontRenderer(SDL_Renderer *renderer, const char *path, int x, int y, int scale)
{
    this->x = x;
    this->y = y;
    this->scale = scale;
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
    for(unsigned int i = 0; i < text.size(); ++i)
    {
        int aux = text[i] - 32;
        // very exact variables made specifically for the monogram bitmap font
        // to be generalised later
        SDL_FRect srcrect({(float) 1 + (5 * (aux % 16)) + (aux % 16), (float) (12 * (aux / 16)) + 2, 5, 7});
        SDL_FRect destrect({x + i * 5 * scale + (i * 2), y, 5.0f * scale, 7.0f * scale});
        SDL_RenderTexture(renderer, font_texture, &srcrect, &destrect);
    }
}

FontRenderer::~FontRenderer()
{
    SDL_DestroySurface(font_surface);
}