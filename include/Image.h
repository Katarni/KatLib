//
// Created by Тимур Ахметзянов on 22.09.2024.
//

#include <Div.h>


namespace kat {
    class Image : public Div {
     public:
        Image() : Div() {}
        explicit Image(sf::RenderWindow* window) : Div(window) {}
        Image(const sf::Image& image, sf::RenderWindow* window) : Div(window), image_(image) {}
        Image(const std::string& file, sf::RenderWindow* window) : Div(window) {
            if (!image_.loadFromFile(file)) {
                throw std::runtime_error("image " + file + " not loaded");
            }
        }

        void render() override {
            sf::Texture texture;
            texture.loadFromImage(image_);
            sf::Sprite sprite;
            sprite.setTexture(texture, true);

            getParent()->draw(sprite);
        }

     private:
        sf::Image image_;
    };
}