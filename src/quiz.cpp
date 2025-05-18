#include <iostream>
#include <random>
#include <string>

#include "include/quiz.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "include/defines.h"
#include "include/font_renderer.h"

void Quiz::init(SDL_Renderer *renderer)
{
    question = new FontRenderer(renderer, "../res/monogram.bmp", 10, 55, 2, 65);
    answer1 = new FontRenderer(renderer, "../res/monogram.bmp", 10, 35, 2, 65);
    answer2 = new FontRenderer(renderer, "../res/monogram.bmp", 10, 45, 2, 65);
    answer3 = new FontRenderer(renderer, "../res/monogram.bmp", 10, 55, 2, 65);
}

void Quiz::render(SDL_Renderer* renderer) {
    if(active)
    {
        printf("%d\n", questionIndex);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 100);
        SDL_FRect background = {0, 0, WINDOW_WIDTH, WINDOW_WIDTH};
        SDL_RenderFillRect(renderer, &background);

        std::cout << quizes[questionIndex].first << std::endl;
        question->text = std::string(quizes[questionIndex].first);
        question->render(renderer);
    }
}

void Quiz::triggerQuiz() {
    if(!active)
    {
        active = true;
    
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 200 / 5);
        questionIndex = distrib(gen) * 5;
    }
}

Quiz::~Quiz()
{
    delete question;
}