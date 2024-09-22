//
// Created by Тимур Ахметзянов on 28.03.2024.
//

#pragma once

#include "Label.h"

namespace kat {
  class Button : public Label {
   public:
    Button() : Label() {}
    Button(sf::RenderWindow* parent) : Label(parent) {}
    Button(float x, float y,
           float width, float height,
           const std::string &data, const sf::Font &font,
           sf::RenderWindow *parent) : Label(x, y, width, height, data, font, parent) {}

    virtual inline bool isPressed(float x, float y) {
      return Div::isHovered(x, y);
    }

    void render() override;
  };

  void Button::render() {
    if (!needRender()) return;
    auto text_params = getStringParams(getData());
    float text_x = (getWidth() - (float)text_params.first*(float)getFontSize()/1.6f)/ 2 + getX();
    float text_y = getY() +
                   (getHeight() - (float)text_params.second*(float)getFontSize()) / 2 -
                   (float)getFontSize()/5;

    sf::Text text;
    text.setFont(getFont());
    text.setFillColor(getColor());
    text.setCharacterSize(getFontSize());
    text.setString(getData());
    text.setPosition(text_x, text_y);

    Div::render();
    getParent()->draw(text);
  }
}
