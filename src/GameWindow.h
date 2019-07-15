//
// Created by Clo on 2019-07-14.
//

#ifndef ROGUELIKE__GAMEWINDOW_H
#define ROGUELIKE__GAMEWINDOW_H

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

struct LauncherParams;
class Screen;

class GameWindow {
public:
  explicit GameWindow(const LauncherParams& params);

  sf::RenderTarget& getRenderTarget();

  void openQuitPopup();
  void close();

  void changeScreen(const sf::String& name);

private:
  void loadScreens();

  void loadWidgets();
  void mainLoop();

  sf::RenderWindow m_window;
  tgui::Gui m_gui;

  tgui::ChildWindow::Ptr m_guiQuitPopup;

  sf::String m_screenName;
  std::map<sf::String, std::shared_ptr<Screen>> m_screens;
};

#endif //ROGUELIKE__GAMEWINDOW_H
