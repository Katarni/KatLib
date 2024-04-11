//
// Created by Тимур Ахметзянов on 27.03.2024.
//

#pragma once

#include "header.h"


namespace kat {
  class Div {
   public:
    Div(): x_(0), y_(0),
           width_(0), height_(0),
           parent_(nullptr), border_radius_(0), background_color_(sf::Color::White) {}

    Div(float x, float y,
        float width, float height,
        sf::RenderWindow* parent): x_(x), y_(y),
                                   width_(width), height_(height),
                                   parent_(parent), background_color_(sf::Color::White),
                                   border_radius_(0){}

    Div& operator=(const Div& div) = default;

    virtual void render();

    void setBackgroundColor(sf::Color color) {
      background_color_ = color;
    }

    const sf::Color &getBackgroundColor() const;

    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);

    float getWidth() const;
    virtual void setWidth(float width);
    float getHeight() const;
    void setHeight(float height);

    sf::RenderWindow *getParent() const;
    void setParent(sf::RenderWindow *parent);

    const float &getBorderRadius() const;
    void setBorderRadius(float border_radius);

    bool isHovered(float x, float y) const;

    void moveY(float d) {
      y_ += d;
    }

    void moveX(float d) {
      x_ += d;
    }

   private:
    sf::Color background_color_;
    float x_, y_;
    float width_, height_;
    sf::RenderWindow* parent_;
    float border_radius_;
  };

  void Div::render() {
    sf::RectangleShape hor_rect;
    hor_rect.setPosition(x_, y_ + border_radius_);
    hor_rect.setSize({width_, height_ - 2*border_radius_});
    hor_rect.setFillColor(background_color_);

    sf::RectangleShape ver_rect;
    ver_rect.setPosition(x_ + border_radius_, y_);
    ver_rect.setSize({width_ - 2*border_radius_, height_});
    ver_rect.setFillColor(background_color_);

    sf::CircleShape top_left_cir;
    top_left_cir.setRadius(border_radius_);
    top_left_cir.setPosition(x_, y_);
    top_left_cir.setFillColor(background_color_);

    sf::CircleShape top_right_cir;
    top_right_cir.setRadius(border_radius_);
    top_right_cir.setPosition(x_ + width_ - 2*border_radius_, y_);
    top_right_cir.setFillColor(background_color_);

    sf::CircleShape bottom_left_cir;
    bottom_left_cir.setRadius(border_radius_);
    bottom_left_cir.setPosition(x_, y_ + height_ - 2*border_radius_);
    bottom_left_cir.setFillColor(background_color_);

    sf::CircleShape bottom_right_cir;
    bottom_right_cir.setRadius(border_radius_);
    bottom_right_cir.setPosition(x_ + width_ - 2*border_radius_, y_ + height_ - 2*border_radius_);
    bottom_right_cir.setFillColor(background_color_);

    parent_->draw(hor_rect);
    parent_->draw(ver_rect);
    parent_->draw(top_left_cir);
    parent_->draw(top_right_cir);
    parent_->draw(bottom_right_cir);
    parent_->draw(bottom_left_cir);
  }

  const sf::Color &Div::getBackgroundColor() const {
    return background_color_;
  }

  float Div::getX() const {
    return x_;
  }

  void Div::setX(float x) {
    x_ = x;
  }

  float Div::getY() const {
    return y_;
  }

  void Div::setY(float y) {
    y_ = y;
  }

  float Div::getWidth() const {
    return width_;
  }

  void Div::setWidth(float width) {
    width_ = width;
  }

  float Div::getHeight() const {
    return height_;
  }

  void Div::setHeight(float height) {
    height_ = height;
  }

  sf::RenderWindow *Div::getParent() const {
    return parent_;
  }

  void Div::setParent(sf::RenderWindow *parent) {
    parent_ = parent;
  }

  const float &Div::getBorderRadius() const {
    return border_radius_;
  }

  void Div::setBorderRadius(float border_radius) {
    border_radius_ = border_radius;
  }

  bool Div::isHovered(float x, float y) const {
    if (x >= x_ &&
        y >= y_ + border_radius_ &&
        x <= x_ + width_ &&
        y <= y_ + height_ - 2*border_radius_) {
      return true;
    }

    if (x >= x_ + border_radius_ &&
        y >= y_ &&
        x <= x_ + width_ - 2*border_radius_ &&
        y <= y_ + height_) {
      return true;
    }

    if ((x - x_ - border_radius_)*(x - x_ - border_radius_) +
        (y - y_ - border_radius_)*(y - y_ - border_radius_) <=
        border_radius_*border_radius_) {
      return true;
    }

    if ((x - x_ - width_ + border_radius_)*(x - x_ - width_ + border_radius_) +
        (y - y_ - border_radius_)*(y - y_ - border_radius_) <=
        border_radius_*border_radius_) {
      return true;
    }

    if ((x - x_ - border_radius_)*(x - x_ - border_radius_) +
        (y - y_ + border_radius_ - height_)*(y - y_ + border_radius_ - height_) <=
        border_radius_*border_radius_) {
      return true;
    }

    if ((x - x_ - width_ + border_radius_)*(x - x_ - width_ + border_radius_) +
        (y - y_ + border_radius_ - height_)*(y - y_ + border_radius_ - height_) <=
        border_radius_*border_radius_) {
      return true;
    }

    return false;
  }
}
