//
// Created by User on 13.03.2022.
//

#ifndef NERO_COMMAND_H
#define NERO_COMMAND_H

#include <vector>
#include <string>
#include <map>
#include <argparse.hpp>
#include <fstream>
#include <iostream>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "../ui/stripe.h"

using namespace ftxui;

void Edit(std::vector<std::string> lines, std::string file_path, ScreenInteractive &screen);

std::string GetLineNumber(unsigned long long max, unsigned long long num);

void StartApp(int argc, char *args[]) {

    auto screen = ScreenInteractive::Fullscreen();
    auto parser = argparse::ArgumentParser("nero");

    parser
            .add_argument("file")
            .help("The file you want to edit");

    try {
        parser.parse_args(argc, args);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        std::exit(1);
    }

    auto file_path = parser.get<std::string>("file");

    std::ifstream file;
    file.open(file_path, std::ios::in);

    std::vector<std::string> lines;

    if (file.is_open()) {
        for (std::string line; std::getline(file, line);) {
            lines.push_back(line);
        }
    }

    Edit(lines, file_path, screen);

}

void Edit(std::vector<std::string> lines, std::string file_path, ScreenInteractive &screen) {

    unsigned int line_offset = 0;
    unsigned int longest_line = 0;

    auto interface = Renderer([&] {

        Elements line_elements;

        for (unsigned long long i = line_offset; i < lines.size(); i++) {
            line_elements.push_back(
                    hbox({
                                 text(GetLineNumber(lines.size(), i)) | color(Color::GrayDark), text(lines[i])
                         })
            );
            if (lines[i].length() > longest_line) {
                longest_line = lines[i].length();
            }
        }

        return vbox({

                            TextStripe("nero [" + file_path + "]", Color::White, Color::Black),
                            vbox(std::move(line_elements)) | flex,
                            TextStripe("Actions", Color::White, Color::Black),
                            hbox({
                                         text(std::to_string(longest_line))
                                 }) | size(Direction::HEIGHT, Constraint::EQUAL, 3)
                    });
    });

    interface = ftxui::CatchEvent(interface, [&](const Event &event) {
        if (event.input() == Event::ArrowDown.input()) {
            if (line_offset < lines.size()) line_offset++;
        }
        if (event.input() == Event::ArrowUp.input()) {
            if (line_offset > 0) line_offset--;
        }
        return true;
    });

    screen.Loop(interface);
}

std::string GetLineNumber(unsigned long long max, unsigned long long num) {
    unsigned int max_len = std::to_string(max - num).length();
    std::string result = std::to_string(num);
    for (int i = 0; i < max_len; i++) {
        result += " ";
    }
    return result;
}

#endif //NERO_COMMAND_H
