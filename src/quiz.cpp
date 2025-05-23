#include <random>
#include <string>

#include "include/quiz.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "include/defines.h"
#include "include/font_renderer.h"

void Quiz::init(SDL_Renderer *renderer)
{
    question = new FontRenderer(renderer, "../res/monogram.bmp", WINDOW_WIDTH / 2 - 656 / 2, 180, 2, 53);
    answer1 = new Button(renderer, WINDOW_WIDTH / 2 - 656 / 2, 320+(70*1), 656, 40, 50, "caca");
    answer2 = new Button(renderer, WINDOW_WIDTH / 2 - 656 / 2, 320+(70*2), 656, 40, 50, "caca");
    answer3 = new Button(renderer, WINDOW_WIDTH / 2 - 656 / 2, 320+(70*3), 656, 40, 50, "caca");
    answer4 = new Button(renderer, WINDOW_WIDTH / 2 - 656 / 2, 320+(70*4), 656, 40, 50, "caca");
}

void Quiz::handleInput(SDL_Event e)
{
    if(active)
    {
        answer1->handleInput(e);
        answer2->handleInput(e);
        answer3->handleInput(e);
        answer4->handleInput(e);
    }
}

void Quiz::render(SDL_Renderer* renderer) {
    if(active)
    {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 100);
        SDL_FRect background = {0, 0, WINDOW_WIDTH, WINDOW_WIDTH};
        SDL_RenderFillRect(renderer, &background);
        
        background = SDL_FRect({question->x-5, question->y-5, 656+10, 48+10});
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
        std::uniform_int_distribution<> distrib(0, 195 / 5);
        questionIndex = distrib(gen) * 5;

        question->text = std::string(quizes[questionIndex].first);
        answer1->text = std::string(quizes[questionIndex+1].first);
        answer2->text = std::string(quizes[questionIndex+2].first);
        answer3->text = std::string(quizes[questionIndex+3].first);
        answer4->text = std::string(quizes[questionIndex+4].first);

        // why can't i set these to a normal function ???
        answer1->onPressed = ([&] { if(quizes[questionIndex+1].second == true) state = 1; else state = 2; return 0; });
        answer2->onPressed = ([&] { if(quizes[questionIndex+2].second == true) state = 1; else state = 2; return 0; });
        answer3->onPressed = ([&] { if(quizes[questionIndex+3].second == true) state = 1; else state = 2; return 0; });
        answer4->onPressed = ([&] { if(quizes[questionIndex+4].second == true) state = 1; else state = 2; return 0; });
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