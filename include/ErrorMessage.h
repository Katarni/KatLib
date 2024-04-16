//
// Created by Тимур Ахметзянов on 30.03.2024.
//

#pragma once

#include "Button.h"


namespace kat {
  class ErrorMessage : public Button {
   public:
    ErrorMessage(): Button(), close_btn_(Button()), need_render_(false) {}
    ErrorMessage(float x, float y,
                 float width, float height,
                 const std::string &data, const sf::Font &font,
                 sf::RenderWindow *parent): Button(x, y, width, height, data, font, parent),
                                            close_btn_(Button(x + 7, y + 7, 26, 26, "x", font, parent)),
                                            need_render_(false) {
      close_btn_.setBorderRadius(13);
      close_btn_.setFontSize(20);
    }

    void render() override {
      auto size = normalizeSize(getData(), getPaddings(), getFontSize(), 1.6f);
      auto old_width = getWidth(), old_height = getHeight();
      setWidth(std::max(old_width, size.first));
      setHeight(std::max(old_height, size.second));
      auto old_x = getX(), old_y = getY();
      setX(getX() - fabs(old_width - getWidth())/2);
      setY(getY() - fabs(old_height - getHeight())/2);
      Button::render();
      close_btn_.setY(getY() + 7);
      close_btn_.setX(getX() + 7);
      close_btn_.render();
      setX(old_x);
      setY(old_y);
      setHeight(old_height);
      setWidth(old_width);
      close_btn_.setY(getY() + 7);
      close_btn_.setX(getX() + 7);
    }

    bool isPressed(float x, float y) override {
      auto size = normalizeSize(getData(), getPaddings(), getFontSize(), 1.6f);
      auto old_width = getWidth(), old_height = getHeight();
      setWidth(std::max(old_width, size.first));
      setHeight(std::max(old_height, size.second));
      auto old_x = getX(), old_y = getY();
      setX(getX() - fabs(old_width - getWidth())/2);
      setY(getY() - fabs(old_height - getHeight())/2);
      close_btn_.setY(getY() + 7);
      close_btn_.setX(getX() + 7);
      bool ans = close_btn_.isPressed(x, y);
      setX(old_x);
      setY(old_y);
      setHeight(old_height);
      setWidth(old_width);
      close_btn_.setY(getY() + 7);
      close_btn_.setX(getX() + 7);
      return ans;
    }

    void setCloseBackground(sf::Color background) {
      close_btn_.setBackgroundColor(background);
    }

    bool needRender() const {
      return need_render_;
    }

    void setNeedRender(bool need_render) {
      need_render_ = need_render;
    }

    void switchNeedRender() {
      need_render_ = !need_render_;
    }

   private:
    Button close_btn_;
    bool need_render_;
  };
}

