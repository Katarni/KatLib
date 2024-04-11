//
// Created by Тимур Ахметзянов on 01.04.2024.
//

#pragma once

#include "CheckBox.h"
#include "../TextInput.h"


namespace kat {
  class ScrollTextInputs : public CheckBox {
   public:
    ScrollTextInputs() : CheckBox() {}
    ScrollTextInputs(float x, float y,
             float width, float height,
             sf::RenderWindow* parent,
             float elm_width, float input_width, float elm_height,
             const sf::Font& font) : CheckBox(x, y, width, height, parent, elm_width, elm_height, font),
                                     input_width_(input_width) {
      setButtonWidth(input_width + elm_width);
    }

    void addElm(const std::string& data) override {
      if (getElms().empty()) {
        getElms().emplace_back(getX() + getPaddings()[0], getY() + getPaddings()[1],
                                getElmWidth(), getElmHeight(), data, getFont(), getParent());
        inputs_.emplace_back(getX() + getPaddings()[0] + getElmWidth(), getY() + getPaddings()[0],
                             input_width_, getElmHeight(), getFont(), getParent());
      } else {
        getElms().emplace_back(getX() + getPaddings()[0],
                                getElms().back().getY() + getElms().back().getHeight() + getElmsDivider(),
                                getElmWidth(), getElmHeight(), data, getFont(), getParent());
        inputs_.emplace_back(getX() + getPaddings()[0] + getElmWidth(),
                               inputs_.back().getY() + inputs_.back().getHeight() + getElmsDivider(),
                               input_width_, getElmHeight(), getFont(), getParent());
      }
    }

    void delElm(int id) override {
      if (id >= getElms().size() || id < 0) return;
      getElms().erase(getElms().begin() + id);
      inputs_.erase(inputs_.begin() + id);
      for (int i = id; i < getElms().size(); ++i) {
        getElms()[i].moveY(-(getElms()[i].getHeight() + getElmsDivider()));
        inputs_[i].moveY(-(inputs_[i].getHeight() + getElmsDivider()));
      }
      updId();
    }

    int isPressed(float x, float y) override;

    void addCharacter(char c);
    void deleteCharacter();

    void moveCursorRight();
    void moveCursorLeft();

    void render() override;

    void clearElms() override;

    std::unordered_map<std::string, std::string>& getText();

   private:
    float input_width_;
    std::vector<TextInput> inputs_;
    std::unordered_map<std::string, std::string> text;
  };

  int ScrollTextInputs::isPressed(float x, float y) {
    if (getAcceptBtn().isPressed(x, y)) return 2;

    int ret = 0;
    for (int i = 0; i < getElms().size(); ++i) {
      if (getElms()[i].isPressed(x, y) || inputs_[i].isPressed(x, y)) {
        deselectAll();
        getElms()[i].setSelected(true);
        getSelectedIndxs().insert(i);
        ret = 1;
      } else {
        getSelectedIndxs().erase(i);
      }
    }
    return ret;
  }

  void ScrollTextInputs::addCharacter(char c) {
    if (getSelectedIndxs().empty()) return;
    inputs_[*getSelectedIndxs().begin()].addCharacter(c);
  }

  void ScrollTextInputs::deleteCharacter() {
    if (getSelectedIndxs().empty()) return;
    inputs_[*getSelectedIndxs().begin()].delCharacter();
  }

  void ScrollTextInputs::render() {
    CheckBox::render();

    for (auto & input : inputs_) {
      if (input.getY() >= getY() + getPaddings()[1]
          && input.getY() + 2*getElmHeight() <= getY() + getHeight() + getPaddings()[3] - getElmsDivider()) {
        input.setBorderRadius(getElmBorderRadius());
        input.setBackgroundColor(getElmBackground());
        input.render();
      }
    }
  }

  void ScrollTextInputs::clearElms() {
    inputs_.resize(0);
    HorScrollArea::clearElms();
  }

  void ScrollTextInputs::moveCursorRight() {
    if (getSelectedIndxs().empty()) return;
    inputs_[*getSelectedIndxs().begin()].moveCursorRight();
  }

  void ScrollTextInputs::moveCursorLeft() {
    if (getSelectedIndxs().empty()) return;
    inputs_[*getSelectedIndxs().begin()].moveCursorLeft();
  }

  std::unordered_map<std::string, std::string>& ScrollTextInputs::getText() {
    text.clear();
    for (int i = 0; i < inputs_.size(); ++i) {
      text[getElms()[i].getData()] = inputs_[i].getData();
    }
    return text;
  }
}
