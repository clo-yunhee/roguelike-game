//
// Created by Clo on 2019-07-13.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "LauncherWindow.h"
#include "GameWindow.h"

int main() {
  LauncherWindow launcher;

  std::cout << "Launcher exited." << std::endl;

  if (!launcher.shouldLaunch()) {
    std::cout << "Not starting game." << std::endl;
    return 0;
  }

  std::cout << "Starting game with: " << launcher.getParams() << std::endl;

  GameWindow game(*launcher.getParams());

  return 0;
}