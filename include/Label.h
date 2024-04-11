//
// Created by Тимур Ахметзянов on 26.03.2024.
//

#pragma once

#include "Div.h"

namespace kat {
  class Label : public Div {
   public:
    Label() : Div(), data_(""), color_(sf::Color::Black),
              paddings_(std::vector<float>(4, 0)),
              font_size_(30) {}

    Label(float x, float y,
          float width, float height,
          const std::string &data, const sf::Font &font,
          sf::RenderWindow *parent) : Div(x, y, width, height, parent),
                                      data_(data),
                                      color_(sf::Color::Black),
                                      paddings_(std::vector<float>(4, 0)),
                                      font_size_(30),
                                      font_(font) {}

    Label(float x, float y,
          float width, float height,
          std::string &&data, const sf::Font &font,
          sf::RenderWindow *parent) : Div(x, y, width, height, parent),
                                      data_(std::move(data)),
                                      color_(sf::Color::Black),
                                      paddings_(std::vector<float>(4, 0)),
                                      font_size_(30),
                                      font_(font) {
    }

    void render() override;

    const std::string &getData() const;
    virtual void setData(const std::string &data);

    const sf::Color &getColor() const;
    void setColor(const sf::Color &color);

    const sf::Font &getFont() const;
    void setFont(const sf::Font &font);
    int getFontSize() const;
    void setFontSize(int fontSize);

    const std::vector<float> &getPaddings() const;
    virtual void setPaddings(const std::vector<float>& paddings);

   private:
    std::string data_;
    sf::Color color_;
    sf::Font font_;
    int font_size_;
    std::vector<float> paddings_;
  };

  void Label::render() {
    sf::Text text;
    text.setFont(font_);
    text.setFillColor(color_);
    text.setCharacterSize(font_size_);
    text.setString(data_);
    text.setPosition(getX() + paddings_[0], getY() + paddings_[1]);

    sf::RectangleShape hor_rect, ver_rect;
    hor_rect.setPosition(getX(), getY() + getBorderRadius());
    hor_rect.setSize({getWidth(), getHeight() - 2*getBorderRadius()});
    hor_rect.setFillColor(getBackgroundColor());
    ver_rect.setPosition(getX() + getBorderRadius(), getY());
    ver_rect.setSize({getWidth() - 2*getBorderRadius(), getHeight()});
    ver_rect.setFillColor(getBackgroundColor());

    sf::CircleShape top_left_cir, top_right_cir;
    top_left_cir.setRadius(getBorderRadius());
    top_left_cir.setPosition(getX(), getY());
    top_left_cir.setFillColor(getBackgroundColor());
    top_right_cir.setRadius(getBorderRadius());
    top_right_cir.setPosition(getX() + getWidth() - 2*getBorderRadius(), getY());
    top_right_cir.setFillColor(getBackgroundColor());

    sf::CircleShape bottom_left_cir, bottom_right_cir;
    bottom_left_cir.setRadius(getBorderRadius());
    bottom_left_cir.setPosition(getX(), getY() + getHeight() - 2*getBorderRadius());
    bottom_left_cir.setFillColor(getBackgroundColor());
    bottom_right_cir.setRadius(getBorderRadius());
    bottom_right_cir.setPosition(getX() + getWidth() - 2*getBorderRadius(), getY() + getHeight() - 2*getBorderRadius());
    bottom_right_cir.setFillColor(getBackgroundColor());

    getParent()->draw(hor_rect);
    getParent()->draw(ver_rect);
    getParent()->draw(top_left_cir);
    getParent()->draw(top_right_cir);
    getParent()->draw(bottom_right_cir);
    getParent()->draw(bottom_left_cir);
    getParent()->draw(text);
  }

  const std::string &Label::getData() const {
    return data_;
  }

  void Label::setData(const std::string &data) {
    data_ = data;
  }

  const sf::Color &Label::getColor() const {
    return color_;
  }

  void Label::setColor(const sf::Color &color) {
    color_ = color;
  }

  const sf::Font &Label::getFont() const {
    return font_;
  }

  void Label::setFont(const sf::Font &font) {
    font_ = font;
  }

  int Label::getFontSize() const {
    return font_size_;
  }

  void Label::setFontSize(int fontSize) {
    font_size_ = fontSize;
  }

  const std::vector<float> &Label::getPaddings() const {
    return paddings_;
  }

  void Label::setPaddings(const std::vector<float> &paddings) {
    paddings_ = paddings;
  }
}