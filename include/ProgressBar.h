//
// Created by Тимур Ахметзянов on 22.09.2024.
//

#pragma once

#include "Div.h"


namespace kat {
    class ProgressBar : public Div {
     public:
        ProgressBar(): Div(), progress_(0), progress_color_(sf::Color::Black) {}
        explicit ProgressBar(sf::RenderWindow* window): Div(window), progress_(0),
                                                        progress_color_(sf::Color::Black) {}
        ProgressBar(float x, float y,
            float width, float height,
            sf::RenderWindow* parent): Div(x, y, width, height, parent), progress_(0),
                                        progress_color_(sf::Color::Black) {}

        void setProgress(double progress) {
            progress_ = progress;
        }

        void addProgress(double delta) {
            progress_ += delta;
        }

        [[nodiscard]]
        double getProgress() const {
            return progress_;
        }

        [[nodiscard]]
        const sf::Color &getProgressColor() const {
            return progress_color_;
        }

        void setProgressColor(const sf::Color &progressColor) {
            progress_color_ = progressColor;
        }

        void render() override {
            Div::render();

            if (!needRender()) return;

            sf::RectangleShape hor_rect;
            sf::RectangleShape ver_rect;
            sf::CircleShape top_left_cir;
            sf::CircleShape bottom_left_cir;

            float p_width = getWidth() * progress_ - getBorderBold();

            hor_rect.setPosition(getX(), getY() + getBorderRadius());
            hor_rect.setSize({p_width, getHeight() - 2*getBorderRadius()});
            hor_rect.setFillColor(progress_color_);

            ver_rect.setPosition(getX() + getBorderRadius(), getY());
            ver_rect.setSize({p_width - getBorderRadius(), getHeight()});
            ver_rect.setFillColor(progress_color_);

            top_left_cir.setRadius(getBorderRadius());
            top_left_cir.setPosition(getX(), getY());
            top_left_cir.setFillColor(progress_color_);

            bottom_left_cir.setRadius(getBorderRadius());
            bottom_left_cir.setPosition(getX(), getY() + getHeight() - 2*getBorderRadius());
            bottom_left_cir.setFillColor(progress_color_);

            getParent()->draw(hor_rect);
            getParent()->draw(ver_rect);
            getParent()->draw(top_left_cir);
            getParent()->draw(bottom_left_cir);
        }

     private:
        float progress_;
        sf::Color progress_color_;
    };
}
