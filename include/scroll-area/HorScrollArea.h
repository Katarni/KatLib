//
// Created by Тимур Ахметзянов on 29.03.2024.
//

#pragma once

#include "../Div.h"
#include "ScrollAreaElm.h"


namespace kat {
  class HorScrollArea : public Div {
   public:
    HorScrollArea() : Div(), elms_(std::vector<ScrollAreaElm>(0)) {}
    HorScrollArea(float x, float y,
                  float width, float height,
                  sf::RenderWindow* parent,
                  float elm_width, float elm_height,
                  const sf::Font& font) : Div(x, y, width, height, parent),
                                          elms_(std::vector<ScrollAreaElm>(0)),
                                          elm_width_(elm_width), elm_height_(elm_height), font_(font),
                                          paddings_(std::vector<float>(4, 0)), elms_divider_(0),
                                          elm_border_radius_(0), elm_background_(sf::Color::White),
                                          selected_background_(sf::Color::White) {}

    void updId() {
      selected_indxs_.clear();
      for (int i = 0; i < elms_.size(); ++i) {
        if (elms_[i].isSelected()) {
          selected_indxs_.insert(i);
        }
      }
    }

    void setElmsBackgroundColor(sf::Color color) {
      elm_background_ = color;
    }

    virtual void setElmBorderRadius(float radius) {
      elm_border_radius_ = radius;
    }

    virtual void addElm(const std::string& data) {
      if (elms_.empty()) {
        elms_.emplace_back(getX() + paddings_[0], getY() + paddings_[1],
                         elm_width_, elm_height_, data, font_, getParent());
      } else {
        elms_.emplace_back(getX() + paddings_[0], elms_.back().getY() + elms_.back().getHeight() + elms_divider_,
                           elm_width_, elm_height_, data, font_, getParent());
      }
    }

    virtual void delElm(int id) {
      if (id >= elms_.size() || id < 0) return;
      elms_.erase(elms_.begin() + id);
      for (int i = id; i < elms_.size(); ++i) {
        elms_[i].moveY(-(elms_[i].getHeight() + elms_divider_));
      }
      updId();
    }

    float getElmsDivider() const {
      return elms_divider_;
    }

    void setElmsDivider(float elmsDivider) {
      elms_divider_ = elmsDivider;
    }

    virtual void moveTop() {
      if (elms_.empty()) return;
      if (elms_.back().getY() + elms_.back().getHeight() <= getY() + getHeight() - paddings_[3]) return;

      for (auto& elm : elms_) {
        elm.moveY(-10);
      }
    }

    virtual void moveBottom() {
      if (elms_.empty()) return;
      if (elms_.front().getY() >= getY() + paddings_[1]) return;

      for (auto& elm : elms_) {
        elm.moveY(10);
      }
    }

    void render() override {
      Div::render();

      for (auto & elm : elms_) {
        if (elm.getY() >= getY() + paddings_[1]
            && elm.getY() + elm.getHeight() <= getY() + getHeight() + paddings_[3]) {
          elm.setBorderRadius(elm_border_radius_);
          if (elm.isSelected()) {
            elm.setBackgroundColor(selected_background_);
          } else {
            elm.setBackgroundColor(elm_background_);
          }
          elm.render();
        }
      }
    }

    const std::vector<float> &getPaddings() const {
      return paddings_;
    }

    virtual void setPaddings(const std::vector<float> &paddings) {
      paddings_ = paddings;
    }

    std::vector<ScrollAreaElm>& getElms() {
      return elms_;
    }

    void setSelectedBackground(const sf::Color &selectedBackground) {
      selected_background_ = selectedBackground;
    }

    std::set<int> &getSelectedIndxs() {
      return selected_indxs_;
    }

    virtual void deselectAll() {
      selected_indxs_.clear();
      for (auto & elm : elms_) {
        elm.setSelected(false);
      }
    }

    virtual int isPressed(float x, float y) {
      int i = 0;
      int ret = 0;
      for (auto& elm : elms_) {
        if (elm.isPressed(x, y)) {
          selected_indxs_.insert(i);
          ret = 1;
        } else {
          selected_indxs_.erase(i);
        }
        ++i;
      }
      return ret;
    }

    virtual void clearElms() {
      elms_.resize(0);
      selected_indxs_.clear();
    }

    float getElmBorderRadius() const {
      return elm_border_radius_;
    }

    const sf::Color &getSelectedBackground() const {
      return selected_background_;
    }

    const sf::Color &getElmBackground() const {
      return elm_background_;
    }

    float getElmWidth() const {
      return elm_width_;
    }

    float getElmHeight() const {
      return elm_height_;
    }

    const sf::Font &getFont() const {
      return font_;
    }

   private:
    float elm_width_, elm_height_;
    float elms_divider_;
    float elm_border_radius_;

    std::vector<ScrollAreaElm> elms_;
    std::set<int> selected_indxs_;

    std::vector<float> paddings_;

    sf::Font font_;
    sf::Color elm_background_;
    sf::Color selected_background_;
  };
}
