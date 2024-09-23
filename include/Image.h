//
// Created by Тимур Ахметзянов on 22.09.2024.
//

#pragma once

#include <Div.h>


namespace kat {
    class Image : public Div {
     public:
        Image() : Div() {}
        explicit Image(sf::RenderWindow* window) : Div(window) {}
        Image(const sf::Image& image, sf::RenderWindow* window) : Div(0, 0, static_cast<float>(image.getSize().x),
                                                                      static_cast<float>(image.getSize().y), window),
                                                                  image_(image) {}
        Image(const std::string& file, sf::RenderWindow* window) : Div(window) {
            loadFromFile(file);
        }

        void loadFromFile(const std::string& file) {
            try {
                image_.loadFromFile(file);
            } catch (const std::exception&) {
                throw std::runtime_error("can't load image from " + file);
            }
            setWidth(static_cast<float>(image_.getSize().x));
            setHeight(static_cast<float>(image_.getSize().y));
        }

        virtual void render() override {
            sf::Texture texture;
            texture.loadFromImage(image_);
            sf::Sprite sprite;
            sprite.setTexture(texture, true);
            sprite.setPosition(getX(), getY());

            if (scaled_) {
                sprite.scale(scale_, scale_);
            } else {
                sprite.scale(getWidth() / static_cast<float>(image_.getSize().x),
                             getHeight() / static_cast<float>(image_.getSize().y));
            }

            getParent()->draw(sprite);
        }

        void scale(float scale) {
            scaled_ = true;
            scale_ = scale;
        }

        void resize(float width, float height, bool keep_aspect_ratio = false) {
            scaled_ = false;
            if (keep_aspect_ratio) {
                float temp_height = width * static_cast<float>(image_.getSize().y) / static_cast<float>(image_.getSize().x);

                if (temp_height < height) {
                    height = temp_height;
                } else {
                    width = height * static_cast<float>(image_.getSize().x) / static_cast<float>(image_.getSize().y);
                }
            }

            setWidth(width);
            setHeight(height);
        }

        void resizeByWidth(float width) {
            scaled_ = false;
            setWidth(width);
            setHeight(width * static_cast<float>(image_.getSize().y) / static_cast<float>(image_.getSize().x));
        }

        void resizeByHeight(float height) {
            scaled_ = false;
            setHeight(height);
            setWidth(height * static_cast<float>(image_.getSize().x) / static_cast<float>(image_.getSize().y));
        }

     private:
        bool scaled_ = false;
        float scale_;

        sf::Image image_;

        using Div::setWidth;
        using Div::setHeight;
    };
}