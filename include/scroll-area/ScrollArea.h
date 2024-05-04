//
// Created by Тимур Ахметзянов on 18.04.2024.
//

#pragma once

#include "../Label.h"


namespace kat {
  class ScrollArea : public Div {
   public:
    ScrollArea() : Div(), elms_(std::vector<Button*>(0)) {}
    ScrollArea(sf::RenderWindow* parent) : Div(parent), elms_(std::vector<Button*>(0)) {}
    ScrollArea(float x, float y,
               float width, float height,
               sf::RenderWindow* parent) : Div(x, y, width, height, parent), elms_(std::vector<Button*>(0)) {}
    ~ScrollArea() {
      clear();
    }

    void render() override {
      if (!needRender()) return;

      Div::render();
      for (auto& elm : elms_) {
        if (elm->getX() >= getX() && elm->getY() >= getY() &&
            elm->getX() + elm->getWidth() <= getX() + getWidth() &&
            elm->getY() + elm->getHeight() <= getY() + getHeight()) {
          elm->render();
        }
      }
    }

    void moveX(float d) override {
      for (auto& elm : elms_) {
        elm->moveX(d);
      }
    }

    void moveY(float d) override {
      for (auto& elm : elms_) {
        elm->moveY(d);
      }
    }

    void addElm(const Button& btn) {
      elms_.push_back(new Button(btn));
    }

    void clear() {
      for (auto& i : elms_) {
        delete i;
      }
      elms_.resize(0);
    }

    std::vector<Button*>& getElms() {
      return elms_;
    }

   private:
    std::vector<Button*> elms_;
  };
}
