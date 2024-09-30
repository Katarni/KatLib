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

        bool tick() {
            ++iter_;
            if (iter_ % duration_ == 0) {
                iter_ = 0;
                nextFrame();
                return true;
            }
            return false;
        }

        void setDuration(int duration) {
            duration_ = duration;
        }

     private:
        int iter_ = 0;
        int count_, cur_frame_, duration_ = 1;
        std::string dir_, prefix_, postfix_;
    };

} // kat
