//
// Created by Тимур Ахметзянов on 26.03.2024.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <iostream>
#include <string>
#include <vector>

std::pair<int, int> getStringParams(const std::string& str) {
  int cnt_lines = 0, max_wid = 0, curr_wid = 0;
  for (char c : str) {
    cnt_lines += !curr_wid;
    if (c == '\n') {
      max_wid = std::max(max_wid, curr_wid);
      curr_wid = -1;
    }
    ++curr_wid;
  }

  return {std::max(max_wid, curr_wid), cnt_lines};
}

char getCharFromEvent(const sf::Event& e, bool is_shift) {
  if (e.key.code == sf::Keyboard::A) {
    return is_shift ? 'A' : 'a';
  } else if (e.key.code == sf::Keyboard::B) {
    return is_shift ? 'B' : 'b';
  } else if (e.key.code == sf::Keyboard::C) {
    return is_shift ? 'C' : 'c';
  } else if (e.key.code == sf::Keyboard::D) {
    return is_shift ? 'D' : 'd';
  } else if (e.key.code == sf::Keyboard::E) {
    return is_shift ? 'E' : 'e';
  } else if (e.key.code == sf::Keyboard::F) {
    return is_shift ? 'F' : 'f';
  } else if (e.key.code == sf::Keyboard::G) {
    return is_shift ? 'G' : 'g';
  } else if (e.key.code == sf::Keyboard::H) {
    return is_shift ? 'H' : 'h';
  } else if (e.key.code == sf::Keyboard::I) {
    return is_shift ? 'I' : 'i';
  } else if (e.key.code == sf::Keyboard::J) {
    return is_shift ? 'J' : 'j';
  } else if (e.key.code == sf::Keyboard::K) {
    return is_shift ? 'K' : 'k';
  } else if (e.key.code == sf::Keyboard::L) {
    return is_shift ? 'L' : 'l';
  } else if (e.key.code == sf::Keyboard::M) {
    return is_shift ? 'M' : 'm';
  } else if (e.key.code == sf::Keyboard::N) {
    return is_shift ? 'N' : 'n';
  } else if (e.key.code == sf::Keyboard::O) {
    return is_shift ? 'O' : 'o';
  } else if (e.key.code == sf::Keyboard::P) {
    return is_shift ? 'P' : 'p';
  } else if (e.key.code == sf::Keyboard::Q) {
    return is_shift ? 'Q' : 'q';
  } else if (e.key.code == sf::Keyboard::R) {
    return is_shift ? 'R' : 'r';
  } else if (e.key.code == sf::Keyboard::S) {
    return is_shift ? 'S' : 's';
  } else if (e.key.code == sf::Keyboard::T) {
    return is_shift ? 'T' : 't';
  } else if (e.key.code == sf::Keyboard::U) {
    return is_shift ? 'U' : 'u';
  } else if (e.key.code == sf::Keyboard::V) {
    return is_shift ? 'V' : 'v';
  } else if (e.key.code == sf::Keyboard::W) {
    return is_shift ? 'W' : 'w';
  } else if (e.key.code == sf::Keyboard::X) {
    return is_shift ? 'X' : 'x';
  } else if (e.key.code == sf::Keyboard::Y) {
    return is_shift ? 'Y' : 'y';
  } else if (e.key.code == sf::Keyboard::Z) {
    return is_shift ? 'Z' : 'z';
  }

  if (e.key.code == sf::Keyboard::Num0) {
    return is_shift ? ')' : '0';
  } else if (e.key.code == sf::Keyboard::Num1) {
    return is_shift ? '!' : '1';
  } else if (e.key.code == sf::Keyboard::Num2) {
    return is_shift ? '@' : '2';
  } else if (e.key.code == sf::Keyboard::Num3) {
    return is_shift ? '#' : '3';
  } else if (e.key.code == sf::Keyboard::Num4) {
    return is_shift ? '$' : '4';
  } else if (e.key.code == sf::Keyboard::Num5) {
    return is_shift ? '%' : '5';
  } else if (e.key.code == sf::Keyboard::Num6) {
    return is_shift ? '^' : '6';
  } else if (e.key.code == sf::Keyboard::Num7) {
    return is_shift ? '&' : '7';
  } else if (e.key.code == sf::Keyboard::Num8) {
    return is_shift ? '*' : '8';
  } else if (e.key.code == sf::Keyboard::Num9) {
    return is_shift ? '(' : '9';
  }

  if (e.key.code == sf::Keyboard::Enter) {
    return '\n';
  }

  if (e.key.code == sf::Keyboard::Equal) {
    return is_shift ? '+' : '=';
  } else if (e.key.code == sf::Keyboard::Hyphen) {
    return is_shift ? '_' : '-';
  } else if (e.key.code == sf::Keyboard::Period) {
    return is_shift ? '>' : '.';
  } else if (e.key.code == sf::Keyboard::Comma) {
    return is_shift ? '<' : ',';
  } else if (e.key.code == sf::Keyboard::Slash) {
    return is_shift ? '?' : '/';
  } else if (e.key.code == sf::Keyboard::Grave) {
    return is_shift ? '~' : '`';
  }

  return -1;
}

std::pair<float, float> normalizeSize(const std::string& data, const std::vector<float>& paddings,
                                      int font_size, float font_mul) {
  auto params = getStringParams(data);
  std::pair<float, float> size;
  size.first = float(params.first*font_size)/font_mul + (float)paddings[0] + (float)paddings[2];
  size.second = float(params.second*font_size) + (float)paddings[1] + (float)paddings[3];
  return size;
}

bool isNumber(const std::string& str) {
  for (char c : str) {
    if (c < '0' || '9' < c) return false;
  }
  return true;
}
