//
// Created by Тимур Ахметзянов on 24.09.2024.
//

#pragma once

#include <Image.h>

namespace kat {

    class Animation : public Image {
     public:
        Animation(const std::string& dir, int count,
                  const std::string& prefix, const std::string& postfix,
                  sf::RenderWindow* window) : Image(dir + prefix + "0" + postfix, window), postfix_(postfix),
                                              prefix_(prefix), dir_(dir), count_(count), cur_frame_(0) {

        }

        bool nextFrame() {
            bool ret = false;
            ++cur_frame_;
            if (cur_frame_ == count_) {
                cur_frame_ = 0;
                ret = true;
            }

            loadFromFile(dir_ + prefix_ + std::to_string(cur_frame_) + postfix_);
            return ret;
        }

     private:
        int count_, cur_frame_;
        std::string dir_, prefix_, postfix_;
    };

} // kat
