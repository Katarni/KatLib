//
// Created by Тимур Ахметзянов on 29.04.2024.
//

#pragma once

#include "header.h"

namespace kat {
  class Line {
   public:
    Line() {
      line_[0] = sf::Vertex({0, 01}, sf::Color::Black);
      line_[1] = sf::Vertex({0, 0}, sf::Color::Black);
      parent_ = nullptr;
    }
    Line(sf::RenderWindow* parent) {
      line_[0] = sf::Vertex({0, 01}, sf::Color::Black);
      line_[1] = sf::Vertex({0, 0}, sf::Color::Black);
      parent_ = parent;
    }
    Line(float x1, float y1, float x2, float y2, sf::RenderWindow* parent) {
      line_[0] = sf::Vertex({x1, y1}, sf::Color::Black);
      line_[1] = sf::Vertex({x2, y2}, sf::Color::Black);
      parent_ = parent;
    }

    void render() const {
      if (parent_ == nullptr) return;
      parent_->draw(line_, 2, sf::Lines);
    }

   private:
    sf::RenderWindow* parent_;
    sf::Vertex line_[2];
  };
}