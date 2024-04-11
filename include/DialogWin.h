//
// Created by Тимур Ахметзянов on 30.03.2024.
//

#pragma once

#include "Button.h"


namespace kat {
  class DialogWin : public Button {
   public:
    DialogWin(): Button(), ac_btn_(Button()), no_btn_(Button()) {}
    DialogWin(float x, float y,
                 float width, float height,
                 const std::string &data, const sf::Font &font,
                 sf::RenderWindow *parent): Button(x, y, width, height, data, font, parent),
                                            ac_btn_(Button(x + width/8, y + 5*height/8, 50,
                                                           30, "AC", font, parent)),
                                            no_btn_(Button(x + 5*width/8, y + 5*height/8, 50,
                                                           30, "NO", font, parent)) {
      ac_btn_.setBorderRadius(10);
      ac_btn_.setFontSize(20);
      no_btn_.setBorderRadius(10);
      no_btn_.setFontSize(20);
    }

    void render() override {
      auto size = normalizeSize(getData(), getPaddings(), getFontSize(), 1.6f);
      auto old_width = getWidth(), old_height = getHeight();
      setWidth(std::max(old_width, size.first));
      setHeight(std::max(old_height, size.second));
      auto old_x = getX(), old_y = getY();
      setX(getX() - fabs(old_width - getWidth())/2);
      setY(getY() - fabs(old_height - getHeight())/2);
      Div::render();
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
      text.setPosition(text_x, text_y - 15);
      getParent()->draw(text);
      ac_btn_.setY(getY() + 5*getHeight()/8);
      ac_btn_.setX(getX() + getWidth()/8);
      no_btn_.setY(getY() + 5*getHeight()/8);
      no_btn_.setX(getX() + 5*getWidth()/8);
      no_btn_.render();
      ac_btn_.render();
      setX(old_x);
      setY(old_y);
      setHeight(old_height);
      setWidth(old_width);
      ac_btn_.setY(getY() + 5*getHeight()/8);
      ac_btn_.setX(getX() + getWidth()/8);
      no_btn_.setY(getY() + 5*getHeight()/8);
      no_btn_.setX(getX() + 5*getWidth()/8);
    }

    int isAnswered(float x, float y) {
      auto size = normalizeSize(getData(), getPaddings(), getFontSize(), 1.6f);
      auto old_width = getWidth(), old_height = getHeight();
      setWidth(std::max(old_width, size.first));
      setHeight(std::max(old_height, size.second));
      auto old_x = getX(), old_y = getY();
      setX(getX() - fabs(old_width - getWidth())/2);
      setY(getY() - fabs(old_height - getHeight())/2);
      ac_btn_.setY(getY() + 5*getHeight()/8);
      ac_btn_.setX(getX() + getWidth()/8);
      no_btn_.setY(getY() + 5*getHeight()/8);
      no_btn_.setX(getX() + 5*getWidth()/8);
      int ans = 0;
      if (ac_btn_.isPressed(x, y)) {
        ans = 1;
      } else if (no_btn_.isPressed(x, y)) {
        ans = -1;
      }
      setX(old_x);
      setY(old_y);
      setHeight(old_height);
      setWidth(old_width);
      ac_btn_.setY(getY() + 5*getHeight()/8);
      ac_btn_.setX(getX() + getWidth()/8);
      no_btn_.setY(getY() + 5*getHeight()/8);
      no_btn_.setX(getX() + 5*getWidth()/8);
      return ans;
    }

    void setCloseBackground(sf::Color background) {
      ac_btn_.setBackgroundColor(background);
      no_btn_.setBackgroundColor(background);
    }

    void setACButtonText(const std::string& data) {
      ac_btn_.setData(data);
    }

    void setNOButtonText(const std::string& data) {
      no_btn_.setData(data);
    }

   private:
    Button ac_btn_, no_btn_;
  };
}
