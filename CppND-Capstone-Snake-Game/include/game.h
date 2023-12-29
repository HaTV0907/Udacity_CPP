#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <mutex>
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer *renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  void ChangeGameStatus();
  friend class Controller;
protected:
    bool _obstacle;

 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update(Renderer* renderer);
  void PauseGame();
  void ResumeGame();
  bool _pause;
  bool _pos;
  std::mutex mtx;
};

#endif