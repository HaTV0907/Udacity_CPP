#include "game.h"
#include <iostream>
#include "SDL.h"

#include <thread>
#include <chrono>
#include <future>
Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height, &score),
    engine(dev()),
    random_w(0, static_cast<int>(grid_width)),
    random_h(0, static_cast<int>(grid_height)) {
    PlaceFood();
}

void Game::Run(Controller const &controller, Renderer *renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, *this);
    Update(renderer);
    renderer->Render(snake, food, &_obstacle, &_pos);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer->UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update(Renderer* renderer) {
    if (this->_pause == true) {
        renderer->PauseMsg();
        return;
    };
    if (!snake.alive)
    {
        return;
    }

    SDL_Window* _pWin = renderer->GetSDLWin();
    snake.Update(&_obstacle, _pWin);

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    std::random_device _rndDev;
    std::mt19937 _rndGen(_rndDev());
    std::uniform_int_distribution<> _rndDis(1, 10);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
        score++;
        PlaceFood();
        // Grow snake and increase speed.
        snake.GrowBody();
        if (_rndDis(_rndGen) <= 2) {
            _pos = true;
            std::thread _tid([&]() {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
                _pos = false;
                lock.unlock(); // Unlock the mutex
                });
            _tid.detach();
        }

    }
}
void Game::ChangeGameStatus() {
    this->_pause ? ResumeGame() : PauseGame();
}

void Game::PauseGame() {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    this->_pause = true;
    lock.unlock(); // Unlock the mutex
}

void Game::ResumeGame() {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    this->_pause = false;
    lock.unlock(); // Unlock the mutex
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }