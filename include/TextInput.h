//
// Created by Тимур Ахметзянов on 28.03.2024.
//

#pragma once

#include "Button.h"


namespace kat {
    class TextInput : public Button {
     public:
        TextInput() : Button(), cursor_pos_(0), selected_(false), L_(0), R_(0),
                      placeholder_color_(sf::Color(119, 119, 119)) {}

        TextInput(sf::RenderWindow *parent) : Button(parent), cursor_pos_(0), selected_(false), L_(0), R_(0),
                                              placeholder_color_(sf::Color(119, 119, 119)) {}

        TextInput(float x, float y,
                  float width, float height,
                  const sf::Font &font, sf::RenderWindow *parent) : Button(x, y, width, height, "", font, parent),
                                                                    cursor_pos_(0), selected_(false), L_(0), R_(0),
                                                                    placeholder_color_(sf::Color(119, 119, 119)) {
            max_text_sz_ = int((getWidth() - getPaddings()[0] - getPaddings()[2]) / ((float) getFontSize() / 1.6f));
        }

        TextInput(float x, float y,
                  float width, float height,
                  const std::string &font, sf::RenderWindow *parent) : Button(x, y, width, height, "", font, parent),
                                                                        cursor_pos_(0), selected_(false), L_(0), R_(0),
                                                                       placeholder_color_(sf::Color(119, 119, 119)) {
            max_text_sz_ = int((getWidth() - getPaddings()[0] - getPaddings()[2]) / ((float) getFontSize() / 1.6f));
        }

        virtual void addCharacter(char c) {
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

        virtual void delCharacter() {
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

        virtual void moveCursorLeft() {
            if (cursor_pos_ != 0) {
                --cursor_pos_;
            }
            if (cursor_pos_ < L_) {
                --L_;
                --R_;
            }
        }

        virtual void moveCursorRight() {
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

        virtual bool isSelected() const;

        void setWidth(float width) override;

        void setPaddings(const std::vector<float> &paddings) override;

        void clear();

        void setData(const std::string &data) override;

        void setSelected(bool selected);

        void setPlaceHolder(const std::string& placeholder) {
            placeholder_ = placeholder;
        }

        const sf::Color &getPlaceholderColor() const {
            return placeholder_color_;
        }

        void setPlaceholderColor(const sf::Color &placeholderColor) {
            placeholder_color_ = placeholderColor;
        }

     private:
        int cursor_pos_;
        bool selected_ = false;
        int max_text_sz_;
        int L_, R_;
        std::string placeholder_;
        sf::Color placeholder_color_;
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
        if (str.empty()) {
            str = std::string(placeholder_.begin(),
                              placeholder_.begin() + std::min<int>(max_text_sz_, placeholder_.size()));
        }

        auto text_params = getStringParams(str);
        float text_x = (getWidth() - (float) text_params.first * (float) getFontSize() / 1.6f) / 2 + getX();
        float text_y = getY() +
                       (getHeight() - (float) text_params.second * (float) getFontSize()) / 2 -
                       (float) getFontSize() / 5;

        sf::Text text;
        text.setFont(getFont());
        text.setFillColor(getData().empty() ? placeholder_color_ : getColor());
        text.setCharacterSize(getFontSize());
        text.setString(str);
        text.setPosition(text_x, text_y);

        Div::render();
        getParent()->draw(text);
    }

    void TextInput::setWidth(float width) {
        Div::setWidth(width);
        max_text_sz_ = int((getWidth() - getPaddings()[0] - getPaddings()[2]) / ((float) getFontSize() / 1.6f));
    }

    void TextInput::setPaddings(const std::vector<float> &paddings) {
        Label::setPaddings(paddings);
        max_text_sz_ = int((getWidth() - getPaddings()[0] - getPaddings()[2]) / ((float) getFontSize() / 1.6f));
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
        R_ = std::min((int) data.size(), max_text_sz_);
    }

    void TextInput::setSelected(bool selected) {
        selected_ = selected;
    }
}
