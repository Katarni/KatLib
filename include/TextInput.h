//
// Created by Тимур Ахметзянов on 28.03.2024.
//

#pragma once

#include "Button.h"


namespace kat {
  class TextInput : public Button {
   public:
    TextInput() : Button() {}
    TextInput(float x, float y,
              float width, float height,
              const sf::Font &font, sf::RenderWindow *parent) : Button(x, y, width, height, "", font, parent),
                                                                cursor_pos_(0), selected_(false), L_(0), R_(0) {
      max_text_sz_ = int((getWidth() - getPaddings()[0] - getPaddings()[2]) / ((float)getFontSize()/1.6f));
    }

    void addCharacter(char c) {
      auto data = getData();
      data.insert(data.begin() + cursor_pos_, c);
      setData(data);
      R_ += (R_ - L_ < max_text_sz_ && R_ - L_ < data.size());
      ++cursor_pos_;
      if (cursor_pos_ > R_) {
        ++L_;
        ++R_;
      }
    }

    void delCharacter() {
      auto data = getData();
      if (data.empty()) return;
      if (cursor_pos_ == 0) return;
      R_ -= (R_ - L_ == data.size());
      data.erase(--cursor_pos_, 1);
      if (R_ > data.size()) {
        --L_;
        --R_;
      }
      if (cursor_pos_ < L_) {
        --L_;
        --R_;
      }
      setData(data);
    }

    void moveCursorLeft() {
      if (cursor_pos_ != 0) {
        --cursor_pos_;
      }
      if (cursor_pos_ < L_) {
        --L_;
        --R_;
      }
    }

    void moveCursorRight() {
      if (cursor_pos_ != getData().size()) {
        ++cursor_pos_;
      }

      if (cursor_pos_ > R_) {
        ++L_;
        ++R_;
      }
    }

    inline bool isPressed(float x, float y) override;

    void render() override;

    bool isSelected() const;

    void setWidth(float width) override;

    void setPaddings(const std::vector<float>& paddings) override;

    void clear();

    void setData(const std::string& data) override;

   private:
    int cursor_pos_;
    bool selected_ = false;
    int max_text_sz_;
    int L_, R_;
  };

  bool TextInput::isPressed(float x, float y) {
    return selected_ = Button::isPressed(x, y);
  }

  bool TextInput::isSelected() const {
    return selected_;
  }

  void TextInput::render() {
    if (!needRender()) return;
    std::string str = std::string(getData().begin() + L_, getData().begin() + R_);

    auto text_params = getStringParams(str);
    float text_x = (getWidth() - (float)text_params.first*(float)getFontSize()/1.6f)/ 2 + getX();
    float text_y = getY() +
                   (getHeight() - (float)text_params.second*(float)getFontSize()) / 2 -
                   (float)getFontSize()/5;

    sf::Text text;
    text.setFont(getFont());
    text.setFillColor(getColor());
    text.setCharacterSize(getFontSize());
    text.setString(str);
    text.setPosition(text_x, text_y);

    Div::render();
    getParent()->draw(text);
  }

  void TextInput::setWidth(float width) {
    Div::setWidth(width);
    max_text_sz_ = int((getWidth() - getPaddings()[0] - getPaddings()[2]) / ((float)getFontSize()/1.6f));
  }

  void TextInput::setPaddings(const std::vector<float>& paddings) {
    Label::setPaddings(paddings);
    max_text_sz_ = int((getWidth() - getPaddings()[0] - getPaddings()[2]) / ((float)getFontSize()/1.6f));
  }

  void TextInput::clear() {
    Button::setData("");
    cursor_pos_ = 0;
    L_ = 0;
    R_ = 0;
  }

  void TextInput::setData(const std::string &data) {
    Label::setData(data);
    L_ = 0;
    R_ = std::min((int)data.size(), max_text_sz_);
  }
}
