//
// Created by Тимур Ахметзянов on 16.04.2024.
//

#pragma once

#include "Button.h"


namespace kat {
  class SelectedItem : public Button {
   public:
    SelectedItem() : Button(), is_selected_(false), selected_color_(sf::Color::Black) {}

    SelectedItem(float x, float y,
                 float width, float height,
                 const std::string &data, const sf::Font &font,
                 sf::RenderWindow *parent) : Button(x, y, width, height, data, font, parent), is_selected_(false),
                                             selected_color_(getBackgroundColor()) {}

    inline bool isPressed(float x, float y) override {
      if (Button::isPressed(x, y)) {
        is_selected_ = !is_selected_;
        return true;
      }
      return false;
    }

    void render() override;

    void setSelectedColor(sf::Color color) {
      selected_color_ = color;
    }

    const sf::Color &getSelectedColor() const {
      return selected_color_;
    }

   private:
    bool is_selected_;
    sf::Color selected_color_;
  };


  void SelectedItem::render() {
    if (!needRender()) return;
    auto text_params = getStringParams(getData());
    float text_x = (getWidth() - (float) text_params.first * (float) getFontSize() / 1.6f) / 2 + getX();
    float text_y = getY() +
                   (getHeight() - (float) text_params.second * (float) getFontSize()) / 2 -
                   (float) getFontSize() / 5;

    sf::Text text;
    text.setFont(getFont());
    text.setFillColor(getColor());
    text.setCharacterSize(getFontSize());
    text.setString(getData());
    text.setPosition(text_x, text_y);

    sf::RectangleShape hor_rect, ver_rect;
    hor_rect.setPosition(getX(), getY() + getBorderRadius());
    hor_rect.setSize({getWidth(), getHeight() - 2 * getBorderRadius()});
    hor_rect.setFillColor(is_selected_ ? selected_color_ : getBackgroundColor());
    ver_rect.setPosition(getX() + getBorderRadius(), getY());
    ver_rect.setSize({getWidth() - 2 * getBorderRadius(), getHeight()});
    ver_rect.setFillColor(is_selected_ ? selected_color_ : getBackgroundColor());

    sf::CircleShape top_left_cir, top_right_cir;
    top_left_cir.setRadius(getBorderRadius());
    top_left_cir.setPosition(getX(), getY());
    top_left_cir.setFillColor(is_selected_ ? selected_color_ : getBackgroundColor());
    top_right_cir.setRadius(getBorderRadius());
    top_right_cir.setPosition(getX() + getWidth() - 2 * getBorderRadius(), getY());
    top_right_cir.setFillColor(is_selected_ ? selected_color_ : getBackgroundColor());

    sf::CircleShape bottom_left_cir, bottom_right_cir;
    bottom_left_cir.setRadius(getBorderRadius());
    bottom_left_cir.setPosition(getX(), getY() + getHeight() - 2 * getBorderRadius());
    bottom_left_cir.setFillColor(is_selected_ ? selected_color_ : getBackgroundColor());
    bottom_right_cir.setRadius(getBorderRadius());
    bottom_right_cir.setPosition(getX() + getWidth() - 2 * getBorderRadius(),
                                 getY() + getHeight() - 2 * getBorderRadius());
    bottom_right_cir.setFillColor(is_selected_ ? selected_color_ : getBackgroundColor());

    getParent()->draw(hor_rect);
    getParent()->draw(ver_rect);
    getParent()->draw(top_left_cir);
    getParent()->draw(top_right_cir);
    getParent()->draw(bottom_right_cir);
    getParent()->draw(bottom_left_cir);
    getParent()->draw(text);
  }
}