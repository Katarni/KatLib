//
// Created by Тимур Ахметзянов on 29.03.2024.
//

#pragma once

#include "ScrollArea.h"


namespace kat {
    class VerScrollArea : public ScrollArea {
     public:
        VerScrollArea() : ScrollArea() {}

        explicit VerScrollArea(sf::RenderWindow *parent) : ScrollArea(parent) {}

        VerScrollArea(float x, float y,
                   float width, float height,
                   sf::RenderWindow *parent) : ScrollArea(x, y, width, height, parent) {}
     private:
        using ScrollArea::moveAllX;
    };
}
