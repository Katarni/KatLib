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
           parent_(nullptr), border_radius_(0), background_color_(sf::Color::White),
           need_render_(true) {}

    Div(sf::RenderWindow* window): x_(0), y_(0),
           width_(0), height_(0),
           parent_(window), border_radius_(0), background_color_(sf::Color::White),
           need_render_(true) {}

    Div(float x, float y,
        float width, float height,
        sf::RenderWindow* parent): x_(x), y_(y),
                                   width_(width), height_(height),
                                   parent_(parent), background_color_(sf::Color::White),
                                   border_radius_(0), need_render_(true) {
      border_bold_ = 0;
      border_color_ = sf::Color::Black;
    }

    Div& operator=(const Div& div) = default;

    virtual void render();

    virtual void setBackgroundColor(sf::Color color) {
      background_color_ = color;
    }

    const sf::Color &getBackgroundColor() const;

    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
    float getCenterX() const;
    float getCenterY() const;

    float getWidth() const;
    virtual void setWidth(float width);
    float getHeight() const;
    void setHeight(float height);

    sf::RenderWindow *getParent() const;
    void setParent(sf::RenderWindow *parent);

    const float &getBorderRadius() const;
    void setBorderRadius(float border_radius);

    inline bool isHovered(float x, float y) const;

    virtual void moveY(float d) {
      y_ += d;
    }

    virtual void moveX(float d) {
      x_ += d;
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

    inline bool isHoverHorizontalPart(float part, float x, float y) const;

    float getBorderBold() const;

    void setBorderBold(float borderBold);

    const sf::Color &getBorderColor() const;

    void setBorderColor(const sf::Color &borderColor);

   private:
    sf::Color background_color_;
    float x_, y_;
    float width_, height_;
    sf::RenderWindow* parent_;
    float border_radius_;
    bool need_render_;

    float border_bold_;
    sf::Color border_color_;
  };

  void Div::render() {
    if (!need_render_) return;
    sf::RectangleShape hor_rect;
    sf::RectangleShape ver_rect;
    sf::CircleShape top_left_cir;
    sf::CircleShape top_right_cir;
    sf::CircleShape bottom_left_cir;
    sf::CircleShape bottom_right_cir;
    if (border_bold_ != 0) {
      // draw border
      float border_x = x_ - border_bold_, border_y = y_ - border_bold_;
      float border_height = height_ + 2*border_bold_, border_width = width_ + 2*border_bold_;

      hor_rect.setPosition(border_x, border_y + border_radius_);
      hor_rect.setSize({border_width, border_height - 2*border_radius_});
      hor_rect.setFillColor(border_color_);

      ver_rect.setPosition(border_x + border_radius_, border_y);
      ver_rect.setSize({border_width - 2*border_radius_, border_height});
      ver_rect.setFillColor(border_color_);

      top_left_cir.setRadius(border_radius_);
      top_left_cir.setPosition(border_x, border_y);
      top_left_cir.setFillColor(border_color_);
      top_right_cir.setRadius(border_radius_);
      top_right_cir.setPosition(border_x + border_width - 2*border_radius_, border_y);
      top_right_cir.setFillColor(border_color_);

      bottom_left_cir.setRadius(border_radius_);
      bottom_left_cir.setPosition(border_x, border_y + border_height - 2*border_radius_);
      bottom_left_cir.setFillColor(border_color_);
      bottom_right_cir.setRadius(border_radius_);
      bottom_right_cir.setPosition(border_x + border_width - 2*border_radius_, border_y + border_height - 2*border_radius_);
      bottom_right_cir.setFillColor(border_color_);

      parent_->draw(hor_rect);
      parent_->draw(ver_rect);
      parent_->draw(top_left_cir);
      parent_->draw(top_right_cir);
      parent_->draw(bottom_right_cir);
      parent_->draw(bottom_left_cir);
    }

    // draw main part
    hor_rect.setPosition(x_, y_ + border_radius_);
    hor_rect.setSize({width_, height_ - 2*border_radius_});
    hor_rect.setFillColor(background_color_);

    ver_rect.setPosition(x_ + border_radius_, y_);
    ver_rect.setSize({width_ - 2*border_radius_, height_});
    ver_rect.setFillColor(background_color_);

    top_left_cir.setRadius(border_radius_);
    top_left_cir.setPosition(x_, y_);
    top_left_cir.setFillColor(background_color_);
    top_right_cir.setRadius(border_radius_);
    top_right_cir.setPosition(x_ + width_ - 2*border_radius_, y_);
    top_right_cir.setFillColor(background_color_);

    bottom_left_cir.setRadius(border_radius_);
    bottom_left_cir.setPosition(x_, y_ + height_ - 2*border_radius_);
    bottom_left_cir.setFillColor(background_color_);
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

  inline bool Div::isHovered(float x, float y) const {
    return isHoverHorizontalPart(1, x, y);
  }

  inline bool Div::isHoverHorizontalPart(float part, float x, float y) const {
    if (x >= x_ &&
        y >= y_ + border_radius_ &&
        x <= x_ + width_*part &&
        y <= y_ + height_ - 2*border_radius_) {
      return true;
    }

    if (x >= x_ + border_radius_ &&
        y >= y_ &&
        x <= x_ + part*width_ - 2*border_radius_ &&
        y <= y_ + height_) {
      return true;
    }

    if ((x - x_ - border_radius_)*(x - x_ - border_radius_) +
        (y - y_ - border_radius_)*(y - y_ - border_radius_) <= border_radius_*border_radius_ &&
        x <= x_ + width_*part) {
      return true;
    }

    if ((x - x_ - width_ + border_radius_)*(x - x_ - width_ + border_radius_) +
        (y - y_ - border_radius_)*(y - y_ - border_radius_) <= border_radius_*border_radius_ &&
        x <= x_ + width_*part) {
      return true;
    }

    if ((x - x_ - border_radius_)*(x - x_ - border_radius_) +
        (y - y_ + border_radius_ - height_)*(y - y_ + border_radius_ - height_) <= border_radius_*border_radius_ &&
        x <= x_ + width_*part) {
      return true;
    }

    if ((x - x_ - width_ + border_radius_)*(x - x_ - width_ + border_radius_) +
        (y - y_ + border_radius_ - height_)*(y - y_ + border_radius_ - height_) <= border_radius_*border_radius_ &&
        x <= x_ + width_*part) {
      return true;
    }

    return false;
  }

  float Div::getBorderBold() const {
    return border_bold_;
  }

  void Div::setBorderBold(float borderBold) {
    if (borderBold < 0) throw std::runtime_error("border bold less than zero");
    border_bold_ = borderBold;
  }

  const sf::Color &Div::getBorderColor() const {
    return border_color_;
  }

  void Div::setBorderColor(const sf::Color &borderColor) {
    border_color_ = borderColor;
  }

  float Div::getCenterY() const {
    return x_ + width_/2;
  }

  float Div::getCenterX() const {
    return y_ + height_/2;
  }
}
