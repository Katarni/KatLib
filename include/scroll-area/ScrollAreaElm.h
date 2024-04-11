//
// Created by Тимур Ахметзянов on 29.03.2024.
//

#pragma once

#include "../Button.h"


namespace kat {
  class ScrollAreaElm : public Button {
   public:
    ScrollAreaElm() : Button(), selected_(false) {}
    ScrollAreaElm(float x, float y,
           float width, float height,
           const std::string &data, const sf::Font &font,
           sf::RenderWindow *parent) : Button(x, y, width, height, data, font, parent), selected_(false) {}

    bool isSelected() const {
      return selected_;
    }

    void setSelected(bool selected) {
      selected_ = selected;
    }

    bool isPressed(float x, float y) override {
      if (Button::isPressed(x, y)) {
        selected_ = !selected_;
      }
      return selected_;
    }

   private:
    bool selected_;
  };
}
