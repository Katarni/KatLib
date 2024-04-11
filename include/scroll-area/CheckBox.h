//
// Created by Тимур Ахметзянов on 01.04.2024.
//

#pragma once

#include "scroll-area/HorScrollArea.h"


namespace kat {
  class CheckBox : public HorScrollArea {
   public:
    CheckBox() : HorScrollArea(), accept_btn_(Button()) {}
    CheckBox(float x, float y,
             float width, float height,
             sf::RenderWindow* parent,
             float elm_width, float elm_height,
             const sf::Font& font) : HorScrollArea(x, y, width, height, parent, elm_width, elm_height, font),
                                     accept_btn_(Button(x, y + height - elm_height,
                                                        elm_width, elm_height, "AC", font, parent)) {}

    void render() override;

    int isPressed(float x, float y) override;

    void moveTop() override;

    void setElmBorderRadius(float radius) override {
      HorScrollArea::setElmBorderRadius(radius);
      accept_btn_.setBorderRadius(radius);
    }

    void setPaddings(const std::vector<float> &paddings) override {
      HorScrollArea::setPaddings(paddings);
      accept_btn_.moveX(paddings[0]);
      accept_btn_.moveY(-paddings[3]);
    }

    void setBtnBackgroundColor(sf::Color color) {
      accept_btn_.setBackgroundColor(color);
    }

    Button &getAcceptBtn();

    void setButtonWidth(float width);
    void setButtonHeight(float height);

   private:
    Button accept_btn_;
  };


  void CheckBox::render() {
    Div::render();

    for (auto & elm : getElms()) {
      if (elm.getY() >= getY() + getPaddings()[1]
          && elm.getY() + 2*getElmHeight() <= getY() + getHeight() + getPaddings()[3] - getElmsDivider()) {
        elm.setBorderRadius(getElmBorderRadius());
        if (elm.isSelected()) {
          elm.setBackgroundColor(getSelectedBackground());
        } else {
          elm.setBackgroundColor(getElmBackground());
        }
        elm.render();
      }
    }

    accept_btn_.render();
  }

  int CheckBox::isPressed(float x, float y) {
    if (accept_btn_.isPressed(x, y)) return 2;

    int ret = 0;
    int i = 0;
    for (auto& elm : getElms()) {
      if (elm.isPressed(x, y)) {
        deselectAll();
        elm.setSelected(true);
        getSelectedIndxs().insert(i);
        ret = 1;
      } else {
        getSelectedIndxs().erase(i);
      }
      ++i;
    }
    return ret;
  }

  void CheckBox::moveTop() {
    if (getElms().empty()) return;
    if (getElms().back().getY() + 2*getElms().back().getHeight() <=
        getY() + getHeight() - getPaddings()[3] - getElmsDivider()) return;

    for (auto& elm : getElms()) {
      elm.moveY(-10);
    }
  }

  Button &CheckBox::getAcceptBtn() {
    return accept_btn_;
  }

  void CheckBox::setButtonWidth(float width) {
    accept_btn_.setWidth(width);
  }

  void CheckBox::setButtonHeight(float height) {
    accept_btn_.setHeight(height);
  }
}
