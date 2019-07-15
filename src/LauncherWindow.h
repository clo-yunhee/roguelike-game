//
// Created by Clo on 2019-07-13.
//

#ifndef ROGUELIKE__LAUNCHERWINDOW_H
#define ROGUELIKE__LAUNCHERWINDOW_H

#include <ostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

struct LauncherParams {
  bool fullscreen;
  sf::Vector2u screenSize;
};

class LauncherWindow {
public:
  LauncherWindow();

  bool shouldLaunch() const noexcept;
  const LauncherParams* getParams() const noexcept;

private:
  void loadWidgets();
  void eventLoop();

  void launchGame();

  sf::RenderWindow m_window;
  tgui::Gui m_gui;

  bool m_shouldLaunch;
  LauncherParams m_params;
};

std::ostream& operator << (std::ostream& out, const LauncherParams* params);

#endif //ROGUELIKE__LAUNCHERWINDOW_H
