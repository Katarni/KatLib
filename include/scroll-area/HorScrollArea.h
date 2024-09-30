//
// Created by Тимур Ахметзянов on 29.03.2024.
//

#pragma once

#include "ScrollArea.h"


namespace kat {
    class HorScrollArea : public ScrollArea {
     private:
        using ScrollArea::moveY;
    };
}
