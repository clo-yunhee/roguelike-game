//
// Created by Clo on 2019-07-14.
//

#include "../Screen.h"
#include "../GameWindow.h"

using namespace Screens;

MainMenu::MainMenu(GameWindow& window)
  : Screen(window), m_gui(window.getRenderTarget()) {
  loadWidgets();
}

void MainMenu::loadWidgets() {
  tgui::Theme theme("themes/Black.txt");
  tgui::Theme::setDefault(&theme);

  auto buttonTemplate = tgui::Button::create();
  buttonTemplate->setSize("50%", "10%");
  buttonTemplate->setTextSize(24);

  auto verticalLayout = tgui::VerticalLayout::create({"75%", "62.5%"});
  verticalLayout->setPosition("(&.size - size) / 2");

  verticalLayout->insertSpace(-1, 1.0f);

  auto startButton = tgui::Button::copy(buttonTemplate);
  startButton->setText("Start game");
  startButton->connect("pressed", &MainMenu::buttonPressed, this, Button::Start);
  verticalLayout->add(startButton);

  verticalLayout->insertSpace(-1, 0.5f);

  auto settingsButton = tgui::Button::copy(buttonTemplate);
  settingsButton->setText("Settings");
  settingsButton->connect("pressed", &MainMenu::buttonPressed, this, Button::Settings);
  verticalLayout->add(settingsButton);

  verticalLayout->insertSpace(-1, 0.5f);

  auto quitButton = tgui::Button::copy(buttonTemplate);
  quitButton->setText("Exit");
  quitButton->connect("pressed", &MainMenu::buttonPressed, this, Button::Exit);
  verticalLayout->add(quitButton);

  verticalLayout->insertSpace(-1, 1.0f);

  m_gui.add(verticalLayout);
}

void MainMenu::buttonPressed(MainMenu::Button target) {
  if (target == Button::Start) {
    m_window.changeScreen("Game");
  }
  else if (target == Button::Settings) {
    m_window.changeScreen("Settings");
  }
  else if (target == Button::Exit) {
    m_window.close();
  }
}

void MainMenu::draw() {
  m_gui.draw();
}

void MainMenu::handleEvent(const sf::Event &event) {
  if (event.type == sf::Event::Closed
      || (event.type == sf::Event::KeyPressed
          && event.key.code == sf::Keyboard::Key::Escape)) {
    m_window.close();
    return;
  }

  m_gui.handleEvent(event);
}