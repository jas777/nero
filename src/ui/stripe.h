//
// Created by User on 13.03.2022.
//

#ifndef NERO_STRIPE_H
#define NERO_STRIPE_H

#include <ftxui/dom/elements.hpp>
#include <string>

using namespace ftxui;

ftxui::Element TextStripe(const std::string &content, ftxui::Color bgColor, ftxui::Color textColor) {
    return hbox({
                        text(content) | center | bgcolor(bgColor) | color(textColor) | hcenter | flex
                }) | bgcolor(bgColor) | size(Direction::HEIGHT, Constraint::EQUAL, 1);
}

#endif //NERO_STRIPE_H
