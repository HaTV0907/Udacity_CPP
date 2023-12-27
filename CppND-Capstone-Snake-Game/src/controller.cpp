#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include "game.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite, bool &ret) const {
    if(ret)
        if (snake.direction != input || snake.size == 1) snake.direction = opposite;
    else
        if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake, Game& game) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown, game._pos);
          break;

        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp, game._pos);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight, game._pos);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft, game._pos);
          break;

        case SDLK_SPACE:
            game.ChangeGameStatus();
            break;

        case SDLK_g:
            if(game._obstacle)
              game._obstacle = false; 
            else
            game._obstacle = true;
            break;
      }
    }
  }
}