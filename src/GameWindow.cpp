//
// Created by Clo on 2019-07-14.
//

#include <iostream>
#include "GameWindow.h"
#include "LauncherWindow.h"
#include "Screen.h"

GameWindow::GameWindow(const LauncherParams &params)
  : m_window(sf::VideoMode(params.screenSize.x,  params.screenSize.y), "Roguelike Game", params.fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close),
    m_gui(m_window) {

  try {
    loadWidgets();
  } catch (const tgui::Exception &ex) {
    std::cerr << "Could not start game: " << ex.what() << std::endl;
    return;
  }

  loadScreens();
  changeScreen("MainMenu");
  mainLoop();
}

sf::RenderTarget& GameWindow::getRenderTarget() {
  return m_window;
}

void GameWindow::openQuitPopup() {
  m_guiQuitPopup->setVisible(true);
}

void GameWindow::close() {
  m_window.close();
}

void GameWindow::changeScreen(const sf::String& name) {
  if (name.isEmpty() || m_screens.find(name) != m_screens.cend()) {
    m_screenName = name;
  }
  else {
    std::cout << "\"" << name.toAnsiString() << "\" does not match any screen" << std::endl;
  }
}

void GameWindow::loadScreens() {
  m_screens["MainMenu"] = std::make_shared<Screens::MainMenu>(*this);
}

void GameWindow::loadWidgets() {
  tgui::Theme theme("themes/Black.txt");
  tgui::Theme::setDefault(&theme);

  m_guiQuitPopup = tgui::ChildWindow::create("Quit?");
  m_guiQuitPopup->setSize("&.width / 6", "&.height / 8");
  m_guiQuitPopup->setPosition("(&.size - size) / 2");
  m_guiQuitPopup->setResizable(false);
  m_guiQuitPopup->setKeepInParent(true);
  m_guiQuitPopup->setPositionLocked(true);
  m_guiQuitPopup->setVisible(false);
  m_guiQuitPopup->connect("closed", &tgui::ChildWindow::setVisible, m_guiQuitPopup, false);

  auto yesButton = tgui::Button::create("Yes");
  yesButton->setPosition("10%", "20%");
  yesButton->setSize("35%", "60%");
  yesButton->connect("pressed", &GameWindow::close, this);
  m_guiQuitPopup->add(yesButton);

  auto noButton = tgui::Button::create("No");
  noButton->setPosition("55%", "20%");
  noButton->setSize("35%", "60%");
  noButton->connect("pressed", &tgui::ChildWindow::setVisible, m_guiQuitPopup, false);
  m_guiQuitPopup->add(noButton);

  m_gui.add(m_guiQuitPopup);
}

void GameWindow::mainLoop() {
  while (m_window.isOpen()) {
    // Event loop
    sf::Event event;
    while (m_window.pollEvent(event)) {
      m_gui.handleEvent(event);

      if (!m_screenName.isEmpty() && !m_guiQuitPopup->isVisible()) {
        m_screens[m_screenName]->handleEvent(event);
      }
    }

    // Rendering
    m_window.clear();

    if (!m_screenName.isEmpty()) {
      m_screens[m_screenName]->draw();
    }

    m_gui.draw();

    m_window.display();
  }
}
