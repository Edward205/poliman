#include <random>
#include <string>

#include "include/quiz.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "include/defines.h"
#include "include/font_renderer.h"

void Quiz::init(SDL_Renderer *renderer)
{
    question = new FontRenderer(renderer, "../res/monogram.bmp", 90, 180, 2, 53);
    answer1 = new FontRenderer(renderer, "../res/monogram.bmp", 90, 180+(70*1), 2, 50);
    answer2 = new FontRenderer(renderer, "../res/monogram.bmp", 90, 180+(70*2), 2, 50);
    answer3 = new FontRenderer(renderer, "../res/monogram.bmp", 90, 180+(70*3), 2, 50);
    answer4 = new FontRenderer(renderer, "../res/monogram.bmp", 90, 180+(70*4), 2, 50);
}

void Quiz::render(SDL_Renderer* renderer) {
    if(active)
    {
        printf("%d\n", questionIndex);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 100);
        SDL_FRect background = {0, 0, WINDOW_WIDTH, WINDOW_WIDTH};
        SDL_RenderFillRect(renderer, &background);
        
        background = SDL_FRect({question->x-5, question->y-5, 646+10, 30+10});
        SDL_SetRenderDrawColor(renderer, 75, 75, 100, 255);
        SDL_RenderFillRect(renderer, &background);

        question->render(renderer);
        answer1->render(renderer);
        answer2->render(renderer);
        answer3->render(renderer);
        answer4->render(renderer);
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

        question->text = std::string(quizes[questionIndex].first);
        answer1->text = std::string(quizes[questionIndex+1].first);
        answer2->text = std::string(quizes[questionIndex+2].first);
        answer3->text = std::string(quizes[questionIndex+3].first);
        answer4->text = std::string(quizes[questionIndex+4].first);

    }
}

Quiz::~Quiz()
{
    delete question;
    delete answer1;
    delete answer2;
    delete answer3;
    delete answer4;
}