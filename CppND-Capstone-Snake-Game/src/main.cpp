#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <memory>
#include "syslog.h"

int main() {
   std::shared_ptr<sysLog> _sysLogFile = std::make_shared<sysLog>();
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  _sysLogFile->save("___________Start game___________");
  std::string _playerName{"Hatv"};

  std::cout << "Enter your name:" << std::endl;
  std::cin >> _playerName;
  std::cout << "Hello " << _playerName << std::endl;
  std::cout << "Game started. Enjoy!\n";
  std::cout << "Press G create/delete obstacle!\n";
  std::cout << "Press SPACE to pause/resume!\n";
  game.Run(controller, &renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  /* Save reslult to file */
  std::string _nameToSave = "Player's name:" + _playerName;
  _sysLogFile->save(_nameToSave.c_str());
  std::string _scoreToSave = "Score: " + std::to_string(game.GetScore());
  _sysLogFile->save(_scoreToSave.c_str());
  std::string _sizeToSave = "Size: " + std::to_string(game.GetSize());
  _sysLogFile->save(_sizeToSave.c_str());
  _sysLogFile->save("___________End game___________");
  
  return 0;
}