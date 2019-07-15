//
// Created by Clo on 2019-07-13.
//

#ifndef ROGUELIKE__MACROS_H
#define ROGUELIKE__MACROS_H

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <TGUI/TGUI.hpp>

class GameWindow;

inline auto VideoMode169(unsigned int height) {
  return sf::VideoMode((height * 16) / 9, height);
}

// Macro to declare public virtual functions in a child Screen class.
#define SCREEN_PUBLIC(name)                         \
  explicit name (GameWindow& window);               \
  virtual void draw();                              \
  virtual void handleEvent(const sf::Event& event);

// Macro to declare common private members in a child Screen class.
#define SCREEN_PRIVATE() \
  void loadWidgets();    \
  tgui::Gui m_gui;

#endif //ROGUELIKE__MACROS_H
