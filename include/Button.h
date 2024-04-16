//
// Created by Тимур Ахметзянов on 28.03.2024.
//

#pragma once

#include "Label.h"

namespace kat {
  class Button : public Label {
   public:
    Button() : Label() {}
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

    Div::render();
    getParent()->draw(text);
  }
}
