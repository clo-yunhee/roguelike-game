//
// Created by Clo on 2019-07-14.
//

#ifndef ROGUELIKE__SCREEN_H
#define ROGUELIKE__SCREEN_H

#include <SFML/Graphics.hpp>

#include "macros.h"

class GameWindow;

class Screen {
public:
  explicit Screen(GameWindow& window);

  virtual void draw() = 0;
  virtual void handleEvent(const sf::Event& event) = 0;

protected:
  GameWindow& m_window;
};

namespace Screens {

class MainMenu : public Screen {
public:
  SCREEN_PUBLIC(MainMenu)

private:
  SCREEN_PRIVATE()
  enum Button { Start, Settings, Exit };
  void buttonPressed(Button target);
};

}

#endif //ROGUELIKE__SCREEN_H
