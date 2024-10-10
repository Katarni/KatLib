//
// Created by Тимур Ахметзянов on 29.03.2024.
//

#pragma once

#include "ScrollArea.h"


namespace kat {
    class HorScrollArea : public ScrollArea {
     public:
        HorScrollArea() : ScrollArea() {}

        explicit HorScrollArea(sf::RenderWindow *parent) : ScrollArea(parent) {}

        HorScrollArea(float x, float y,
                      float width, float height,
                      sf::RenderWindow *parent) : ScrollArea(x, y, width, height, parent) {}
     private:
        using ScrollArea::moveAllY;
    };
}
