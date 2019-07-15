//
// Created by Clo on 2019-07-13.
//

#include <iostream>
#include "LauncherWindow.h"
#include "macros.h"

LauncherWindow::LauncherWindow()
    : m_window(VideoMode169(360), "Roguelike Launcher", sf::Style::Titlebar | sf::Style::Close),
      m_gui(m_window),
      m_shouldLaunch(false) {

  m_params.screenSize = sf::Vector2u(854, 480);
  m_params.fullscreen = false;

  try {
    loadWidgets();
    eventLoop();
  } catch (const tgui::Exception &ex) {
    std::cerr << "Could not start launcher: " << ex.what() << std::endl;
  }
}

bool LauncherWindow::shouldLaunch() const noexcept {
  return m_shouldLaunch;
}

const LauncherParams* LauncherWindow::getParams() const noexcept {
  return &m_params;
}

void LauncherWindow::loadWidgets() {
  tgui::Theme theme("themes/Black.txt");
  tgui::Theme::setDefault(&theme);

  auto launchButton = tgui::Button::create("Launch game");
  launchButton->setPosition("(&.width - width) / 2", "70%");
  launchButton->setSize("40%", "16.67%");
  launchButton->setTextSize(0);
  launchButton->connect("pressed", &LauncherWindow::launchGame, this);
  m_gui.add(launchButton);
}

void LauncherWindow::eventLoop() {
  while (m_window.isOpen()) {
    // Event loop
    sf::Event event;
    while (m_window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        m_window.close();
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Key::Escape) {
          m_window.close();
        } else if (event.key.code == sf::Keyboard::Key::Enter) {
          launchGame();
        }
        break;
      default:
        break;
      }

      // Pass the event to all the widgets
      m_gui.handleEvent(event);
    }

    // Rendering
    m_window.clear();
    m_gui.draw();
    m_window.display();
  }
}

void LauncherWindow::launchGame() {
  m_shouldLaunch = true;
  m_window.close();
}

std::ostream& operator << (std::ostream& out, const LauncherParams* params) {
  if (params == nullptr) {
    return out << "null";
  }

  return out << std::boolalpha
      <<"{"
      << "width: " << params->screenSize.x << ", "
      << "height: " << params->screenSize.y << ", "
      << "fullscreen: " << params->fullscreen
      << "}";
}