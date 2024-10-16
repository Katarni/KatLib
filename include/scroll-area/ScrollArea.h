//
// Created by Тимур Ахметзянов on 18.04.2024.
//

#pragma once

#include "../Div.h"


namespace kat {
    class ScrollArea : public Div {
     public:
        ScrollArea() : Div(), elms_(std::vector<Div *>(0)), crop_borders_(false) {}

        explicit ScrollArea(sf::RenderWindow *parent) : Div(parent),
                                                        elms_(std::vector<Div *>(0)), crop_borders_(false) {}

        ScrollArea(float x, float y,
                   float width, float height,
                   sf::RenderWindow *parent) : Div(x, y, width, height, parent),
                                                elms_(std::vector<Div *>(0)), crop_borders_(false) {}

        virtual ~ScrollArea() {
            clear();
        }

        void render() override {
            if (!needRender()) return;

            Div::render();
            for (auto &elm: elms_) {
                if (crop_borders_) {
                    if (elm->getX() >= getX() &&
                        elm->getY() >= getY() &&
                        elm->getX() + elm->getWidth() <= getX() + getWidth() &&
                        elm->getY() + elm->getHeight()  <= getY() + getHeight()) {
                        elm->render();
                    }
                } else {
                    if (elm->getX() + elm->getWidth() >= getX() &&
                        elm->getY() + elm->getHeight() >= getY() &&
                        elm->getX() <= getX() + getWidth() &&
                        elm->getY() <= getY() + getHeight()) {
                        elm->render();
                    }
                }
            }
        }

        bool moveAllX(float d) {
            if (d == 0) return true;

            if (d > 0) {
                float min_x = 1e9;
                for (auto &elm: elms_) {
                    min_x = std::min(min_x, elm->getX());
                }
                if (min_x > getX()) return false;
            } else {
                float max_x = -1e9;
                for (auto &elm: elms_) {
                    max_x = std::max(max_x, elm->getX() + elm->getWidth());
                }
                if (max_x < getX() + getWidth()) return false;
            }

            for (auto &elm: elms_) {
                elm->moveX(d);
            }
            return true;
        }

        bool moveAllY(float d) {
            if (d == 0) return true;

            if (d > 0) {
                float min_y = 1e9;
                for (auto &elm: elms_) {
                    min_y = std::min(min_y, elm->getY());
                }
                if (min_y > getY()) return false;
            } else {
                float max_y = -1e9;
                for (auto &elm: elms_) {
                    max_y = std::max(max_y, elm->getY() + elm->getHeight());
                }
                if (max_y < getY() + getHeight()) return false;
            }

            for (auto &elm: elms_) {
                elm->moveY(d);
            }
            return true;
        }

        virtual void addElm(Div* btn) {
            elms_.push_back(btn);
        }

        virtual void removeElm(int idx) {
            if (idx >= elms_.size() || idx < 0) {
                throw std::runtime_error("ScrollArea out of range");
            }
            delete elms_[idx];
            elms_.erase(elms_.begin() + idx);
        }

        virtual void popBack() {
            if (elms_.empty()) {
                throw std::runtime_error("ScrollArea out of range");
            }

            delete elms_.back();
            elms_.pop_back();
        }

        void clear() {
            for (auto &i: elms_) {
                delete i;
            }
            elms_.resize(0);
        }

        std::vector<Div *> &getElms() {
            return elms_;
        }

        virtual void isPressed(float x, float y) {
            for (auto &elm: elms_) {
                if (crop_borders_) {
                    if (elm->getX() >= getX() &&
                        elm->getY() >= getY() &&
                        elm->getX() + elm->getWidth() <= getX() + getWidth() &&
                        elm->getY() + elm->getHeight()  <= getY() + getHeight()) {
                        auto btn = dynamic_cast<Button*>(elm);
                        if (btn != nullptr) {
                            btn->isPressed(x, y);
                        }
                    }
                } else {
                    if (elm->getX() + elm->getWidth() >= getX() &&
                        elm->getY() + elm->getHeight() >= getY() &&
                        elm->getX() <= getX() + getWidth() &&
                        elm->getY() <= getY() + getHeight()) {
                        auto btn = dynamic_cast<Button*>(elm);
                        if (btn != nullptr) {
                            btn->isPressed(x, y);
                        }
                    }
                }
            }
        }

        bool isCropBorders() const {
            return crop_borders_;
        }

        void setCropBorders(bool cropBorders) {
            crop_borders_ = cropBorders;
        }

     private:
        std::vector<Div *> elms_;
        bool crop_borders_;
    };
}
